/*
 * UnitTest.cpp
 *
 * System testing suite
 *
 *  Created on: 11 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifdef UNIT_TEST
#include "UnitTest.hpp"

namespace hotpants {

  void UnitTest::run()
  {
    // local vars
    clock_t begin, end;
    double dur = 0.0;
    unsigned int overloadCount = 0;
    double total = 0.0;
    bool error = false;

    // data
    printf("HotPants Output Test\n");
    printf("--------------------\n");
    printf("Sampling rate = %.2fHz\n", s);
    printf("Wavetable length = %d\n", kTableLength);
    printf("Buffer size = %d\n\n", blockSize);

#ifdef EXPECT_NO_PARAM_CHANGES
    printf("Refresh checking is ON\n");
    printf("There should be no module refresh messages in this test\n\n");
#endif

    // instrument construction
    printf("Constructing instrument...");
    fflush(stdout);
    begin = clock();
    HotPantsCore c;
    printf(" done\n");
    printf("Object size is %lukb\n", sizeof(c) / kK);
    printf("Attempting start note without initialisation... ");
    if(!c.startNote(1, 10, 10)) {
      printf(" operation failed as expected\n");
    } else {
      printf(" ERROR: operation incorrectly succeeded!\n");
      exit(EXIT_FAILURE);
    }

    printf("Initialising instrument at sampling rate %.2f... ", s);
    c.initialise(s);
    end = clock();
    dur = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    printf("done\n");
    printf(">> TIME: %.2e secs\n", dur);

    // generate some notes
    printf("\nStarting and then stopping %d random notes\n", randomNotes);
    printf("Test runs %d times... ", noteCycles);
    fflush(stdout);
    srand(time(NULL));
    begin = clock();
    for(int j = 0; j < noteCycles; ++j)
    {
      // start notes
      for(int i = 0; i < randomNotes; ++i)
      {
        c.startNote(i, randomNote(), rand() % kMidiMaxVelocity);
      }
      // stop notes
      for(int i = 0; i < randomNotes; ++i)
      {
        c.stopNote(i);
      }
    }
    end = clock();
    printf(" done\n");
    // should now be zero active notes
    printf("Should now be ZERO active voices... ");
    fflush(stdout);
    assert(c._countActiveVoices() == 0);
    printf("OK\n");
    dur = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    printf(">> TIME: %.2e secs, %.2e s/note\n", dur, dur/randomNotes/noteCycles);

    if(reinit) {
      // reinitialise the instrument
      printf("\nRe-initialising the instrument at %.2fHz... ", 2*s);
      fflush(stdout);
      c.initialise(2 * s);
      printf("done\n");
    }

    // real notes
    printf("\nStarting buffer output test notes (x %d)... ", randomNotes);
    fflush(stdout);
    for(int i = 0; i < randomNotes; ++i)
    {
      c.startNote(i, randomNote(), rand() % kMidiMaxVelocity);
    }
    printf("done\n");

    printf("Rendering output...");
    float bufferL[blockSize] = { 0.0 };
    float bufferR[blockSize] = { 0.0 };

    c.render(bufferL, bufferR, blockSize);
    printf(" done\n");

    // check the output
    bool output = false;
    for(unsigned int i = 0; i < blockSize; ++i)
    {
      // overload check
      if(bufferL[i] > kAmpMax || bufferR[i] > kAmpMax)
        overloadCount++;

      if(bufferL[i] > 0.0) { output = true; total += bufferL[i]; }
      if(bufferR[i] > 0.0) { output = true; total += bufferR[i]; }
    }

    if(output)
    {
      if(display_buffer) {
        printf("Buffer contents:\n");
        for(unsigned int i = 0; i < blockSize; ++i) {
          printf("%3d :\t%.2e\t\t%.2e\n", i, bufferL[i], bufferR[i]);
        }
      } else {
        printf("Buffer produced output OK (+ve sum %.2e)\n", total);
        if(overloadCount) {
          printf("WARNING: Output produced %d overloaded frames\n", overloadCount);
          error = true;
        }
      }
    } else {
      printf(">> ERROR: NO AUDIBLE OUTPUT PRODUCED! <<\n");
      exit(EXIT_FAILURE);
    }

#ifdef SYNTH_SIMULATION
    int randRange = 10;
    printf("\nStopping all notes...");
    for(int i = 0; i < randomNotes; ++i)
    {
      c.stopNote(i);
    }
    printf("done\n");
#endif

#ifndef SYNTH_SIMULATION
    printf("\nDoing %d silent render cycles and timing, %d active notes... ",
        renderCycles, (int) c._countActiveVoices());
    fflush(stdout);
#else
    printf("\nSynth simulation test:\n----------------------\nDoing %d cycles with random notes and param changes\n", renderCycles);
    printf("Notes active at start of test = %d\n", (int) c._countActiveVoices());
#endif

    /*
     * Main test cycle
     */
    begin = clock();
    for(int i = 0; i < renderCycles; ++i)
    {
#ifdef SYNTH_SIMULATION
      printf("\n>> Cycle %d/%d:\n", i+1, renderCycles);

      // start random notes and set random parameters
      if(randomTime(randRange)) {
        int id = rand() % 10;
        MidiNote note = rand() % std::numeric_limits<uint8_t>::max();
        MidiVelocity v = rand() % kMidiMaxVelocity;
        printf("Trying to start a note with ID %d, Midi note %d, velocity %d... ", id, note, v);
        if(c.startNote(id, note, v))
          printf("OK\n");
        else
          printf("note pitch invalid or ID already active\n");
      }
      if(randomTime(randRange/2)) {
        int id = rand() % 10;
        printf("Trying to stop a note with id %d... ", id);

        if(c.stopNote(id))
          printf("OK\n");
        else
          printf("this ID isn't active\n");
      }
      if(true) {
        // always try parameters
        eParameter p = static_cast<eParameter>(rand() % kNumOfParams);
        const _parameterMap m = c.getParamMap(p);
        ParamValue v = randFPRange(m.maxValue, m.minValue);
        printf("Trying to set parameter %d with value %.2f... ", p, v);
        if(c.setParam(p, v))
          printf("OK\n");
        else
          printf("param invalid or value out of range\n");
      }
#endif

      c.render(bufferL, bufferR, blockSize);
    }

    end = clock();

#ifdef SYNTH_SIMULATION
    printf("\nTest complete.\n");
#else
    printf("Done\n");
#endif

    dur = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    printf("Notes active at end of test = %d\n", (int) c._countActiveVoices());
    printf(">> TIME: %.2e secs, %.2e secs/cycle\n\n", dur, dur/renderCycles);

    if(!error)
      printf("No errors encountered\n");

    printf("\bUnit Test main end\n\n");
    return;
  }
}

int main()
{
  hotpants::UnitTest test;
  test.run();
}

#endif
