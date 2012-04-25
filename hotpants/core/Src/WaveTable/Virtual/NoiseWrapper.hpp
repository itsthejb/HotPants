/*
 * NoiseWrapper.hpp
 *
 * Wrapper for a noise object, with required
 * getFrameAtIndex() method to allow use as a
 * wavetable.
 *
 *  Created on: 15 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef NOISEWRAPPER_H_
#define NOISEWRAPPER_H_

#include "../WaveTableBase.hpp"
#include "../../Generator/Noise.hpp"

namespace hotpants {

  class NoiseWrapper: public WaveTableBase
  {
    public:
      eWaveform       getWaveForm() const                 { return kWave_Noise; }
      SampleInternal  getFrameAtIndex(IndexedValue) const { return osc.getNextSample(); }
    private:
      Noise           osc;
  };

} /* end: namespace hotpants */
#endif /* NOISE1_H_ */
