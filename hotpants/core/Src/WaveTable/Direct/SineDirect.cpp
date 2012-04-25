/*
 * SineDirect.cpp
 *
 *  Created on: 10 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "SineDirect.hpp"
#include <cmath>

namespace hotpants {

  SineDirect::SineDirect()
  {
    PhaseValue phaseInc = kTwoPi / kTableLength;
    PhaseValue phase = 0.0;

    for(IndexedValue i = 0; i < kTableLength; i++) {
      table[i] = std::sin(phase);
      phase += phaseInc;
    }
  }

} /* end: namespace hotpants */
