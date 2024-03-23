/*
 * TriPartial.cpp
 *
 *  Created on: 15 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include <cmath>
#include "TriPartial.hpp"
#include "../../../Include/Compilation.hpp"
#include "../../../Include/TypesConstants.hpp"

namespace hotpants {

  TriPartial::TriPartial()
  {
#ifdef WTABLE_CONST_HARMONICS
    unsigned int maxHarmonic = kHarmonics_Tri;
#else
    unsigned int maxHarmonic = WaveTableBase::calcMaxHarmonic() / 2;
#endif
    PhaseValue phase = 0.0;
    const double rolloff = 8.0 / std::pow( kPi, 2 );
    double movingAverage = 0.0;
    
    int8_t direction;
    SampleInternal ampVal;

    for(IndexedValue i = 0; i < kTableLength; i++)
    {
      // reset for this sample
      ampVal = 0.0;
      direction = 1;

      /*
       * Triangle wave requires adding of odd harmonics
       * with amplitude decaying as the inverse square of the
       * harmonic number
       * and flipping the sign each time
       */
      for(unsigned int k = 1; k < maxHarmonic; k += 2)
      {
        ampVal += direction * (1.0 / (k * k)) * std::sin(k * phase);
        // flip sign
        direction = -direction;
      }

      // store value
      table[i] = rolloff * ampVal;
      // update moving average
      movingAverage = (ampVal + (i * movingAverage)) / (i + 1);

      phase += kPhaseInc;
    }
    
    // DC offset
    for(IndexedValue i = 0; i < kTableLength; i++) {
      table[i] -= movingAverage;
    }
  }

} /* end: namespace hotpants */
