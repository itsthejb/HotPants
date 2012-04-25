/*
 * SquarePartial.cpp
 *
 *  Created on: 15 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include <cmath>
#include "SquarePartial.hpp"
#include "../../../Include/Compilation.hpp"
#include "../../../Include/TypesConstants.hpp"

namespace hotpants {

  SquarePartial::SquarePartial()
  {
#ifdef WTABLE_CONST_HARMONICS
    unsigned int maxHarmonic = kHarmonics_Square;
#else
    unsigned int maxHarmonic = WaveTableBase::calcMaxHarmonic() / 2;
#endif
    PhaseValue phase = 0.0;
    double scalingFactor = 0.0;
    double movingAverage = 0.0;
    
    SampleInternal ampVal;

    for(IndexedValue i = 0; i < kTableLength; i++)
    {
      // reset for this sample
      ampVal = 0.0;

      // sum odd harmonics
      for(unsigned int j = 1; j <= maxHarmonic; j += 2) {
        ampVal += std::sin(j * phase) / j;
      }

      // store value
      table[i] = ampVal;
      // update moving average
      movingAverage = (ampVal + (i * movingAverage)) / (i + 1);

      // check for scaling factor
      if(ampVal > scalingFactor) scalingFactor = ampVal;

      phase += kPhaseInc;
    }
    
    /*
     * go back over the table and rescale to +/- 1.0
     * using scalingFactor
     */
    for(IndexedValue i = 0; i < kTableLength; i++) {
      table[i] /= scalingFactor;
      table[i] -= movingAverage;
    }
  }

} /* end: namespace hotpants */
