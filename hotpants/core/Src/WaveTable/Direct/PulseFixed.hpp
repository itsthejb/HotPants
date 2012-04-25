/*
 * PulseFixed.hpp
 *
 * Direct calculated pulse wave.
 *
 *  Created on: 14 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef PULSEFIXED_H_
#define PULSEFIXED_H_

#include "../WaveTableBase.hpp"

namespace hotpants {

  class PulseFixed: public WaveTableBase
  {
    public:
      PulseFixed();
      eWaveform getWaveForm() const { return kWave_SquareFixed; }
  };

} /* end: namespace hotpants */
#endif /* PULSETABLE1_H_ */
