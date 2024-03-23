/*
 * DelayMono.cpp
 *
 *  Created on: 17 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "DelayMono.hpp"
#include "../Core/HotPantsCore.hpp"
#include "../Utility/Utility.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../../Include/Compilation.hpp"

namespace hotpants {

  void DelayMono::initialise(SamplingRate r)
  {
    _MACRO_SETSAMPLINGRATE_(r);
    BufferUtils::wipeBuffer(output);
    refresh(kFORCE_REFRESH);
  }

  void DelayMono::refresh(eRefreshType force)
  {
    // resize buffer?
    if(force || core.getParamManager().paramModified(thisChannel.time))
    {
#ifdef EXPECT_NO_PARAM_CHANGES
      if(!force)
        fprintf(stderr, "DelayMono::refresh() - parameter refresh when unexpected and unforced!\n");
#endif

      BufferUtils::resizeBuffer(delayBuffer, static_cast<BlockSize>(
          core.getParamManager().getValue(thisChannel.time) * samplingRate));
    }
  }

  BufferMono& DelayMono::getDelayBuffer(Buffer const* inBuffer, BlockSize numFrames)
  {
    // refresh settings
    refresh(kCHECK_FOR_UPDATES);
    // ensure mixbuffer is large enough
    output.resize(numFrames);

    ParamValue feedback = core.getParamManager().getValue(thisChannel.feedback) * kPercToDec;

    // push whole input onto delay
    SampleInternal front;
    for(BlockSize i = 0; i < numFrames; ++i) {
      front = delayBuffer.front();
      output[i] = front;
      delayBuffer.pop();
      delayBuffer.push(inBuffer[i] + (front * feedback));
    }

    return output;
  }
}
