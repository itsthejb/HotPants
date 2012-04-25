/*
 * ParamDefaults.hpp
 *
 * Full static parameter definition map. This is cloned on creation of
 * a ParameterArray object.
 *
 *  Created on: 24 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef DEFAULTS_H_
#define DEFAULTS_H_

#include "../Src/Core/ParameterArray.hpp"

namespace hotpants {

  const _parameterMap ParameterArray::kDefaultParameters[kNumOfParams] = {
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // ParameterManager parameter map
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Enum Value         | Def             | Max               | Min             | Unit          | Flag    | Module        | Conf. settings
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  { kParam_AmpAttack,     0.1,              5.0,                0.01,             kUnit_Secs,     kFrt2,    eModule_Amp,    Z,Z,Z,F,F,F },
  { kParam_AmpDecay,      0.5,              5.0,                0.01,             kUnit_Secs,     kFrt2,    eModule_Amp,    Z,Z,Z,F,F,F },
  { kParam_AmpSustain,    75,               100,                0,                kUnit_Perc,     kFrt2,    eModule_Amp,    Z,Z,Z,F,F,F },
  { kParam_AmpRelease,    0.25,             kMaxRelease,        0.01,             kUnit_Secs,     kFrt2,    eModule_Amp,    Z,Z,Z,F,F,F },
  { kParam_AmpScaling,    50,               100,                0.01,             kUnit_Perc,     kFrt2,    eModule_Amp,    Z,Z,Z,F,F,F },
  { kParam_Velocity,      0,                100,                0,                kUnit_Perc,     kFrt2,    eModule_None,   Z,Z,Z,F,F,F },
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  { kParam_Osc1Wave,      kWave_SineDirect, kNumOfOscWaves-1,   kWave_SineDirect, kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_Osc1Tuning,    0.0,              36.0,               -36.0,            kUnit_ST,       kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_Osc1Amp,       0.6,              1.0,                0.0,              kUnit_Gain,     kFrt2,    eModule_None,   Z,Z,Z,F,T,F },
  { kParam_Osc2Wave,      kWave_SineDirect, kNumOfOscWaves-1,   kWave_SineDirect, kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_Osc2Tuning,    0.0,              36.0,               -36.0,            kUnit_ST,       kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_Osc2Fine,      0,                100,                -100,             kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_OscMod,        kOscMod_None,     kNumOfOscMods-1,    kOscMod_None,     kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_Osc2Amp,       0.0,              1.0,                0.0,              kUnit_Gain,     kFrt2,    eModule_None,   Z,Z,Z,F,T,F },
  { kParam_Osc3Wave,      kWave_SineDirect, kNumOfOscWaves-1,   kWave_SineDirect, kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_Osc3Tuning,    0.0,              36.0,               -36.0,            kUnit_ST,       kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_Osc3Amp,       0.0,              1.0,                0.0,              kUnit_Gain,     kFrt2,    eModule_None,   Z,Z,Z,F,T,F },
  { kParam_OscAnalogue,   0,                100,                0,                kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_PulseWidth,    50,               100,                0,                kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  { kParam_Filt1Type,     kFiltType_Off,    kNumOfFiltTypes-1,  kFiltType_Off,    kUnit_Index,    kFnone,   eModule_Filt,   Z,Z,Z,F,F,F },
  { kParam_Filt1Cutoff,   5000,             kFiltMaxFreq,       kFiltMinFreq,     kUnit_Hz,       kFrt3,    eModule_Filt,   Z,Z,Z,F,T,F },
  { kParam_Filt1Q,        kMinimumQ,        kMaximumQ,          kMinimumQ,        kUnit_Generic,  kFnone,   eModule_Filt,   Z,Z,Z,F,T,F },
  { kParam_Filt1EQGain,   -3.0,             24.0,               -48.0,            kUnit_Gain,     kFrt2,    eModule_Filt,   Z,Z,Z,F,T,F },
  { kParam_Filt2Type,     kFiltType_Off,    kNumOfFiltTypes-1,  kFiltType_Off,    kUnit_Index,    kFnone,   eModule_Filt,   Z,Z,Z,F,F,F },
  { kParam_Filt2Cutoff,   5000,             kFiltMaxFreq,       kFiltMinFreq,     kUnit_Hz,       kFrt3,    eModule_Filt,   Z,Z,Z,F,T,F },
  { kParam_Filt2Q,        kMinimumQ,        kMaximumQ,          kMinimumQ,        kUnit_Generic,  kFnone,   eModule_Filt,   Z,Z,Z,F,T,F },
  { kParam_Filt2EQGain,   -3.0,             24.0,               -48.0,            kUnit_Gain,     kFrt2,    eModule_Filt,   Z,Z,Z,F,T,F },
  { kParam_FiltConnect,   kConnect_Serial,  kConnect_Parallel,  kConnect_Serial,  kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_FiltMix,       0.5,              1.0,                0.0,              kUnit_Generic,  kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_FiltKeyTrack,  0,                200,                0,                kUnit_Perc,     kFnone,   eModule_Filt,   Z,Z,Z,F,T,F },
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Mod Section
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  { kParam_LFO1Target,    eModT_None,       kNumOfModTargets-1, eModT_None,       kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_LFO1Wave,      kLFOwave_Sine,    kNumOfLFOwaves-1,   kLFOwave_Sine,    kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_LFO1Rate,      2,                70,                 0.1,              kUnit_Hz,       kFrt3,    eModule_Mod,    Z,Z,Z,F,T,F },
  { kParam_LFO1Amount,    1,                100,                0,                kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_LFO2Target,    eModT_None,       kNumOfModTargets-1, eModT_None,       kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_LFO2Wave,      kLFOwave_Sine,    kNumOfLFOwaves-1,   kLFOwave_Sine,    kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_LFO2Rate,      2,                70,                 0.1,              kUnit_Hz,       kFrt3,    eModule_Mod,    Z,Z,Z,F,T,F },
  { kParam_LFO2Amount,    1,                100,                0,                kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  { kParam_Env1Target,    eModT_None,       kNumOfModTargets-1, eModT_None,       kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_Env1Amount,    0,                100,                -100,             kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_Env1Attack,    0.1,              5.0,                0.01,             kUnit_Secs,     kFrt2,    eModule_Mod,    Z,Z,Z,F,T,F },
  { kParam_Env1Decay,     0.5,              5.0,                0.01,             kUnit_Secs,     kFrt2,    eModule_Mod,    Z,Z,Z,F,T,F },
  { kParam_Env1Sustain,   75,               100,                0,                kUnit_Perc,     kFrt2,    eModule_Mod,    Z,Z,Z,F,T,F },
  { kParam_Env1Release,   0.25,             5.0,                0.1,              kUnit_Secs,     kFrt2,    eModule_Mod,    Z,Z,Z,F,T,F },
  { kParam_Env2Target,    eModT_None,       kNumOfModTargets-1, eModT_None,       kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_Env2Amount,    0,                100,                -100,             kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_Env2Attack,    0.1,              5.0,                0.01,             kUnit_Secs,     kFrt2,    eModule_Mod,    Z,Z,Z,F,T,F },
  { kParam_Env2Decay,     0.5,              5.0,                0.01,             kUnit_Secs,     kFrt2,    eModule_Mod,    Z,Z,Z,F,T,F },
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  { kParam_WheelTarget,   eModT_None,       kNumOfModTargets-1, eModT_None,       kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_WheelAmount,   50,               100,                -100,             kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  { kParam_VeloTarget,    eModT_None,       kNumOfModTargets-1, eModT_None,       kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_VeloAmount,    50,               100,                -100,             kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Effects Section
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  { kParam_DistortType,   kDistortion_Off,  kNumOfDistorts-1,   kDistortion_Off,  kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_DistortGain,   1.0,              12.0,               1.0,              kUnit_Gain,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Delay
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  { kParam_DelayL_Mix,    30,               100,                0,                kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_DelayL_Time,   0.15,             kMaxDelay,          0.01,             kUnit_Secs,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_DelayL_FB,     35,               100,                0,                kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_DelayR_Mix,    30,               100,                0,                kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_DelayR_Time,   0.25,             kMaxDelay,          0.01,             kUnit_Secs,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_DelayR_FB,     25,               100,                0,                kUnit_Perc,     kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_DelayHP,       200,              kFiltMaxFreq,       kFiltMinFreq,     kUnit_Hz,       kFrt3,    eModule_None,   Z,Z,Z,F,T,F },
  { kParam_DelayLP,       3500,             kFiltMaxFreq,       kFiltMinFreq,     kUnit_Hz,       kFrt3,    eModule_None,   Z,Z,Z,F,T,F },
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  { kParam_Polyphony,     kMaxActive,       kMaxActive,         1,                kUnit_Index,    kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_Portamento,    0,                5.0,                0,                kUnit_Secs,     kFrt2,    eModule_None,   Z,Z,Z,F,F,F },
  { kParam_PitchBend,     2.0,              36.0,               0.0,              kUnit_ST,       kFnone,   eModule_None,   Z,Z,Z,F,F,F },
  { kParam_GlobalTuning,  0.0,              6.0,                -6.0,             kUnit_ST,       kFnone,   eModule_None,   Z,Z,Z,F,T,F },
  { kParam_GlobalVolume,  1.0,              4.0,                0.0,              kUnit_Gain,     kFrt2,    eModule_None,   Z,Z,Z,F,T,F }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  };

}
#endif /* DEFAULTS_H_ */
