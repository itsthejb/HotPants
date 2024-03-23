/*
 * SawDirect.hpp
 *
 * Direct calculated saw wave.
 *
 *  Created on: 14 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef SAWDIRECT_H_
#define SAWDIRECT_H_

#include "../WaveTableBase.hpp"

namespace hotpants {

  class SawDirect: public WaveTableBase
  {
    public:
      SawDirect();
      eWaveform getWaveForm() const { return kWave_SawDirect; }
  };

} /* end: namespace hotpants */
#endif /* SAWTABLE1_H_ */
