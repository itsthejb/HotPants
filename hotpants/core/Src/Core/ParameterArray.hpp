/*
 * ParameterArray.hpp
 *
 * Contains the actual array of storage for the
 * instrument's parameters. Access is public,
 * but can only be instantiated by a ParameterManager
 * object.
 *
 * Constructor functions by cloning the static
 * default parameter array and module map.
 *
 *  Created on: 24 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef PARAMDEFAULTS_H_
#define PARAMDEFAULTS_H_

#include "../../Include/Enums.hpp"
#include "../../Include/ParamTypes.hpp"
#include "../../Include/Compilation.hpp"

namespace hotpants {

  class ParameterArray
  {
    public:
      friend class                  ParameterManager;
      _parameterMap                 settings[kNumOfParams];

    /*
     * For some reason #ifdefing out moduleMap[] completely
     * causes a crash in the wavetable read...
     */
#ifdef CACHE_MODULES
    public:
      _moduleMap                    moduleMap[eNumOfModules];
#else
    private:
      _moduleMap                    moduleMap[eNumOfModules];
#endif

    private:
      ParameterArray();             // can only be constructed by ParameterManager
      static const bool             F, T;
      static const ParamValue       Z;
      static const _parameterMap    kDefaultParameters[kNumOfParams];

#ifdef CACHE_MODULES
      static const _moduleMap       kDefaultModuleMap[eNumOfModules];
#endif
  };

}
#endif /* PARAMDEFAULTS_H_ */
