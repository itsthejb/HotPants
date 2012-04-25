/*
 * TriDirect.hpp
 *
 * Direct calculated triangle wave.
 *
 *  Created on: 15 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef TRIDIRECT_H_
#define TRIDIRECT_H_

#include "../WaveTableBase.hpp"

namespace hotpants {

  class TriDirect: public WaveTableBase
  {
    public:
      TriDirect();
      eWaveform getWaveForm() const { return kWave_TriDirect; }
  };

} /* end: namespace hotpants */
#endif /* TRIANGLEDIRECT_H_ */
