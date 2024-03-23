/*
 * ParameterArray.cpp
 *
 *  Created on: 24 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "../../Include/ParamMaps.hpp"
#include "../../Include/Compilation.hpp"
#include "../../Include/ParamDefaults.hpp"
#include "ParameterArray.hpp"
#include <cassert>
#include <string.h>     // memcpy()

namespace hotpants {

  // these constants improve readability in the default array
  // defined in defaults.hpp
  const bool       ParameterArray::F = false;    // default modified flag
  const bool       ParameterArray::T = true;
  const ParamValue ParameterArray::Z = 0.0;      // zeroed value

#ifdef CACHE_MODULES
  const _moduleMap ParameterArray::kDefaultModuleMap[eNumOfModules] = {
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Group "dirty" flag function pointer map
  // Relates parameters to a module class
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      { eModule_None,       true,     },         // parameters that cannot be modulated
      { eModule_Filt,       true,     },
      { eModule_Amp,        true,     },
      { eModule_Mod,        true,     }
  };
#endif

  /*
   * Constructor inspects the default map for errors,
   * clones it for the user settings, and does additional
   * configuration.
   */
  ParameterArray::ParameterArray()
  {
    // clone the default parameter maps
    memcpy(settings, kDefaultParameters, sizeof(kDefaultParameters));

    // check that parameter map is correctly defined
    // and copy default settings
    for(eParameter p =  kFirstParam;
                   p != kNumOfParams;
                   p =  static_cast<eParameter>(p+1))
    {
      if(settings[p].enumVal != p) {
        fprintf(stderr, "Settings map correlation error: parameter %d\n", p);
        assert(false);
      }
      // this flag is set below, so all should be false at this stage
      if(settings[p].modTarget != false) {
        fprintf(stderr, "Default settings mod target flag should be false: parameter %d\n", p);
        assert(false);
      }
      // copy over the default value
      settings[p].value = settings[p].defValue;
    }

#ifdef CACHE_MODULES
    // copy module cache map
    memcpy(moduleMap, kDefaultModuleMap, sizeof(kDefaultModuleMap));

    // check module map
    for(eParamModule g  = eModule_None;
                         g != eNumOfModules;
                         g  = static_cast<eParamModule>(g+1))
    {
      if(moduleMap[g].module != g) {
        fprintf(stderr, "Module map correlation error: module %d\n", g);
        assert(false);
      }
    }
#endif

    // check oscillator map
    for(eOscillator o = kFirstOsc; o < kNumOfOscs; o = static_cast<eOscillator>(o+1)) {
      if(kOscMap[o].enumVal != o) {
        fprintf(stderr, "Oscillator map correlation error: oscillator %d\n", o);
        assert(false);
      }
    }
    // check filter map
    for(eFilter f = kFirstFilter; f < kNumOfFilts; f = static_cast<eFilter>(f+1)) {
      if(kFilterMap[f].enumVal != f) {
        fprintf(stderr, "Filter map correlation error: filter %d\n", f);
        assert(false);
      }
    }

    // set mod target flags for applicable getParameters
    for(eModT t = eModT_None; t < kNumOfModTargets; t = static_cast<eModT>(t+1)) {
      if(t != eModT_None) {
        settings[kModMap[t].parameter].modTarget = true;
      }
    }
  }

}
