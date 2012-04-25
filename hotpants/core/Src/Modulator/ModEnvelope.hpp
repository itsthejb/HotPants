/*
 * ModEnvelope.hpp
 *
 * Specialisation of the ADSR envelope for use as a
 * modulation envelope.
 * Could feasibly allow short-circuiting in the same
 * fashion at the LFO. However, due to the logarithmic
 * calculations in the ADSR envelope, this would
 * probably not be of great benefit.
 *
 *  Created on: 12 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef MODENVELOPE_H_
#define MODENVELOPE_H_

#include "../Envelope/ADSRcurve.hpp"

namespace hotpants {

  class ModEnvelope: public ADSRcurve, Modulator
  {
    public:
      explicit        ModEnvelope(HotPantsCore& c): ADSRcurve(c) {}
      SampleInternal  getModValueForBlock(BlockSize);
    private:
      BufferMono      buffer;
  };

}
#endif /* MODENVELOPE_H_ */
