/*
 *  ParamMapping.hpp
 *
 *  AU-specific parameter mappings, mostly converting
 *  preprocessor strings to CoreFoundation types.
 *
 *  Created by Jon Crooke on 26/06/2010.
 *  Copyright 2010 jB Soft. All rights reserved.
 *
 */

#ifndef PARAMMAPPING_H_
#define PARAMMAPPING_H_

#include "AUInstrumentBase.h"
#include "CoreInclude.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Mapping types
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct _AUstringMap_ {  const hotpants::eParameter      enumVal;
                        const CFStringRef               string;           };
struct _AUunitMap_   {  const hotpants::eParamUnitType  internalValue;
                        const AudioUnitParameterUnit    AUvalue;          };
struct _AUflagMap_   {  const uint32_t                  internalValue;
                        const UInt32                    AUvalue;          };
struct _AUmenuItemMap{  const hotpants::eParameter      enumVal;
                        const CFStringRef*              array;            
                        const size_t                    size;             };

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// String mapping
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const _AUstringMap_ AUstringMap[hotpants::kNumOfParams] = {
  // amp envelope
  { hotpants::kParam_AmpAttack,       CFSTR(kParamName_AmpAttack)       },
  { hotpants::kParam_AmpDecay,        CFSTR(kParamName_AmpDecay)        },
  { hotpants::kParam_AmpSustain,      CFSTR(kParamName_AmpSustain)      },
  { hotpants::kParam_AmpRelease,      CFSTR(kParamName_AmpRelease)      },
  { hotpants::kParam_AmpScaling,      CFSTR(kParamName_AmpScaling)      },
  { hotpants::kParam_Velocity,        CFSTR(kParamName_Velocity)        },
  // oscillators
  { hotpants::kParam_Osc1Wave,        CFSTR(kParamName_Osc1Wave)        },
  { hotpants::kParam_Osc1Tuning,      CFSTR(kParamName_Osc1Tuning)      },
  { hotpants::kParam_Osc1Amp,         CFSTR(kParamName_Osc1Amp)         },
  { hotpants::kParam_Osc2Wave,        CFSTR(kParamName_Osc2Wave)        },
  { hotpants::kParam_Osc2Tuning,      CFSTR(kParamName_Osc2Tuning)      },
  { hotpants::kParam_Osc2Fine,        CFSTR(kParamName_Osc2Fine)        },
  { hotpants::kParam_OscMod,          CFSTR(kParamName_OscMod)          },
  { hotpants::kParam_Osc2Amp,         CFSTR(kParamName_Osc2Amp)         },
  { hotpants::kParam_Osc3Wave,        CFSTR(kParamName_Osc3Wave)        },
  { hotpants::kParam_Osc3Tuning,      CFSTR(kParamName_Osc3Tuning)      },
  { hotpants::kParam_Osc3Amp,         CFSTR(kParamName_Osc3Amp)         },
  { hotpants::kParam_OscAnalogue,     CFSTR(kParamName_OscAnalogue)     },
  { hotpants::kParam_PulseWidth,      CFSTR(kParamName_PulseWidth)      },
  // filters
  { hotpants::kParam_Filt1Type,       CFSTR(kParamName_Filt1Type)       },
  { hotpants::kParam_Filt1Cutoff,     CFSTR(kParamName_Filt1Cutoff)     },
  { hotpants::kParam_Filt1Q,          CFSTR(kParamName_Filt1Q)          },
  { hotpants::kParam_Filt1EQGain,     CFSTR(kParamName_Filt1EQGain)     },
  { hotpants::kParam_Filt2Type,       CFSTR(kParamName_Filt2Type)       },
  { hotpants::kParam_Filt2Cutoff,     CFSTR(kParamName_Filt2Cutoff)     },
  { hotpants::kParam_Filt2Q,          CFSTR(kParamName_Filt2Q)          },
  { hotpants::kParam_Filt2EQGain,     CFSTR(kParamName_Filt2EQGain)     },
  { hotpants::kParam_FiltConnect,     CFSTR(kParamName_FiltConnect)     },
  { hotpants::kParam_FiltMix,         CFSTR(kParamName_FiltMix)         },
  { hotpants::kParam_FiltKeyTrack,    CFSTR(kParamName_FiltKeyTrack)    },
  // Modulation
  // LFOs
  { hotpants::kParam_LFO1Target,      CFSTR(kParamName_LFO1Target)      },
  { hotpants::kParam_LFO1Wave,        CFSTR(kParamName_LFO1Wave)        },
  { hotpants::kParam_LFO1Rate,        CFSTR(kParamName_LFO1Rate)        },
  { hotpants::kParam_LFO1Amount,      CFSTR(kParamName_LFO1Amount)      },
  { hotpants::kParam_LFO2Target,      CFSTR(kParamName_LFO2Target)      },
  { hotpants::kParam_LFO2Wave,        CFSTR(kParamName_LFO2Wave)        },
  { hotpants::kParam_LFO2Rate,        CFSTR(kParamName_LFO2Rate)        },
  { hotpants::kParam_LFO2Amount,      CFSTR(kParamName_LFO2Amount)      },
  // Envelopes
  { hotpants::kParam_Env1Target,      CFSTR(kParamName_Env1Target)      },
  { hotpants::kParam_Env1Amount,      CFSTR(kParamName_Env1Amount)      },
  { hotpants::kParam_Env1Attack,      CFSTR(kParamName_Env1Attack)      },
  { hotpants::kParam_Env1Decay,       CFSTR(kParamName_Env1Decay)       },
  { hotpants::kParam_Env1Sustain,     CFSTR(kParamName_Env1Sustain)     },
  { hotpants::kParam_Env1Release,     CFSTR(kParamName_Env1Release)     },
  { hotpants::kParam_Env2Target,      CFSTR(kParamName_Env2Target)      },
  { hotpants::kParam_Env2Amount,      CFSTR(kParamName_Env2Amount)      },
  { hotpants::kParam_Env2Attack,      CFSTR(kParamName_Env2Attack)      },
  { hotpants::kParam_Env2Decay,       CFSTR(kParamName_Env2Decay)       },
  // mod wheel
  { hotpants::kParam_WheelTarget,     CFSTR(kParamName_WheelTarget)     },
  { hotpants::kParam_WheelAmount,     CFSTR(kParamName_WheelAmount)     },
  // velocity mod
  { hotpants::kParam_VeloTarget,      CFSTR(kParamName_VeloTarget)      },
  { hotpants::kParam_VeloAmount,      CFSTR(kParamName_VeloAmount)      },
  // effects
  { hotpants::kParam_DistortType,     CFSTR(kParamName_DistortType)     },
  { hotpants::kParam_DistortGain,     CFSTR(kParamName_DistortGain)     },
  // delay
  { hotpants::kParam_DelayL_Mix,      CFSTR(kParamName_DelayL_Mix)      },
  { hotpants::kParam_DelayL_Time,     CFSTR(kParamName_DelayL_Time)     },
  { hotpants::kParam_DelayL_FB,       CFSTR(kParamName_DelayL_FB)       },
  { hotpants::kParam_DelayR_Mix,      CFSTR(kParamName_DelayR_Mix)      },
  { hotpants::kParam_DelayR_Time,     CFSTR(kParamName_DelayR_Time)     },
  { hotpants::kParam_DelayR_FB,       CFSTR(kParamName_DelayR_FB)       },
  { hotpants::kParam_DelayHP,         CFSTR(kParamName_DelayHP)         },
  { hotpants::kParam_DelayLP,         CFSTR(kParamName_DelayLP)         },
  // global pitch
  { hotpants::kParam_Polyphony,       CFSTR(kParamName_Polyphony)       },
  { hotpants::kParam_Portamento,      CFSTR(kParamName_Portamento)      },
  { hotpants::kParam_PitchBend,       CFSTR(kParamName_PitchBend)       },
  { hotpants::kParam_GlobalTuning,    CFSTR(kParamName_GlobalTuning)    },
  { hotpants::kParam_GlobalVolume,    CFSTR(kParamName_GlobalVolume)    }
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Factory presets
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const AUPreset AUpresetMap[hotpants::kNumOfPresets] = {
    { hotpants::kPreset_Factory1,     CFSTR(kPresetName_Factory1) },
    { hotpants::kPreset_Factory2,     CFSTR(kPresetName_Factory2) }
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Menu Items
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const CFStringRef AUmenu_OscWaveforms[hotpants::kNumOfOscWaves] = {
  CFSTR(kMenuItem_Osc_Sine),
  CFSTR(kMenuItem_Osc_Tri),
  CFSTR(kMenuItem_Osc_Saw),
  CFSTR(kMenuItem_Osc_Square),
  CFSTR(kMenuItem_Osc_PulsePWM),
  CFSTR(kMenuItem_Osc_Noise)      
};
const CFStringRef AUmenu_OscMods[hotpants::kNumOfOscMods] = {
  CFSTR(kMenuItem_OscMod_None),
  CFSTR(kMenuItem_OscMod_FM),
  CFSTR(kMenuItem_OscMod_AM),
  CFSTR(kMenuItem_OscMod_RM)
};
const CFStringRef AUmenu_LFOwaveforms[hotpants::kNumOfLFOwaves] = {
  CFSTR(kMenuItem_LFO_Sine),
  CFSTR(kMenuItem_LFO_Tri),
  CFSTR(kMenuItem_LFO_Saw),
  CFSTR(kMenuItem_LFO_Square),
  CFSTR(kMenuItem_LFO_SandH)
};
const CFStringRef AUmenu_filterTypes[hotpants::kNumOfFiltTypes] = {
  CFSTR(kMenuItem_Filt_Off),
  CFSTR(kMenuItem_Filt_LP),
  CFSTR(kMenuItem_Filt_HP),
  CFSTR(kMenuItem_Filt_BP_CSG),
  CFSTR(kMenuItem_Filt_BP_CZPG),
  CFSTR(kMenuItem_Filt_Notch),
  CFSTR(kMenuItem_Filt_AllPass),
  CFSTR(kMenuItem_Filt_Peaking),
  CFSTR(kMenuItem_Filt_LowShelf),
  CFSTR(kMenuItem_Filt_HiShelf)
};
const CFStringRef AUmenu_filtConnections[hotpants::kNumOfConnections] = {
  CFSTR(kMenuItem_ConnectSerial),
  CFSTR(kMenuItem_ConnectParallel)
};
const CFStringRef AUmenu_disortTypes[hotpants::kNumOfDistorts] = {
  CFSTR(kMenuItem_Distort_Off),
  CFSTR(kMenuItem_Distort_HardC),
  CFSTR(kMenuItem_Distort_Fold),
};
const CFStringRef AUmenu_modTargets[hotpants::kNumOfModTargets] = {
  CFSTR(kMenuItem_Mod_None),
  CFSTR(kMenuItem_Mod_GlobalVol),
  CFSTR(kMenuItem_Mod_GlobalTune),
  CFSTR(kMenuItem_Mod_Osc1Tuning),
  CFSTR(kMenuItem_Mod_Osc1Amp),
  CFSTR(kMenuItem_Mod_Osc2Tuning),
  CFSTR(kMenuItem_Mod_Osc2Fine),
  CFSTR(kMenuItem_Mod_Osc2Amp),
  CFSTR(kMenuItem_Mod_Osc3Tuning),
  CFSTR(kMenuItem_Mod_Osc3Amp),
  CFSTR(kMenuItem_Mod_PulseWidth),
  CFSTR(kMenuItem_Mod_Filt1Cutoff),
  CFSTR(kMenuItem_Mod_Filt1Q),
  CFSTR(kMenuItem_Mod_Filt2Cutoff),
  CFSTR(kMenuItem_Mod_Filt2Q),
  CFSTR(kMenuItem_Mod_FiltMix),
  CFSTR(kMenuItem_Mod_LFO1Amount),
  CFSTR(kMenuItem_Mod_LFO1Rate),
  CFSTR(kMenuItem_Mod_LFO2Amount),
  CFSTR(kMenuItem_Mod_LFO2Rate),
  CFSTR(kMenuItem_Mod_Env1Amount),
  CFSTR(kMenuItem_Mod_Env2Amount),
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Parameters to menu item array
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const _AUmenuItemMap AUmenuItemMap[] = {
  { hotpants::kParam_Osc1Wave,      AUmenu_OscWaveforms,    hotpants::kNumOfOscWaves    },
  { hotpants::kParam_Osc2Wave,      AUmenu_OscWaveforms,    hotpants::kNumOfOscWaves    },
  { hotpants::kParam_Osc3Wave,      AUmenu_OscWaveforms,    hotpants::kNumOfOscWaves    },
  { hotpants::kParam_OscMod,        AUmenu_OscMods,         hotpants::kNumOfOscMods     },
  { hotpants::kParam_LFO1Wave,      AUmenu_LFOwaveforms,    hotpants::kNumOfLFOwaves    },
  { hotpants::kParam_LFO2Wave,      AUmenu_LFOwaveforms,    hotpants::kNumOfLFOwaves    },
  { hotpants::kParam_Filt1Type,     AUmenu_filterTypes,     hotpants::kNumOfFiltTypes   },
  { hotpants::kParam_Filt2Type,     AUmenu_filterTypes,     hotpants::kNumOfFiltTypes   },
  { hotpants::kParam_FiltConnect,   AUmenu_filtConnections, hotpants::kNumOfConnections },
  { hotpants::kParam_DistortType,   AUmenu_disortTypes,     hotpants::kNumOfDistorts    },
  { hotpants::kParam_LFO1Target,    AUmenu_modTargets,      hotpants::kNumOfModTargets  },
  { hotpants::kParam_LFO2Target,    AUmenu_modTargets,      hotpants::kNumOfModTargets  },
  { hotpants::kParam_Env1Target,    AUmenu_modTargets,      hotpants::kNumOfModTargets  },
  { hotpants::kParam_Env2Target,    AUmenu_modTargets,      hotpants::kNumOfModTargets  },
  { hotpants::kParam_WheelTarget,   AUmenu_modTargets,      hotpants::kNumOfModTargets  },
  { hotpants::kParam_VeloTarget,    AUmenu_modTargets,      hotpants::kNumOfModTargets  }
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Unit mapping
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const _AUunitMap_ AUunitMap[hotpants::kNumOfUnits] = {
  { hotpants::kUnit_Gain,    kAudioUnitParameterUnit_LinearGain         },
  { hotpants::kUnit_Secs,    kAudioUnitParameterUnit_Seconds            },
  { hotpants::kUnit_Perc,    kAudioUnitParameterUnit_Percent            },
  { hotpants::kUnit_Index,   kAudioUnitParameterUnit_Indexed            },
  { hotpants::kUnit_ST,      kAudioUnitParameterUnit_RelativeSemiTones  },
  { hotpants::kUnit_Hz,      kAudioUnitParameterUnit_Hertz              },
  { hotpants::kUnit_Generic, kAudioUnitParameterUnit_Generic            }
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Flag mapping
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const _AUflagMap_ AUflagMap[hotpants::kFlagCount] = {
  { hotpants::kFnone,        0                                         },
  { hotpants::kFread,        kAudioUnitParameterFlag_IsReadable        },
  { hotpants::kFwrite,       kAudioUnitParameterFlag_IsWritable        },
  { hotpants::kFrw,          kAudioUnitParameterFlag_IsReadable
                            |kAudioUnitParameterFlag_IsWritable        },
  { hotpants::kFrt2,         kAudioUnitParameterFlag_DisplaySquareRoot },
  { hotpants::kFrt3,         kAudioUnitParameterFlag_DisplayCubeRoot   },
  { hotpants::kFsqr,         kAudioUnitParameterFlag_DisplaySquared    },
  { hotpants::kFcube,        kAudioUnitParameterFlag_DisplayCubed      }
};

#endif
