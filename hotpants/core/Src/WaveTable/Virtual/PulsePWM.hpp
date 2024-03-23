/*
 * PulsePWM.hpp
 *
 * Virtual pulse wave with width modulation wavetable.
 * Requested index is used to derive the correct +ve/-ve
 * sample, with reference to the current pulse width
 * from the core's parameter manager.
 *
 *  Created on: 14 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef PULSEPWM_H_
#define PULSEPWM_H_

#include "../../WaveTable/WaveTableBase.hpp"
#include "../../Core/HotPantsCore.hpp"

namespace hotpants {

  class PulsePWM: public WaveTableBase, Component
  {
    public:
      explicit          PulsePWM(HotPantsCore&);
      SampleInternal    getFrameAtIndex(IndexedValue) const;
      eWaveform         getWaveForm() const { return kWave_PulsePWM; }
    private:
      mutable double    pulseWidthIndex;
      void              calcPulseWidth() const;
  };

  inline void PulsePWM::calcPulseWidth() const
  {
    pulseWidthIndex = core.getParamManager().getValue(kParam_PulseWidth) * kPercToDec * kTableLength;
  }

} /* end: namespace hotpants */
#endif /* PULSEPWM_H_ */
