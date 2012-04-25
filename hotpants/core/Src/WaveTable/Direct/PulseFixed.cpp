/*
 * PulseFixed.cpp
 *
 *  Created on: 14 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "PulseFixed.hpp"
#include "../../../Include/TypesConstants.hpp"

namespace hotpants {

  PulseFixed::PulseFixed()
  {
    PhaseValue	    phaseInc = kTwoPi / kTableLength;
    PhaseValue	    phase    = 0.0;
    SampleInternal	amp      = kAmpMax;

    for(IndexedValue i = 0; i < kTableLength; i++)
    {
      table[i] = amp;
      phase += phaseInc;
      // invert phase after pulse width is reached
      if(amp == kAmpMax && phase > (kDefaultPulseWidth * kTwoPi))
        amp = -kAmpMax;
    }
  }

} /* end: namespace hotpants */
