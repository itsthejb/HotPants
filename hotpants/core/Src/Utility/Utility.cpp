/*
 * TrigTable.cpp
 *
 *  Created on: 14 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "Utility.hpp"
#include "../Core/HotPantsCore.hpp"
#include "../../Include/Compilation.hpp"
#include <cmath>
#include <algorithm>

#ifdef THREAD_SAFE
  #include <boost/thread/thread.hpp>
#endif

namespace hotpants {

  bool          Utility::_noteTableInit = false;
  FreqMap       Utility::freqMap = FreqMap();
#ifdef THREAD_SAFE
  boost::mutex  Utility::noteMapMutex;
#endif

  TrigTable::TrigTable(HotPantsCore& c): Component(c)
#ifdef DEDICATED_TRIG_TABLE
  , sineTable(c)
#endif
  { }

  double TrigTable::sin(double angle)
  {
#ifdef TRIG_TABLE
    double indexFP = (kTableLength / kTwoPi) * angle;
    IndexedValue i = static_cast<IndexedValue>(indexFP);
#ifdef TRIG_INTERPOLATE
    SampleInternal s1 = _getSineVal(i);
    SampleInternal s2 = _getSineVal(i+1);
    return s1 + ((s2 - s1) * (indexFP - i));
#else
    return _getSineVal(i);
#endif  // TRIG_INTERPOLATE
#else
    return std::sin(angle);
#endif  // TRIG_TABLE
  }

  double TrigTable::cos(double angle) { return sin(angle + (kPi/2)); }
  double TrigTable::tan(double angle) { return (sin(angle) / cos(angle)); }

  SampleInternal TrigTable::_getSineVal(IndexedValue i)
  {
#ifdef DEDICATED_TRIG_TABLE
    return sineTable.getFrameAtIndex(i);
#else
    return core.getWavetables().getFrameFromTableAtIndex(kWave_SineDirect, i);
#endif
  }

  void Utility::initialise()
  {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(noteMapMutex);
#endif
    for(MidiNote n = kMidiNoteMin; n <= kMidiNoteMax; ++n) {
//      freqMap[n] = kTuningA * std::pow(2., (n - 69.) / 12.);
      freqMap[n] = keyTrackNote(n, 2.0);
    }
    assert(freqMap.size() == static_cast<FreqMap::size_type>(kMidiNumOfNotes));
    // set initialised flag
    _noteTableInit = true;
  }

  NoteFrequency Utility::midiNoteToFreq(MidiNote note)
  {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(noteMapMutex);
#endif
    assert(_noteTableInit);
    FreqMap::const_iterator iter = freqMap.find(note);
    if(iter != freqMap.end())
      return iter->second;
    else
      return 0.0;
  }

  // template specialisation for queues
  template<> void BufferUtils::resizeBuffer<DelayQueue>(DelayQueue& b, BlockSize s) {
    while(b.size() < s) b.push(0.0);
    while(b.size() > s) b.pop();
  }

}
