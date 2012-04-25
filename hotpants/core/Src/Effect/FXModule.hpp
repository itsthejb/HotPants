/*
 * FXModule.hpp
 *
 * Effects module. Contains all available
 * effects devices connected in series from
 * the mixed voice output.
 *
 *  Created on: 9 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef FXSECTION_H_
#define FXSECTION_H_

#include "../Interface/Interfaces.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../Effect/AllEffects.hpp"
#include "../Filter/DCFilter.hpp"
#include "../Filter/AntiAlias.hpp"
#include "../../Include/Compilation.hpp"

namespace hotpants {

  class FXModule: public ComponentSetup, MonoToStereoRenderer
  {
    public:
      explicit            FXModule(HotPantsCore& c);
      void                initialise(SamplingRate);
      virtual void        renderMonoToStereo( Buffer* l,
                                              Buffer* r,
                                              BlockSize s);
    private:
      DigitalDistortion   clipper;
      DelayStereo         delay;
#ifdef SOUND_QUALITY_IN_FX
      AntiAlias           antiAliasFilter;
      DCFilter            dcFilter;
#endif
#ifdef VOL_IN_FXMODULE
      StereoVolume        masterVol;
#endif
  };

}
#endif /* FXSECTION_H_ */
