/*
 * AudioOsc.cpp
 *
 *  Created on: 20 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "AudioOsc.hpp"
#include "../../Include/Enums.hpp"
#include "../Core/HotPantsCore.hpp"
#include "../../Include/Compilation.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define _MACRO_CALC_GLOBAL_TUNING_ {                                                             \
  analogueRandom = (core.getParamManager().getValue(kParam_OscAnalogue) / kAnalogueScale)        \
                   * ((rand() / static_cast<double>(RAND_MAX / kAmpRange) - kAmpMax));           \
  globalTuning = tuningScale * (core.getParamManager().getGlobalTuningScale() + analogueRandom);}\
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace hotpants {

  void AudioOsc::refresh(eRefreshType force)
  {
    OscillatorBase::refresh(force);
    _MACRO_CALC_GLOBAL_TUNING_
  }

  // Oscillator 2 also has a fine tuning control
  void Osc2::refresh(eRefreshType force)
  {
    assert(samplingRate && tableFreq);
    _MACRO_GET_AMP_WAVE_

    // refresh local tuning
    if(force ||
       core.getParamManager().paramModified(kParam_Osc2Tuning) ||
       core.getParamManager().paramModified(kParam_Osc2Fine))
    {
#ifdef EXPECT_NO_PARAM_CHANGES
      if(!force)
        fprintf(stderr, "Osc2::refresh() - parameter refresh when unexpected and unforced!\n");
#endif

      tuningScale = Utility::calcTuning(
                    core.getParamManager().getValue(kParam_Osc2Tuning) +
                   (core.getParamManager().getValue(kParam_Osc2Fine) * kPercToDec) );
      // calculate table index increment
      calcIndexInc();
    }
    // global tuning and analogue
    _MACRO_CALC_GLOBAL_TUNING_
  }

  void AudioOsc::setFrequency(NoteFrequency freqIn)
  {
    assert(freqIn > 0.0);
    frequency = freqIn;
    // be sure to reset portamento values here
    indexFP = 0.0, portoCounter = 0, portoDuration = 0;
    refresh(kFORCE_REFRESH);
  }

  void AudioOsc::setBend(NoteFrequency startNote, SampleDuration durationIn)
  {
    // pitch increase/decrease in Hz for each sample
    assert(durationIn);
    portoDuration = durationIn;
    indexInc      = tableFreq * startNote * tuningScale;
    portoIndexInc = ((frequency - startNote) / portoDuration) * tableFreq;
  }

  /*
   * Normal audio oscillator rendering
   */
  void AudioOsc::renderMono(Buffer* buffer, BlockSize numFrames)
  {
    // refresh values used during the render cycle
    refresh(kCHECK_FOR_UPDATES);
    // write to buffer
    for(BlockSize i = 0; i < numFrames; ++i) {
      getNextSample();
      advanceFrames(0.0);
      buffer[i] += (sample * amp);
    }
  }

  void Osc1::renderFM(Buffer* buffer, BlockSize numFrames)
  {
    // refresh render cycle data
    refresh(kCHECK_FOR_UPDATES);
    // write to buffer
    for(BlockSize i = 0; i < numFrames; ++i) {
      getNextSample();
      // frequency modulation
      advanceFrames(buffer[i] * kFMmultiplier);
      // overwrite the modulator
      buffer[i] = (sample * amp);
    }
  }

  void Osc1::renderAM(Buffer* buffer, BlockSize numFrames)
  {
    // refresh render cycle data
    refresh(kCHECK_FOR_UPDATES);
    // write to buffer
    for(BlockSize i = 0; i < numFrames; ++i) {
      getNextSample();
      advanceFrames(0.0);
      // AM modulation - unipolar multiplication
      buffer[i] *= (sample + kAmpMax) * amp;
    }
  }

  void Osc1::renderRM(Buffer* buffer, BlockSize numFrames)
  {
    // refresh render cycle data
    refresh(kCHECK_FOR_UPDATES);
    // write to buffer
    for(BlockSize i = 0; i < numFrames; ++i) {
      getNextSample();
      advanceFrames(0.0);
      // ring modulation - straight signal multiplication
      buffer[i] *= sample * amp;
    }
  }

  void Osc1::renderMono(Buffer* b, BlockSize n)
  {
    // oscillator modulations
    switch(static_cast<eOscMod>(core.getParamManager().getValue(kParam_OscMod)))
    {
      case kOscMod_None:
        { AudioOsc::renderMono(b, n); return; }
      case kOscMod_RM:
        { renderRM(b, n);              return; }
      case kOscMod_AM:
        { renderAM(b, n);              return; }
      case kOscMod_FM:
        { renderFM(b, n);              return; }
      default:
        // should never get here
        assert(false);
        return;
    }
  }

}
