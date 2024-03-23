/*
 * Enums.hpp
 *
 * All parameters initially defined and
 * enumerated here.
 *
 *  Created on: 20 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef PARAMETERLIST_H_
#define PARAMETERLIST_H_

namespace hotpants {

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Parameter list
  enum eParameter {
    // Synth body
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // amp envelope
    kParam_AmpAttack = 0,
    kParam_AmpDecay,
    kParam_AmpSustain,
    kParam_AmpRelease,
    kParam_AmpScaling,
    kParam_Velocity,
    // oscillators
    kParam_Osc1Wave,
    kParam_Osc1Tuning,
    kParam_Osc1Amp,
    kParam_Osc2Wave,
    kParam_Osc2Tuning,
    kParam_Osc2Fine,
    kParam_OscMod,
    kParam_Osc2Amp,
    kParam_Osc3Wave,
    kParam_Osc3Tuning,
    kParam_Osc3Amp,
    kParam_OscAnalogue,
    kParam_PulseWidth,
    // filters
    kParam_Filt1Type,
    kParam_Filt1Cutoff,
    kParam_Filt1Q,
    kParam_Filt1EQGain,
    kParam_Filt2Type,
    kParam_Filt2Cutoff,
    kParam_Filt2Q,
    kParam_Filt2EQGain,
    kParam_FiltConnect,
    kParam_FiltMix,
    kParam_FiltKeyTrack,
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Modulation
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // LFOs
    kParam_LFO1Target,
    kParam_LFO1Wave,
    kParam_LFO1Rate,
    kParam_LFO1Amount,
    kParam_LFO2Target,
    kParam_LFO2Wave,
    kParam_LFO2Rate,
    kParam_LFO2Amount,
    // Envelopes
    kParam_Env1Target,
    kParam_Env1Amount,
    kParam_Env1Attack,
    kParam_Env1Decay,
    kParam_Env1Sustain,
    kParam_Env1Release,
    kParam_Env2Target,
    kParam_Env2Amount,
    kParam_Env2Attack,
    kParam_Env2Decay,
    // Mod wheel
    kParam_WheelTarget,
    kParam_WheelAmount,
    // velo mod
    kParam_VeloTarget,
    kParam_VeloAmount,
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Effects
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    kParam_DistortType,
    kParam_DistortGain,
    // Delay
    kParam_DelayL_Mix,
    kParam_DelayL_Time,
    kParam_DelayL_FB,
    kParam_DelayR_Mix,
    kParam_DelayR_Time,
    kParam_DelayR_FB,
    kParam_DelayHP,
    kParam_DelayLP,
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Global ParameterManager
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    kParam_Polyphony,
    kParam_Portamento,
    kParam_PitchBend,
    kParam_GlobalTuning,
    kParam_GlobalVolume,
    kNumOfParams
  };
  // looping/mapping aliases
  const eParameter kFirstParam = kParam_AmpAttack;
  const eParameter kParam_None = kNumOfParams;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Factory presets
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eFactoryPreset {
    kPreset_Factory1 = 0,
    kPreset_Factory2,
    kNumOfPresets
  };
  const eFactoryPreset kFirstPreset = kPreset_Factory1;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Waveforms
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eWaveform {
    // audio
    kWave_SineDirect = 0,
    kWave_TriPartial,
    kWave_SawPartial,
    kWave_SquareFixed,
    kWave_PulsePWM,
    kWave_Noise,
    // lfo
    kWave_TriDirect,
    kWave_SawDirect,
    kNumOfAllWaves
  };
  const eWaveform kFirstWaveform = kWave_SineDirect;

  enum eOscWaveform {
    kOscWave_Sine       = kWave_SineDirect,
    kOscWave_Tri        = kWave_TriPartial,
    kOscWave_Saw        = kWave_SawPartial,
    kOscWave_Square     = kWave_SquareFixed,
    kOscWave_PulsePWM   = kWave_PulsePWM,
    kOscWave_Noise      = kWave_Noise,
    kNumOfOscWaves      = 6
  };
  enum eLFOwaveForm {
    kLFOwave_Sine       = kWave_SineDirect,
    kLFOwave_Tri        = kWave_TriDirect,
    kLFOwave_Saw        = kWave_SawDirect,
    kLFOwave_Square     = kWave_SquareFixed,
    kLFOwave_SandH,
    kNumOfLFOwaves      = 5
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Oscillator modulations
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~=
  enum eOscMod {
    kOscMod_None = 0,
    kOscMod_FM,
    kOscMod_AM,
    kOscMod_RM,
    kNumOfOscMods
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Filter types
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eFilterType {
    kFiltType_Off = 0,
    kFiltType_LP,
    kFiltType_HP,
    kFiltType_BP_CSG,
    kFiltType_BP_CZPG,
    kFiltType_Notch,
    kFiltType_AllPass,
    // eq types
    kFiltType_Peaking,
    kFiltType_LowShelf,
    kFiltType_HiShelf,
    kNumOfFiltTypes
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Filter connection
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eFilterConnection {
    kConnect_Serial = 0,
    kConnect_Parallel,
    kNumOfConnections
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Distortion type
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eDistortionType {
    kDistortion_Off = 0,
    kDistortion_HardC,
    kDistortion_FoldBack,
    kNumOfDistorts
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Oscillators
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eOscillator {
    kOsc1 = 0,
    kOsc2,
    kOsc3,
    kLFO1,
    kLFO2,
    kNumOfOscs
  };
  const unsigned int kNumOfAudioOscs = static_cast<int>(kOsc3+1);
  const eOscillator  kFirstOsc       = kOsc1;
  const unsigned int kNumOfLFOs      = 2;
  const unsigned int kNumOfEnvs      = 2;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Filters
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eFilter {
    kFiltFixed = 0,
    kFilt1,
    kFilt2,
    kFiltDelayHP,
    kFiltDelayLP,
    kNumOfFilts
  };
  const eFilter kFirstFilter = kFiltFixed;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Channels
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eDelayChannel {
    kDelayChannel_Left = 0,
    kDelayChannel_Right,
    kNumOfDelayChannels
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Modulation targets
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eModT {
    eModT_None = 0,
    eModT_GlobalVolume,
    eModT_GlobalTuning,
    // Oscs
    eModT_Osc1Tuning,
    eModT_Osc1Amp,
    eModT_Osc2Tuning,
    eModT_Osc2Fine,
    eModT_Osc2Amp,
    eModT_Osc3Tuning,
    eModT_Osc3Amp,
    eModT_PulseWidth,
    // Filters
    eModT_Filt1Cutoff,
    eModT_Filt1Q,
    eModT_Filt2Cutoff,
    eModT_Filt2Q,
    eModT_FiltMix,
    // Modulators
    eModT_LFO1Amount,
    eModT_LFO1Rate,
    eModT_LFO2Amount,
    eModT_LFO2Rate,
    eModT_Env1Amount,
    eModT_Env2Amount,
    //
    kNumOfModTargets
  };
  const eModT kFirstModT = eModT_GlobalVolume;

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Parameter units
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eParamUnitType {
    kUnit_Gain = 0,
    kUnit_Secs,
    kUnit_Perc,         // percent
    kUnit_Index,
    kUnit_ST,           // relative semitones
    kUnit_Hz,
    kUnit_Generic,      // 0.0 - 1.0
    kNumOfUnits
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Parameter modules
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eParamModule {
    eModule_None = 0,
    eModule_Filt,
    eModule_Amp,
    eModule_Mod,
    eNumOfModules
  };
  
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Parameter flags
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eParamFlag {
    kFnone = 0,
    kFread,
    kFwrite,
    kFrw,
    kFrt2,
    kFrt3,
    kFsqr,
    kFcube,
    kFlagCount
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Midi CCs
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eSupportedMidiCCs {
    kMidiCCModWheel = 1
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Component refresh
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  enum eRefreshType
  {
    kCHECK_FOR_UPDATES = false,
    kFORCE_REFRESH     = true
  };

} /* end: namespace hotpants */
#endif /* PARAMETERLIST_H_ */
