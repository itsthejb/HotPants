/*
 * AntiAlias.cpp
 *
 *  Created on: 22 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "AntiAlias.hpp"
#include "../../Include/TypesConstants.hpp"

namespace hotpants {

  void AntiAlias::initialise(SamplingRate r)
  {
    _MACRO_SETSAMPLINGRATE_(r);
    lowpass.initialise(r);
    hipass.initialise(r);
    lowpass.recalculate(kFiltType_LP, kAntiAliasHighFreq, kAntiAliasQ, 0.0);
    hipass. recalculate(kFiltType_HP, kAntiAliasLowFreq,  kAntiAliasQ, 0.0);
  }

  void AntiAlias::renderMono(Buffer* b, BlockSize s)
  {
    lowpass.renderMono(b, s);
    hipass. renderMono(b, s);
  }

}
