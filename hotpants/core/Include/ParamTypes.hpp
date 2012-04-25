/*
 * ParamTypes.hpp
 *
 * Types for the static mapping of modules to their
 * related parameters, and for modulation targets to
 * their relative parameter targets.
 * Actual static (default) data defined in ParamDefaults.hpp
 *
 *  Created on: 8 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef PARAMTYPES_H_
#define PARAMTYPES_H_

#include "Enums.hpp"
#include "TypesConstants.hpp"

namespace hotpants {

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Parameter map
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  struct _parameterMap {
    const   eParameter          enumVal = kParam_AmpAttack;
    const   ParamValue          defValue = 0.0;
    const   ParamValue          maxValue;
    const   ParamValue          minValue;
    const   eParamUnitType      unit;
    const   eParamFlag          flag;
    const   eParamModule        module;
            ParamValue          value;
    mutable ParamValue          delayVal;     // parameter smoothing
            ParamValue          mod;
            bool                modTarget;
    const   bool                smooth;
    mutable bool                modified;
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Factory presets
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  struct kPresetVal {
      const eParameter          enumVal;
      const ParamValue          value;
  };
  struct kPreset {
      const eFactoryPreset      enumVal;
      const char*               name;
      const kPresetVal          parameter[kNumOfParams];
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Oscillator parameter enum map
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  struct _modMap {
    const eModT                 modTarget;
    const eParameter            parameter;
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Oscillator parameter enum map
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  struct _oscMap {
    eOscillator                 enumVal;
    eParameter                  wave;
    eParameter                  amp;
    eParameter                  tuning;
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Delay channel map
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  struct _delayMap {
    eDelayChannel               channel;
    eParameter                  mix;
    eParameter                  time;
    eParameter                  feedback;
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Filter parameter enum map
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  struct _filtMap {
    eFilter                     enumVal;
    eParameter                  type;
    eParameter                  cutoff;
    eParameter                  q;
    eParameter                  gain;
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Group object map
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  struct _moduleMap {
    const eParamModule          module;
    bool                        dirty;
  };

} /* end namespace hotpants */
#endif /* PARAMTYPES_H_ */
