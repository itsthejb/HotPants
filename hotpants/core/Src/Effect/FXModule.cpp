/*
 * FXModule.cpp
 *
 *  Created on: 9 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "FXModule.hpp"
#include "../Core/HotPantsCore.hpp"
#include "../../Include/Compilation.hpp"

namespace hotpants {

  FXModule::FXModule(HotPantsCore& c)
  : ComponentSetup(c), clipper(c), delay(c),
#ifdef SOUND_QUALITY_IN_FX
    antiAliasFilter(c), dcFilter(c),
#endif
#ifdef VOL_IN_FXMODULE
    masterVol(c)
#endif
  { }

  void FXModule::initialise(SamplingRate r)
  {
    _MACRO_SETSAMPLINGRATE_(r);
    // clipper doesn't require initialisation
    delay.initialise(r);
#ifdef SOUND_QUALITY_IN_FX
    antiAliasFilter.initialise(r);
    dcFilter.initialise(r);
#endif
  }

  void FXModule::renderMonoToStereo(Buffer* l,Buffer* r,BlockSize s)
  {
    // digital distortion
    clipper.renderMono(l, s);
#ifdef SOUND_QUALITY_IN_FX
    // sound quality filtering
    antiAliasFilter.renderMono(l, s);
    dcFilter.renderMono(l, s);
#endif
    delay.renderMonoToStereo(l, r, s);
#ifdef VOL_IN_FXMODULE
    masterVol.renderStereo(l, r, s);
#endif
  }

}
