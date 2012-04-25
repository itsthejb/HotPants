/*
 * TriPartial.hpp
 *
 * Fourier series calculated triangle wave.
 *
 *  Created on: 15 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef TRIPARTIAL_H_
#define TRIPARTIAL_H_

#include "../WaveTableBase.hpp"

namespace hotpants {

  class TriPartial: public WaveTableBase
  {
    public:
      TriPartial();
      eWaveform getWaveForm() const { return kWave_TriPartial; }
  };

} /* end: namespace hotpants */
#endif /* TRIPARTIAL_H_ */
