/*
 * TriDirect.cpp
 *
 *  Created on: 15 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "TriDirect.hpp"

namespace hotpants {

  TriDirect::TriDirect()
  {
    SampleInternal	ampVal = 0;
    SampleInternal	amkPinc = 4.0 / kTableLength;

    for(IndexedValue i = 0; i < kTableLength; i++)
    {
      table[i] = ampVal;

      // switch direction?
      if(ampVal >= kAmpMax || ampVal <= -kAmpMax)
        amkPinc = -amkPinc;

      // update amplitude
      ampVal += amkPinc;
    }
  }

} /* end: namespace hotpants */
