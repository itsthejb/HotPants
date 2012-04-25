/*
 * VolumeControl.cpp
 *
 *  Created on: 27 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "VolumeStereo.hpp"
#include "../Core/HotPantsCore.hpp"

namespace hotpants {

  void StereoVolume::renderStereo(Buffer* l, Buffer* r, BlockSize s)
  {
    ParamValue masterVol = core.getParamManager().getValue(kParam_GlobalVolume);
    for(BlockSize i = 0; i < s; ++i) { l[i] *= masterVol; r[i] *= masterVol; }
  }

}
