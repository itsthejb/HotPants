/*
 * TypesConstants.hpp
 *
 * Type definitions and constants
 *
 *  Created on: 10 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef TYPESCONSTANTS_H_
#define TYPESCONSTANTS_H_

#include "Enums.hpp"
#include <stdint.h>
#include <vector>
#include <limits>
#include <queue>

namespace hotpants {

  /*
   * Types
   */
  typedef float                               Percentage;        // decimal percentage (0.0-1.0)
  //typedef double                              SampleInternal;
  typedef float                               SampleInternal;    // float for performance?
  typedef float                               SampleExternal;
  typedef double                              PhaseValue;
  typedef double                              IndexFPValue;
  typedef unsigned int                        IndexedValue;
  typedef float                               NoteFrequency;
  typedef float                               SamplingRate;
  typedef float                               ParamValue;
  typedef uint32_t                            SampleDuration;
  typedef double                              TimeDuration;

  // buffers
  typedef size_t                              BlockSize;
  typedef SampleExternal                      Buffer;

  // midi types
  typedef int8_t                              MidiType;
  typedef MidiType                            MidiNote;
  typedef MidiType                            MidiVelocity;
  typedef MidiType                            MidiValue;
  typedef MidiType                            MidiCC;
  typedef uint32_t                            NoteUniqueId;

  // containers
  class Voice;
  typedef std::vector<SampleExternal>         BufferMono;
  typedef std::queue<SampleInternal>          DelayQueue;

  /*
   * Wavetable length
   * Short for unit development, 16k for integration (elsewhere)
   */
  const unsigned int    kK           = 1024;
#ifdef  __UNIT_DEV__                                  // use a short wavetable
  const unsigned int    kTableLength = (30);          // during unit development
#else                                                 // use a long (16k) table
  const unsigned int    kTableLength = (16 * kK);     // elsewhere (integration)
#endif

  /*
   * Constants
   */
  const unsigned int    kNumOfInputs          = 0;
  const unsigned int    kNumOfOutputs         = 1;
  const unsigned int    kMaxActive            = 36;
  const unsigned int    kMaxPolyphony         = (2 * kMaxActive);
  const unsigned int    kOctave               = 12;
  const unsigned int    kHarmonicScale        = 8;        // reduction in wavetable harmonics
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // MIDI specification
  const unsigned int    kMidiMaxVelocity      = 127;
  const MidiNote        kMidiNoteMin          = 21;
  const MidiNote        kMidiNoteMax          = 108;
  const MidiNote        kMidiNumOfNotes       = kMidiNoteMax-kMidiNoteMin+1;
  const MidiNote        kMidiNotANote         = -1;
  const float           kTuningA              = 440.0;
  // pitch bend
  const MidiValue       kPitchBendCentre      = 63;
  const MidiValue       kPitchBendMax         = 127;
  const MidiValue       kPitchBendMin         = 0;
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // mathematical constants
  const double          kPi                   = 3.141592653589793;
  const double          kTwoPi                = (2 * kPi);
  const double          kTwelveRootTwo        = 1.05946309435929;
  const double          kRoot2                = 1.41421356237309504880;
  // amp
  const float           kAmpMax               = 1.0;
  const unsigned int    kAmpRange             = static_cast<int>(2 * kAmpMax);
  //
  const double          kTableLengthFP        = static_cast<double>(kTableLength);
  const unsigned int    kBlockSize            = (4 * kK);
  const double          kPhaseInc             = (kTwoPi / kTableLength);
  const float           kDefaultPulseWidth    = 0.5;
  const double          kEpsilon              = 1.0e-3;
  const float           kPercToDec            = 1.0e-2;   // eg. 56% -> 0.56
  const float           kGlobalVolScale       = 1.0;      // volume scale down multiplier
  const unsigned int    kMidiMaxValue         = 127;
  const unsigned int    kFMmultiplier         = 1000;
  const unsigned int    kAnalogueScale        = (1000);
  // filters
  const ParamValue      kMaximumQ             = 1.0;
  const ParamValue      kMinimumQ             = 0.1;
  const ParamValue      kFiltMaxFreq          = 20000;
  const ParamValue      kFiltMinFreq          = 50;
  // anti-aliasing filter
  const unsigned int    kAntiAliasLowFreq     = 100;
  const unsigned int    kAntiAliasHighFreq    = 15000;
  const float           kAntiAliasQ           = 1.0;
  // delay
  const float           kDelayFilterQ         = kMaximumQ;
  // tail times
  const float           kMaxDelay             = 2.0;
  const float           kMaxRelease           = 5.0;
  // instrument properties
  const float           kMaxTailTime          = kMaxDelay + kMaxRelease;
  const float           kMaxLatency           = 0.0;
  // wavetable harmonics
  const unsigned int    kHarmonics_Saw        = 16;
  const unsigned int    kHarmonics_Tri        = 8;
  const unsigned int    kHarmonics_Square     = 8;

#ifdef UINT32_MAX
  const SampleDuration kSustained             = UINT32_MAX;
#else
  const SampleDuration kSustained             = std::numeric_limits<uint32_t>::max();
#endif

} /* end: namespace hotpants */
#endif /* TYPESCONSTANTS_H_ */
