/*
 * VoiceManager.cpp
 *
 *  Created on: 24 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "VoiceManager.hpp"
#include "../Module/Voice.hpp"
#include "../Core/HotPantsCore.hpp"
#include "../../Include/TypesConstants.hpp"

#ifdef MULTITHREAD
  #include <boost/thread/thread.hpp>
#endif

namespace hotpants {

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Constructor / destructor
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  VoiceManager::VoiceManager(HotPantsCore& c)
  : Component(c), mixer(c), _counter(0), _initialised(false) { }

  VoiceManager::~VoiceManager() { _wipeLists(); }

  void VoiceManager::initialise(SamplingRate rate)
  {
    // initialise all voices with the sampling rate
    _wipeLists();
    for(unsigned int i = 0; i < kMaxPolyphony; ++i)
    {
      Voice* v = new Voice(core);
      v->initialise(rate);
      freeVoices.push(v);
    }
    inactiveVoices.reserve(kMaxPolyphony);
    assert(freeVoices.size() == kMaxPolyphony);

    _freeAllVoices();
    _initialised = true;
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Voice activation / deactivation / checking
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Voice* VoiceManager::getVoice(NoteUniqueId ID)
  {
    Voice* ret = 0;

    // need to steal a note?
    if(activeVoices.size() >= static_cast<VoiceCount>(core.getParamManager().getValue(kParam_Polyphony)) ||
       freeVoices.empty())
    {
      // voice steal should always be able to find a note
      // or there is something very wrong!
      ret = _stealVoice();

    } else {
      // assign a voice from the free voices stack
      ret = freeVoices.top();
      freeVoices.pop();
    }

    if(ret != 0) {
      // add to active voice map
      activeVoices.insert(std::make_pair(ID, ActiveVoice(ret, _counter++)));
    }

    // done
    assert(_sanityCheck());
    return ret;
  }

  bool VoiceManager::stopVoice(NoteUniqueId ID)
  {
    assert(_initialised);

    // find the note in the active note map
    ActiveVoiceList::iterator iter = activeVoices.find(ID);
    // note not active?!
    if(iter == activeVoices.end())
      return false;

    // release the note
    Voice* v = iter->second.voice();
    v->release();
    // add to inactive voices vector
    inactiveVoices.push_back(v);
    // remove from active voices map
    activeVoices.erase(iter);

    assert(_sanityCheck());
    // reset note counter on silence
    if(activeVoices.empty() && inactiveVoices.empty())
    {
      _counter = 0;
    }

    return true;
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Render
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  bool VoiceManager::renderAllVoices(Buffer* buffer, BlockSize numFrames)
  {
    assert(_initialised);

    // no sounding voices?
    if(countAllActiveVoices() == 0)
      return false;

    ActiveVoiceList::const_iterator i1;
    InactiveVoiceList::iterator i2;       // might remove a voice
    Voice* v = 0;

#ifdef MULTITHREAD
    boost::thread_group renderThreads;
#endif

    // render from all active voices
    for(i1 = activeVoices.begin(); i1 != activeVoices.end(); ++i1)
    {
      v = i1->second.voice();
#ifdef MULTITHREAD
      renderThreads.add_thread(new boost::thread(_renderAndAddToMixer, &mixer, v, numFrames));
#else
      _renderAndAddToMixer(&mixer, v, numFrames);
#endif
    }

    // render from all inactive voices
    i2 = inactiveVoices.begin();
    while(i2 != inactiveVoices.end()) {

      if(!(*i2)->isSilent())
      {
        // not silent: render this voice
        v = *i2;
#ifdef MULTITHREAD
        renderThreads.add_thread(new boost::thread(_renderAndAddToMixer, &mixer, v, numFrames));
#else
        _renderAndAddToMixer(&mixer, v, numFrames);
#endif
        ++i2;
      } else {
        // silent: reset and remove this voice
        (*i2)->reset();
        freeVoices.push(*i2);
        i2 = inactiveVoices.erase(i2);
        assert(_sanityCheck());
      }
    }

#ifdef MULTITHREAD
    // need to wait for all voices to render
    renderThreads.join_all();
#endif

    // mix to output
    mixer.renderMono(buffer, numFrames);
    return true;
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // List management
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  // completely wipe all the lists
  void VoiceManager::_wipeLists()
  {
    if(!_initialised)
      return;

    // delete all voices
    _freeAllVoices();
    Voice* v;
    while(!freeVoices.empty())
    {
      v = freeVoices.top();
      delete v;
      freeVoices.pop();
    }
  }

  // kill all voices and move to free stack
  void VoiceManager::_freeAllVoices()
  {
    if(!_initialised)
      return;

    Voice* v;

    // active voices
    ActiveVoiceList::iterator iter1;
    for(iter1 = activeVoices.begin();
        iter1 != activeVoices.end();
        ++iter1)
    {
      v = iter1->second.voice();
      v->kill();
      freeVoices.push(v);
    }
    activeVoices.clear();

    // inactive voices
    InactiveVoiceList::iterator iter2;
    for(iter2 = inactiveVoices.begin();
        iter2 != inactiveVoices.end();
        ++iter2)
    {
      v = *iter2;
      v->kill();
      freeVoices.push(v);
    }
    inactiveVoices.clear();

    // reset the note age counter
    _counter = 0;
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Voice stealing
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  Voice* VoiceManager::_stealVoice()
  {
    Voice* v;
    // first try to steal an inactive note
    v = _voiceStealer<InactiveVoiceList, SampleInternal>(inactiveVoices);
    if(v != 0)
      return v;

    // could not get an inactive note, try for an active note
    v = _voiceStealer<ActiveVoiceList, NoteAge>(activeVoices);
    if(v != 0)
      return v;

    // ERROR could not get a note?!
    assert(v != 0);

    return v;
  }

  template<typename T, typename U>
  Voice* VoiceManager::_voiceStealer(T& container)
  {
#ifndef NDEBUG
    typename T::size_type s = container.size();
#endif

    // is this container empty?
    if(container.empty()) return 0;

    // find the lowest amplitude voice in the inactive voice vector
    typename T::iterator iter = container.begin();

    // try the first element
    typename T::iterator lowestElem = iter;
    U lowestVal, thisVal;
    _getPredValue(iter, lowestVal);

    // try all others
    ++iter;
    while(iter != container.end())
    {
      //thisAmp = _derefListIter(iter)->getCurrentAmp();
      _getPredValue(iter, thisVal);

      // is this note quieter?
      if(thisVal < lowestVal)
      {
        lowestVal  = thisVal;
        lowestElem = iter;
      }
      ++iter;
    }

    // kill the voice
    Voice* v = _derefListIter(lowestElem);
    v->kill();
    // remove from container
    container.erase(lowestElem);

#ifndef NDEBUG
    assert(container.size() == s-1);
#endif

    return v;
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Template specialisations
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  template<> Voice* VoiceManager::_derefListIter<ActiveVoiceList::iterator>
  (ActiveVoiceList::iterator iter)
  {
    return iter->second.voice();
  }
  // template specialisation for maps (pair container)
  template<> void VoiceManager::_getPredValue<ActiveVoiceList::iterator, NoteAge>
  (ActiveVoiceList::iterator iter, NoteAge& ret)
  {
    ret = iter->second.age();
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // List debugger
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef NDEBUG
  inline bool VoiceManager::_sanityCheck()
  {
    // check that list sizes make sense
    assert(freeVoices.size() <= kMaxPolyphony);
    assert(activeVoices.size() <= kMaxActive);
    assert(activeVoices.size() + inactiveVoices.size() <= kMaxPolyphony);
    assert(freeVoices.size() + activeVoices.size() + inactiveVoices.size() == kMaxPolyphony);
    return true;
  }
#endif

}
