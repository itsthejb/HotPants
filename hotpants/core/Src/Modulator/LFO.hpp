/*
 * LFO.hpp
 *
 * Base class, and concrete classes for low-frequency
 * oscillators, used as modulation control sources.
 *
 * The LFO class takes advantage of some short-circuiting,
 * meaning on the first sample of a block need be
 * calculated.
 * The cycleComplete() method is used by the sample
 * and hold type, getting a fresh noise sample at the
 * start of each cycle.
 *
 *  Created on: 8 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef LFO_H_
#define LFO_H_

#include "../Interface/Interfaces.hpp"
#include "../Generator/Noise.hpp"
#include "../Oscillator/OscillatorBase.hpp"
#include "../../Include/ParamMaps.hpp"
#include <cstdlib>
#include <ctime>

namespace hotpants {

  class LFO: public OscillatorBase, Modulator
  {
    public:
      explicit        LFO(HotPantsCore&);
      SampleInternal  getModValueForBlock(BlockSize);
      void            initialise(SamplingRate);
      void            refresh(eRefreshType);
    protected:
      void            getNoiseSample() { sample = (noise.getNextSample()); }
      void            advanceFrames(IndexedValue n, IndexFPValue i) {}
    private:
      // sample-and-hold noise source
      Noise           noise;
  };

  // concrete classes for built-in LFOs

  class LFO1: public LFO {
    public:
      explicit         LFO1(HotPantsCore& c): LFO(c) {}
    private:
      const _oscMap&   getThisOsc() const { return kOscMap[kLFO1]; }
  };

  class LFO2: public LFO {
    public:
      explicit         LFO2(HotPantsCore& c): LFO(c) {}
    private:
      const _oscMap&   getThisOsc() const { return kOscMap[kLFO2]; }
  };

}
#endif /* LFO_H_ */
