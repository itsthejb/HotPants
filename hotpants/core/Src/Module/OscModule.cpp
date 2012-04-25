/*
 * OscModule.cpp
 *
 *  Created on: 27 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "OscModule.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../../Include/Enums.hpp"
#include "../Core/HotPantsCore.hpp"

namespace hotpants {
  
  void OscModule::renderMono(Buffer* buffer, BlockSize numFrames)
  {
    // render osc2 before osc1, as it is the osc mod modulator
    // this puts the modulation values in the buffer, ready for use
    osc2.renderMono(buffer, numFrames);
    osc1.renderMono(buffer, numFrames);
    osc3.renderMono(buffer, numFrames);

    // turn down the amp so that a voice is always between
    // +ve kAmpMax & -ve kAmpMax
    for(BlockSize i = 0; i < numFrames; ++i)
      buffer[i] *= 1.0/kNumOfOscs;
  }

  void OscModule::noteOn(MidiNote newNote, MidiVelocity v)
  {
    note = newNote;
    NoteFrequency freq = Utility::midiNoteToFreq(newNote);
    osc1.setFrequency(freq);
    osc2.setFrequency(freq);
    osc3.setFrequency(freq);
  }

  void OscModule::setBend(MidiNote lastNote, SampleDuration portoDur)
  {
    // portamento?
    NoteFrequency freq = Utility::midiNoteToFreq(lastNote);
    assert(freq);
    osc1.setBend(freq, portoDur);
    osc2.setBend(freq, portoDur);
    osc3.setBend(freq, portoDur);
  }

  void OscModule::initialise(SamplingRate r)
  {
    _MACRO_SETSAMPLINGRATE_(r);
    osc1.initialise(r);
    osc2.initialise(r);
    osc3.initialise(r);
  }

} /* end namespace hotpants */

