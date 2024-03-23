/*
 * UnitTest.hpp
 *
 * Unit Testing class, friend of HotPantsCore,
 * allows full public access for testing purposes.
 * Any testing code can go in the UnitTest::run()
 * function.
 *
 *  Created on: 11 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifdef UNIT_TEST
#ifndef UNITTEST_H_
#define UNITTEST_H_

#include "CoreInclude.hpp"
#include <cstdlib>
#include <cstdio>

// testing constants
const hotpants::SamplingRate s = 4096.0;
const unsigned int blockSize = 64;            // rendering block size
const bool display_buffer = true;             // print the buffer's contents?
const bool reinit = true;                     // reinitialise with a new sampling rate?
const int randomNotes = hotpants::kMaxActive; // number of notes to generate

// Testing defines
#define SYNTH_SIMULATION                      // simulates normal synth operation
#define TEST_NOTEON                           // run large number of note on/off
#define TEST_RENDER                           // run large number of render cycles
#ifndef SYNTH_SIMULATION                      // not compatible with simulation:
  #define EXPECT_NO_PARAM_CHANGES             // ... so report if there are any refreshes
#endif

#ifdef SYNTH_SIMULATION
  #include <limits>
#endif

#ifdef TEST_NOTEON
  const int noteCycles = 100000;
#else
  const int noteCycles = 1;
#endif
#ifdef SYNTH_SIMULATION
  const int renderCycles = 100;
#else
#ifdef TEST_RENDER
  const int renderCycles = 100000;
#else
  const int renderCycles = 1;
#endif
#endif

namespace hotpants {
  // testing class
  class UnitTest {
    public:
      void run();
    private:
      MidiNote  randomNote() { return (rand() % kMidiNumOfNotes) + kMidiNoteMin; }
      bool      randomTime(int r) { return true; /*return (rand() % r == 0);*/ }
      double    randFPRange(double max, double min)
      {
        assert(max > min);
        return static_cast<double>(
            rand() % static_cast<int>(std::abs((int) max) + std::abs((int) min) * 100))
            / 100 - std::abs((int) min
          );
      }
  };
}
#endif /* UNITTEST_H_ */
#endif
