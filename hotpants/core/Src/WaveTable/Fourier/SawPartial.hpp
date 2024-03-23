/*
 * SawPartial.hpp
 *
 * Fourier series calculated saw wave.
 *
 *  Created on: 15 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef SAWPARTIAL_H_
#define SAWPARTIAL_H_

#include "../WaveTableBase.hpp"

namespace hotpants {

  class SawPartial: public WaveTableBase
  {
    public:
      SawPartial();
      eWaveform getWaveForm() const { return kWave_SawPartial; }
  };

} /* end: namespace hotpants */
#endif /* SAWPARTIAL_H_ */
