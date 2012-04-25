/*
 * AmpModule.cpp
 *
 *  Created on: 6 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "AmpModule.hpp"
#include "../Envelope/ADSRcurve.hpp"
#include "../Core/HotPantsCore.hpp"
#include "../Core/ParameterManager.hpp"

namespace hotpants {

  void AmpModule::initialise(SamplingRate r)
  {
    _MACRO_SETSAMPLINGRATE_(r);
    ampEnvelope.initialise(r);
  }

  void AmpModule::refresh()
  {
    ParameterManager& p = core.getParamManager();
    ADSRcurveParams newEnv(p.getValue(kParam_AmpAttack),
                           p.getValue(kParam_AmpDecay),
                           p.getValue(kParam_AmpSustain),
                           p.getValue(kParam_AmpRelease),
                           p.getValue(kParam_AmpScaling));
    ampEnvelope.createEnvelope(newEnv);

#ifdef CACHE_MODULES
    // settings refreshed
    core.getParamManager().moduleSetClean(eModule_Amp);
#endif
  }

  void AmpModule::noteOn(MidiNote note, MidiVelocity velo)
  {
    // calculate velocity
    velocityScale = std::pow(static_cast<double>(velo)/kMidiMaxVelocity,
                             static_cast<double>(core.getParamManager().getValue(kParam_Velocity))/20);
  }

  void AmpModule::renderMono(Buffer* buffer, BlockSize numFrames)
  {
    ampEnvelope.renderMono(buffer, numFrames);
#ifdef SCALE_DOWN_OSCS
    // apply overall volume scaling
    for(BlockSize i = 0; i < numFrames; ++i)
      buffer[i] *= velocityScale;
#endif
  }
}
