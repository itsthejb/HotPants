/*
 * DCFilter.hpp
 *
 * This is based on code found in the document:
 * "Introduction to Digital Filters"
 * Julius O. Smith III (jos@ccrma.stanford.edu)
 * (http://www-ccrma.stanford.edu/~jos/filters/)
 *
 *  Created on: 8 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef DCFILTER_H_
#define DCFILTER_H_

#include "../Interface/Interfaces.hpp"
#include "../../Include/TypesConstants.hpp"

namespace hotpants {

  class DCFilter: public ComponentSetup, MonoRenderer
  {
    public:
      explicit              DCFilter(HotPantsCore& c): ComponentSetup(c),
                              delayIn(0.0), delayOut(0.0), R(0.0) { }
      void                  initialise(SamplingRate r) { _MACRO_SETSAMPLINGRATE_(r);
                                                         R = 1.0-(2.0*kPi*DCFreq/r); }
      void                  renderMono(Buffer*, BlockSize);
    private:
      SampleExternal        delayIn;
      SampleExternal        delayOut;
      float                 R;
      static const float    DCFreq;
  };

}
#endif /* DCFILTER_H_ */
