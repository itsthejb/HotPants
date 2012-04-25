/*
 * Utility.hpp
 *
 * A range of utility functions. General calculations,
 * template functions for output buffers and a wavetable-
 * based trigonometry class.
 *
 *  Created on: 9 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include "../../Include/TypesConstants.hpp"
#include "../../Include/Compilation.hpp"
#include "../Interface/Interfaces.hpp"
#include <map>
#include <cmath>

#ifdef DEDICATED_TRIG_TABLE
  #include "../WaveTable/Direct/SineDirect.hpp"
#endif
#ifdef THREAD_SAFE
  #include <boost/thread/mutex.hpp>
#endif

namespace hotpants {
  
  typedef std::map<MidiNote, NoteFrequency> FreqMap;

  class Utility
  {
    public:
      static void          initialise();
      // midi
      static NoteFrequency midiNoteToFreq(MidiNote);
      static NoteFrequency keyTrackNote(MidiNote n, double c) { return kTuningA * std::pow(c, (n - 69.) / 12.); }
      static double        calcTuning(double t)               { return std::pow(kTwelveRootTwo, t); }
      // floating point comparison
      static bool          fpEqual(double a, double b)        { return (std::abs(a - b) <= kEpsilon); }
      // dB <-> power ratio
      static double        dBGainToPower(double gain)         { return pow(10.0, gain / 10); }
      static double        powerTodBGain(double power)        { return 10 * log10(power); }
      static float         midiControlToFloat(MidiValue v)    { return static_cast<float>(v) / kMidiMaxValue; }
    private:
      static FreqMap       freqMap;
      static bool          _noteTableInit;
#ifdef THREAD_SAFE
      static boost::mutex noteMapMutex;
#endif
  };

  /*
   * Template functions for managing output buffers
   */
  namespace BufferUtils
  {
    template<typename T> void resizeBuffer(T& b, BlockSize s) {
      while(b.size() < s) b.push_back(0.0);
      while(b.size() > s) b.pop_back();
    }
    // specialisation for queues
    template<> void resizeBuffer<DelayQueue>(DelayQueue&, BlockSize);
    template<class T> void wipeBuffer(T& b) { std::fill(b.begin(), b.end(), 0.0); }
  }

  /*
   * Trigonometry calculations using wavetable
   */
  class TrigTable: public Component
  {
    public:
                                    TrigTable(HotPantsCore&);
      double                        sin(double);
      double                        cos(double);
      double                        tan(double);
    private:
      SampleInternal                _getSineVal(IndexedValue);
#ifdef DEDICATED_TRIG_TABLE
      SineDirect                    sineTable;
#endif
  };

}
#endif /* UTILITY_H_ */
