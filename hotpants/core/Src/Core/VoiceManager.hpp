/*
 * VoiceManager.hpp
 *
 * Manages three containers of voices. A fixed number
 * of voices, up to kMaxPolyphony are allocated at
 * instrument initialisation and put on the free voices
 * stack. After this, voices are shifted between the
 * activeVoices and inactiveVoices containers.
 *
 * The number of active voices is limited to kMaxActive,
 * half of kMaxPolyphony, since notes with a long release
 * may still be sounding in the inactive container.
 *
 * Note-on process:
 * ----------------
 * 1. Try to get a free voices from the freeVoices stack.
 * 2. If it's empty, kill the quiestest voice from the
 *    inactive list.
 * 3. If THAT is empty (all notes active?!), then kill
 *    an active note. This shouldn't ever be necessary,
 *    since an inactive note should alwys be attainable.
 *
 * Rendering:
 * ----------
 * Go through all voices in the active list, and request
 * they render to their internal buffers.
 * Go through the inactive voice list, and request they
 * render. If any silent voices are encountered, then
 * shift them back to the free voices stack.
 *
 * The mixer is passed references to all the voices's
 * internal buffers, and mixes them together into the
 * final output buffer.
 *
 *  Created on: 24 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef VOICEMANAGER_H_
#define VOICEMANAGER_H_

#include "../Interface/Interfaces.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../Mixer/Mixer.hpp"
#include "../Module/Voice.hpp"
#include <map>
#include <stack>
#include <vector>

namespace hotpants {

  /*
   * class ActiveVoice
   *
   * Simple container for a Voice pointer, with
   * an integer measure of the note's "age",
   * used for the stealing of active voices.
   */
  typedef unsigned long NoteAge;
  class ActiveVoice
  {
    public:
      explicit        ActiveVoice(Voice* v, NoteAge a)
                      : _elem(v), _age(a) {}
      NoteAge         age() const   { return _age; }
      Voice*          voice() const { return _elem; }
    private:
      Voice*          _elem;
      NoteAge         _age;
  };

  // voice list container types
  typedef std::stack<Voice*>                    FreeVoiceList;
  typedef std::map<NoteUniqueId, ActiveVoice>   ActiveVoiceList;
  typedef std::vector<Voice*>                   InactiveVoiceList;
  typedef ActiveVoiceList::size_type            VoiceCount;

  class VoiceManager: public Component
  {
    public:
      explicit                                  VoiceManager(HotPantsCore&);
      virtual                                   ~VoiceManager();
      void                                      initialise(SamplingRate);

      Voice*                                    getVoice(NoteUniqueId);
      bool                                      stopVoice(NoteUniqueId);

      bool                                      isNoteActive(NoteUniqueId);
      VoiceCount                                countAllActiveVoices();
      VoiceCount                                countActiveVoices();
      bool                                      renderAllVoices(Buffer*, BlockSize);
      static void                               _renderAndAddToMixer(MonoMixer*, Voice*, BlockSize);

    private:
      // list management
      void                                      _initLists();
      void                                      _clearLists();
      void                                      _freeAllVoices();
      void                                      _wipeLists();
      Voice*                                    _stealVoice();
#ifndef NDEBUG
      bool                                      _sanityCheck();
#endif

      // voice stealing template functions
      template<typename T, typename U>  Voice*  _voiceStealer(T&);
      template<typename T>              Voice*  _derefListIter(T);
      template<typename T, typename U>  void    _getPredValue(T, U&);

      // voice lists
      FreeVoiceList                             freeVoices;
      ActiveVoiceList                           activeVoices;
      InactiveVoiceList                         inactiveVoices;

      // voice mixer
      MonoMixer                                 mixer;
      NoteAge                                   _counter;
      bool                                      _initialised;
  };

  // static stub function to allow dispatching multi-thread rendering
  inline void VoiceManager::_renderAndAddToMixer(MonoMixer* m, Voice* v, BlockSize numFrames)
  {
    m->addBuffer(v->getRenderedBuffer(numFrames), 1.0);
  }

  // active AND inactive voices
  inline VoiceCount VoiceManager::countAllActiveVoices()
  {
    return activeVoices.size() + inactiveVoices.size();
  }

  // just active voices
  inline VoiceCount VoiceManager::countActiveVoices()
  {
    return activeVoices.size();
  }

  inline bool VoiceManager::isNoteActive(NoteUniqueId ID)
  {
    // note is active if it is in the list
    return (activeVoices.find(ID) != activeVoices.end());
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Template Helpers
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  template<typename T> Voice* VoiceManager::_derefListIter(T iter) {
    return *iter;
  }
  template<typename T, typename U> void VoiceManager::_getPredValue(T iter, U& ret) {
    ret = (*iter)->getCurrentAmp();
  }

  // template specialisations for maps (pair container) - see VoiceManager.cpp
  template<> Voice* VoiceManager::_derefListIter<ActiveVoiceList::iterator>
  (ActiveVoiceList::iterator iter);
  template<> void VoiceManager::_getPredValue<ActiveVoiceList::iterator, NoteAge>
  (ActiveVoiceList::iterator iter, NoteAge& ret);

}
#endif /* VOICEMANAGER_H_ */
