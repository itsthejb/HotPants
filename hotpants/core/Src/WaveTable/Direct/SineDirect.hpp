/*
 * SineDirect.hpp
 *
 * Direct calculated sine wave.
 *
 *  Created on: 10 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef SINETEST_H_
#define SINETEST_H_

#include "../WaveTableBase.hpp"

namespace hotpants
{
  class SineDirect: public WaveTableBase
  {
    public:
      SineDirect();
      eWaveform getWaveForm() const { return kWave_SineDirect; }
  };

} /* end: namespace hotpants */
#endif /* SINETEST_H_ */
