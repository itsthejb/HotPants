/*
 * SawDirect.cpp
 *
 * Direct calculation sawtooth wavetable
 *
 *  Created on: 14 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "SawDirect.hpp"

namespace hotpants {

  SawDirect::SawDirect()
  {
    SampleInternal 	ampInc = (2 * kAmpMax) / kTableLength;
    SampleInternal	ampVal = -(2 * kAmpMax);

    for(IndexedValue i = 0; i < kTableLength; i++)
    {
      table[i] = ampVal + kAmpMax;
      ampVal += ampInc;
    }
  }

} /* end: namespace hotpants */
