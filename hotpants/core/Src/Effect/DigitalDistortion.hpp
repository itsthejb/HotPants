/*
 * DigitalDistortion.hpp
 *
 *  Created on: 22 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef DIGITALDISTORTION_H_
#define DIGITALDISTORTION_H_

#include "../Interface/Interfaces.hpp"

namespace hotpants {

  class DigitalDistortion: public ComponentSetup, MonoRenderer
  {
    public:
      explicit  DigitalDistortion(HotPantsCore& c): ComponentSetup(c) {}
      void      initialise(SamplingRate r) { _MACRO_SETSAMPLINGRATE_(r); }
      void      renderMono(Buffer*, BlockSize);
  };

} /* end namespace hotpants */
#endif /* DIGITALDISTORTION_H_ */
