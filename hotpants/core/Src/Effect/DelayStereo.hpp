/*
 * DelayStereo.hpp
 *
 * Stereo delay unit, comprised of two MonoDelays
 * for each L/R channel, and a low-pass and high-
 * pass filter.
 *
 *  Created on: 26 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef STEREODELAY_H_
#define STEREODELAY_H_

#include "../Interface/Interfaces.hpp"
#include "DelayMono.hpp"

namespace hotpants {

  class DelayStereo: public ComponentSetup, MonoToStereoRenderer
  {
    public:
      explicit          DelayStereo(HotPantsCore&);
      void              initialise(SamplingRate);
      void              renderMonoToStereo(Buffer*, Buffer*, BlockSize);
    protected:
      void              refresh(eRefreshType);
    private:
      DelayMono         delayL, delayR;
      DelayHighPass     highPass;
      DelayLowPass      lowPass;
  };

}
#endif /* STEREODELAY_H_ */
