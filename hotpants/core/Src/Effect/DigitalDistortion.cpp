/*
 * DigitalDistortion.cpp
 *
 *  Created on: 22 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "DigitalDistortion.hpp"
#include "../Core/HotPantsCore.hpp"
#include "../Utility/Utility.hpp"
#include <cmath>

namespace hotpants {

  void DigitalDistortion::renderMono(Buffer* buffer, BlockSize numFrames)
  {
    ParamValue gain = core.getParamManager().getValue(kParam_DistortGain);
    double ratio  = Utility::dBGainToPower(gain);
    // make up gain reduction maintains the same overall volume
    double makeUp = 1.0/gain;
    eDistortionType e = static_cast<eDistortionType>(core.getParamManager().getValue(kParam_DistortType));

    switch(e)
    {
      // hard clipping
      case kDistortion_HardC:
      {
        for(BlockSize i = 0; i < numFrames; ++i) {
          // amplify
          buffer[i] *= ratio;
          // limit
          if(buffer[i] >  kAmpMax) buffer[i] =  kAmpMax;
          if(buffer[i] < -kAmpMax) buffer[i] = -kAmpMax;
          // make up gain
          buffer[i] *= makeUp;
        }
      }
        break;

      // fold-back
      case kDistortion_FoldBack:
      {
        for(BlockSize i = 0; i < numFrames; ++i) {
          // amplify
          buffer[i] *= ratio;
          // limit
          if(buffer[i] >  kAmpMax) buffer[i] -= kAmpMax;
          if(buffer[i] < -kAmpMax) buffer[i] += kAmpMax;
          // make up gain
          buffer[i] *= makeUp;
        }
      }
      case kDistortion_Off:
        // clipping off
        break;
      default:
        // should never get here!
        assert(false);
        break;
    }
  }
}
