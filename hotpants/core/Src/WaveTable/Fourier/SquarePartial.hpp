/*
 * SquarePartial.hpp
 *
 * Fourier series calculated square wave.
 *
 *  Created on: 15 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef SQUAREPARTIAL_H_
#define SQUAREPARTIAL_H_

#include "../WaveTableBase.hpp"

namespace hotpants {

  class SquarePartial: public WaveTableBase
  {
    public:
      SquarePartial();
      eWaveform getWaveForm() const { return kWave_SquareFixed; }
  };

} /* end: namespace hotpants */
#endif /* SQUAREPARTIAL_H_ */
