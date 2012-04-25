/*
 * PulsePWM.cpp
 *
 *  Created on: 14 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "PulsePWM.hpp"
#include "../../Core/HotPantsCore.hpp"

namespace hotpants {

  PulsePWM::PulsePWM(HotPantsCore& c): Component(c) { calcPulseWidth(); }

  SampleInternal PulsePWM::getFrameAtIndex(IndexedValue index) const
  {
    if(core.getParamManager().paramModified(kParam_PulseWidth))
      calcPulseWidth();
    // calculate amp from requested table pos
    if(index <= pulseWidthIndex)
      return kAmpMax;
    else
      return -kAmpMax;
  }

} /* end: namespace hotpants */
