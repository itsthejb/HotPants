/*
 * ParamMaps.hpp
 *
 * Constant static maps, used mostly to link components
 * to entries in the parameter settings array.
 *
 *  Created on: 28 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef PARAMMAPS_H_
#define PARAMMAPS_H_

#include "Enums.hpp"
#include "ParamTypes.hpp"

namespace hotpants {

  const _modMap kModMap[kNumOfModTargets] = {
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //  Mod target             -> Real instrument parameter
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    { eModT_None,               kParam_None             },
    { eModT_GlobalVolume,       kParam_GlobalVolume     },
    { eModT_GlobalTuning,       kParam_GlobalTuning     },
    { eModT_Osc1Tuning,         kParam_Osc1Tuning       },
    { eModT_Osc1Amp,            kParam_Osc1Amp          },
    { eModT_Osc2Tuning,         kParam_Osc2Tuning       },
    { eModT_Osc2Fine,           kParam_Osc2Fine         },
    { eModT_Osc2Amp,            kParam_Osc2Amp          },
    { eModT_Osc3Tuning,         kParam_Osc3Tuning       },
    { eModT_Osc3Amp,            kParam_Osc3Amp          },
    { eModT_PulseWidth,         kParam_PulseWidth       },
    { eModT_Filt1Cutoff,        kParam_Filt1Cutoff      },
    { eModT_Filt1Q,             kParam_Filt1Q           },
    { eModT_Filt2Cutoff,        kParam_Filt2Cutoff      },
    { eModT_Filt2Q,             kParam_Filt2Q           },
    { eModT_FiltMix,            kParam_FiltMix          },
    { eModT_LFO1Amount,         kParam_LFO1Amount       },
    { eModT_LFO1Rate,           kParam_LFO1Rate         },
    { eModT_LFO2Amount,         kParam_LFO2Amount       },
    { eModT_LFO2Rate,           kParam_LFO2Rate         },
    { eModT_Env1Amount,         kParam_Env1Amount       },
    { eModT_Env2Amount,         kParam_Env2Amount       }
  };

  const _oscMap  kOscMap[kNumOfOscs] = {
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Oscillator | Waveform param   | Oscillator amp    | Oscillator tuning
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    { kOsc1,      kParam_Osc1Wave,   kParam_Osc1Amp,     kParam_Osc1Tuning      },
    { kOsc2,      kParam_Osc2Wave,   kParam_Osc2Amp,     kParam_Osc2Tuning      },
    { kOsc3,      kParam_Osc3Wave,   kParam_Osc3Amp,     kParam_Osc3Tuning      },
    { kLFO1,      kParam_LFO1Wave,   kParam_LFO1Amount,  kParam_LFO1Rate        },
    { kLFO2,      kParam_LFO2Wave,   kParam_LFO2Amount,  kParam_LFO2Rate        }
  };

  const _filtMap kFilterMap[kNumOfFilts] = {
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Filter       | Filter type       | Filter cutoff       | Filter Q      | EQ gain
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    { kFiltFixed,   kParam_None,        kParam_None,          kParam_None,    kParam_None             },
    { kFilt1,       kParam_Filt1Type,   kParam_Filt1Cutoff,   kParam_Filt1Q,  kParam_Filt1EQGain      },
    { kFilt2,       kParam_Filt2Type,   kParam_Filt2Cutoff,   kParam_Filt2Q,  kParam_Filt2EQGain      },
    { kFiltDelayHP, kParam_None,        kParam_DelayHP,       kParam_None,    kParam_None             },
    { kFiltDelayLP, kParam_None,        kParam_DelayLP,       kParam_None,    kParam_None             },
  };

  const _delayMap kDelayMap[kNumOfDelayChannels] = {
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //  Delay channel       | Mix parameter     | Delay time          | Delay feedback
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    { kDelayChannel_Left,   kParam_DelayL_Mix,  kParam_DelayL_Time,   kParam_DelayL_FB },
    { kDelayChannel_Right,  kParam_DelayR_Mix,  kParam_DelayR_Time,   kParam_DelayR_FB }
  };

} /* end namespace hotpants */
#endif /* PARAMDEFAULTS_H_ */
