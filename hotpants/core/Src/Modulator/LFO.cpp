/*
 * LFO.cpp
 *
 *  Created on: 18 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "LFO.hpp"
#include "../Core/HotPantsCore.hpp"
#include "../WaveTable/WaveTableBase.hpp"
#include "../../Include/Compilation.hpp"

namespace hotpants {

  LFO::LFO(HotPantsCore& c): OscillatorBase(c) { }

  void LFO::initialise(SamplingRate r)
  {
    OscillatorBase::initialise(r);
    refresh(kFORCE_REFRESH);
    getNoiseSample();
  }

  void LFO::refresh(eRefreshType force)
  {
    assert(samplingRate && tableFreq);
    _MACRO_GET_AMP_WAVE_
    // refresh local tuning
    if(force || core.getParamManager().paramModified(getThisOsc().tuning))
    {
#ifdef EXPECT_NO_PARAM_CHANGES
      if(!force)
        fprintf(stderr, "LFO::refresh() - parameter refresh when unexpected and unforced!\n");
#endif
      frequency = core.getParamManager().getValue(getThisOsc().tuning);
      calcIndexInc();
    }
  }

  SampleInternal LFO::getModValueForBlock(BlockSize blockSize)
  {
    // refresh values used during the render cycle
    refresh(kCHECK_FOR_UPDATES);

    // hold the sample with S&H
    if(static_cast<eLFOwaveForm>(
        core.getParamManager().getValue(getThisOsc().wave)) != kLFOwave_SandH)
    {
      sample = wavetables->
                getFrameFromTableAtIndex(wave,static_cast<IndexedValue>(indexFP));
    }

    /*
     * The LFO can get the first sample, and skip forward to
     * the end of the block
     */
    indexFP += indexInc * blockSize * tuningScale;

    // reset phase if necessary
    while(indexFP >= kTableLength)
    {
      indexFP -= kTableLength;
      if(static_cast<eLFOwaveForm>(
          core.getParamManager().getValue(getThisOsc().wave)) == kLFOwave_SandH) {
        getNoiseSample();
      }
    }
    return sample * amp * kPercToDec;
  }

}
