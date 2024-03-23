/*
 * FilterModule.cpp
 *
 *  Created on: 6 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "FilterModule.hpp"
#include "../Core/HotPantsCore.hpp"
#include <cassert>
#include <string.h>

namespace hotpants {

  void FilterModule::initialise(SamplingRate r)
  {
    _MACRO_SETSAMPLINGRATE_(r);
    filt1.initialise(r);
    filt2.initialise(r);
  }

  void FilterModule::noteOn(MidiNote note, MidiVelocity velo)
  {
    assert(note);
    NoteFrequency freq = Utility::midiNoteToFreq(note);
    filt1.setKeyTrackNote(freq);
    filt2.setKeyTrackNote(freq);
  }

  void FilterModule::refresh()
  {
    // force filters to recalculate
    filt1.refresh(kFORCE_REFRESH);
    filt1.refresh(kFORCE_REFRESH);

#ifdef CACHE_MODULES
    // settings refreshed
    core.getParamManager().moduleSetClean(eModule_Filt);
#endif
  }

  void FilterModule::renderMono(Buffer* buffer, BlockSize numFrames)
  {
    // get current connection type
    eFilterConnection connect =
        static_cast<eFilterConnection>(core.getParamManager().getValue(kParam_FiltConnect));

    switch(connect)
    {
      case kConnect_Serial:
      {
        filt1.renderMono(buffer, numFrames);
        filt2.renderMono(buffer, numFrames);
      }
        break;
        
      case kConnect_Parallel:
      {
        // parallel filter mix
        // need to make a copy of the input buffer
        // to process separately and then mix together
        BufferUtils::resizeBuffer(filt1buffer, numFrames);
        BufferUtils::resizeBuffer(filt2buffer, numFrames);
        memcpy(&filt1buffer[0], buffer, sizeof(Buffer) * numFrames);
        memcpy(&filt2buffer[0], buffer, sizeof(Buffer) * numFrames);

        // render the filters
        filt1.renderMono(&filt1buffer[0], numFrames);
        filt2.renderMono(&filt2buffer[0], numFrames);

        // get the mix between the two filters
        ParamValue filt2mix = core.getParamManager().getValue(kParam_FiltMix);

        // add and mix the voices
        mixer.addBuffer(&filt1buffer[0], 1.0-filt2mix);
        mixer.addBuffer(&filt2buffer[0], filt2mix);
        mixer.renderMono(buffer, numFrames);
      }
        break;
      default:
        // should not get here
        assert(false);
        break;
    }
  }

} /* end namespace hotpants */
