/*
 * VolumeStereo.hpp
 *
 * Simple output/master volume control unit.
 *
 *  Created on: 27 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef VOLUMECONTROL_H_
#define VOLUMECONTROL_H_

#include "../Interface/Interfaces.hpp"

namespace hotpants {

  class StereoVolume: public ComponentSetup, StereoRenderer
  {
    public:
      explicit  StereoVolume(HotPantsCore& c): ComponentSetup(c) {}
      void      renderStereo(Buffer*, Buffer*, BlockSize);
      void      initialise(SamplingRate r) { _MACRO_SETSAMPLINGRATE_(r); }
  };
}
#endif /* VOLUMECONTROL_H_ */
