/*
 * SawPartial.cpp
 *
 * Additive synthesis saw wave
 * Sum of all partials up to Nyquist limit
 * for current wavetable size
 *
 *  Created on: 15 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include <cmath>
#include "SawPartial.hpp"
#include "../../../Include/TypesConstants.hpp"
#include "../../../Include/Compilation.hpp"

namespace hotpants {

  SawPartial::SawPartial()
  {
#ifdef WTABLE_CONST_HARMONICS
    unsigned int maxHarmonic = kHarmonics_Saw;
#else
    unsigned int maxHarmonic = WaveTableBase::calcMaxHarmonic();
#endif
    PhaseValue phase = 0.0;
    const double rolloff = kPi / 2;
    double scalingFactor = 0.0;
    SampleInternal ampVal;
    double movingAverage = 0.0;

    for(IndexedValue i = 0; i < kTableLength; i++)
    {
      ampVal = 0.0;

      // sum all harmonics
      for(unsigned int j = 1; j <= maxHarmonic; j++) {
        ampVal -= rolloff * (std::sin(j * phase) / j);
      }

      // adjust scaling factor if necessary
      if(ampVal > scalingFactor) scalingFactor = ampVal;
      // update moving average
      movingAverage = (ampVal + (i * movingAverage)) / (i + 1);

      // store value
      table[i] = ampVal;
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
