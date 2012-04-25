/*
 * ModModule.cpp
 *
 *  Created on: 6 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "ModModule.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../Core/HotPantsCore.hpp"
#include "../../Include/ParamTypes.hpp"
#include "../Utility/Utility.hpp"

namespace hotpants {

  ModModule::ModModule(HotPantsCore& c)
  : ComponentSetup(c), lfo1(c), lfo2(c),
    env1(c), env2(c), veloMod(0.0) { }

  void ModModule::initialise(SamplingRate r)
  {
    _MACRO_SETSAMPLINGRATE_(r);
    lfo1.initialise(r);
    lfo2.initialise(r);
    env1.initialise(r);
    env2.initialise(r);
  }

  void ModModule::refresh()
  {
    // refresh lfos
    lfo1.refresh(kFORCE_REFRESH);
    lfo2.refresh(kFORCE_REFRESH);

    // both envelopes have 50% scaling - not selectable
    ParameterManager& p = core.getParamManager();
    // envelope1 is full ADSR
    ADSRcurveParams env1Param( p.getValue(kParam_Env1Attack),
                               p.getValue(kParam_Env1Decay),
                               p.getValue(kParam_Env1Sustain),
                               p.getValue(kParam_Env1Release),
                               50.0);
    // envelope2 is AD-only
    ADSRcurveParams env2Param( p.getValue(kParam_Env2Attack),
                               p.getValue(kParam_Env2Decay),
                               0.0, 0.0, 50.0);
    env1.createEnvelope(env1Param);
    env2.createEnvelope(env2Param);

#ifdef CACHE_MODULES
    // settings refreshed
    p.moduleSetClean(eModule_Mod);
#endif
  }

  void ModModule::noteOn(MidiNote n, MidiVelocity v) { veloMod = Utility::midiControlToFloat(v); }

  void ModModule::processBlock(BlockSize numFrames)
  {
    ParameterManager& parameters = core.getParamManager();
    SampleInternal modValue;
    // LFO1
    modValue = lfo1.getModValueForBlock(numFrames);
    parameters.setMod(kParam_LFO1Target, modValue);
    // LFO2
    modValue = lfo2.getModValueForBlock(numFrames);
    parameters.setMod(kParam_LFO2Target, modValue);
    // Envelope 1
    modValue = env1.getModValueForBlock(numFrames);
    parameters.setMod(kParam_Env1Target, parameters.getValue(kParam_Env1Amount) * modValue * kPercToDec);
    // Envelop 2
    modValue = env2.getModValueForBlock(numFrames);
    parameters.setMod(kParam_Env2Target, parameters.getValue(kParam_Env2Amount) * modValue * kPercToDec);
    // note velocity
    parameters.setMod(kParam_VeloTarget, parameters.getValue(kParam_VeloAmount) * veloMod  * kPercToDec);
  }

}
