/*
 * DelayStereo.cpp
 *
 *  Created on: 26 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "DelayStereo.hpp"
#include "../Core/HotPantsCore.hpp"

namespace hotpants {

  DelayStereo::DelayStereo(HotPantsCore& c)
  : ComponentSetup(c), delayL(c, kDelayMap[kDelayChannel_Left]),
    delayR(c, kDelayMap[kDelayChannel_Right]), highPass(c), lowPass(c) { }

  void DelayStereo::initialise(SamplingRate r)
  {
    _MACRO_SETSAMPLINGRATE_(r);
    delayL.initialise(r);
    delayR.initialise(r);
    highPass.initialise(r);
    lowPass.initialise(r);
    // clear the queue
    refresh(kFORCE_REFRESH);
  }

  void DelayStereo::refresh(eRefreshType force)
  {
    delayL.refresh(force);
    delayR.refresh(force);
    highPass.refresh(force);
    lowPass.refresh(force);
  }

  void DelayStereo::renderMonoToStereo(Buffer* lIn,
                                       Buffer* rIn,
                                       BlockSize s)
  {
    // refresh components
    refresh(kCHECK_FOR_UPDATES);

    // the input is mono - left channel only
    BufferMono& lOut = delayL.getDelayBuffer(lIn, s);
    BufferMono& rOut = delayR.getDelayBuffer(lIn, s);

    // filter
    lowPass.renderStereo (&lOut[0], &rOut[0], s);
    highPass.renderStereo(&lOut[0], &rOut[0], s);

    // calculate mix settings
    ParamValue leftWet  = core.getParamManager().getValue(kParam_DelayL_Mix) * kPercToDec;
    ParamValue leftDry  = 1.0 - leftWet;
    ParamValue rightWet = core.getParamManager().getValue(kParam_DelayR_Mix) * kPercToDec;
    ParamValue rightDry = 1.0 - rightWet;

    // mix the output
    SampleExternal sample;
    for(BlockSize i = 0; i < s; ++i)
    {
      // temporarily store the input sample
      sample = lIn[i];
      // mix and write to left and right output channels
      lIn[i] = (leftWet  * lOut[i]) + (leftDry  * sample);
      rIn[i] = (rightWet * rOut[i]) + (rightDry * sample);
    }
  }

}
