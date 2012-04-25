/*
 * ParameterManager.hpp
 *
 * Parameter module. Manages the internal parameter
 * array, accessors and mutators. Also incorporates
 * a simple low-pass parameter smoothing filter.
 *
 *  Created on: 21 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "../../Include/TypesConstants.hpp"
#include "../../Include/Enums.hpp"
#include "../../Include/ParamTypes.hpp"
#include "../../Include/ParamMaps.hpp"
#include "../../Include/Compilation.hpp"
#include "ParameterArray.hpp"
#include "../Utility/Utility.hpp"
#include "../Interface/Interfaces.hpp"

#ifdef THREAD_SAFE
  #include <boost/thread/thread.hpp>
#endif

namespace hotpants {

  class ParameterManager: public Component
  {
    public:
      explicit                    ParameterManager(HotPantsCore&);
      // parameter access and modification
      ParamValue                  getValue(eParameter) const;
      const _parameterMap&        getParamMap(eParameter) const;
      bool                        paramModified(eParameter) const;
      bool                        setValue(eParameter, ParamValue);
      // modulation
      void                        setMod(eParameter, ParamValue);
      bool                        midiCC(MidiCC, MidiValue);
      bool                        pitchBend(MidiValue);
      // other
      void                        prepareForRender();
      const double                getGlobalTuningScale() const;

#ifdef CACHE_MODULES
      const bool                  moduleIsDirty(eParamModule) const;
      void                        moduleSetClean(eParamModule);
#endif

    private:
      // the actual parameter storage array
      ParameterArray              paramMap;
      // stored for global pitch
      mutable float               _globalTuningScale;
      float                       _pitchBend;
      float                       _modWheel;

#ifdef CACHE_MODULES
      void                        checkAndSetFlagForModule(eParamModule);
#endif

#ifdef THREAD_SAFE
      // concurrency mutexes
      mutable boost::mutex        paramMutex;
      mutable boost::mutex        modWheelMutex;
#endif
  };

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Inline functions
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  inline bool ParameterManager::pitchBend(MidiValue newBend)
  {
    if(newBend < 0)
      return false;
    // pitch bend messages always come in from the host
    // so we can assume that the message is intentional
    _pitchBend = static_cast<float>(newBend - kPitchBendCentre) / kPitchBendCentre;
    paramMap.settings[kParam_GlobalTuning].modified = true;
    return true;
  }

  inline void ParameterManager::prepareForRender()
  {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(paramMutex);
#endif
    // reset all mod target amounts
    eParameter p;
    for(eModT t = kFirstModT; t < kNumOfModTargets; t = static_cast<eModT>(t+1)) {
      p = kModMap[t].parameter;
      if(paramMap.settings[p].mod != 0.0) {
        paramMap.settings[p].mod = 0.0;
        paramMap.settings[p].modified = true;
      }
    }
  }

#ifdef CACHE_MODULES
  inline void ParameterManager::checkAndSetFlagForModule(eParamModule g)
  {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(paramMutex);
#endif
    if(g != eModule_None)
      paramMap.moduleMap[g].dirty = true;
  }
#endif

  inline const _parameterMap& ParameterManager::getParamMap(eParameter p) const {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(paramMutex);
#endif
    // returns a parameter array row
    return paramMap.settings[p];
  }

  inline void ParameterManager::setMod(eParameter t, ParamValue v) {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(paramMutex);
#endif
    eParameter p = kModMap[static_cast<IndexedValue>(paramMap.settings[t].value)].parameter;
    if(p == kParam_None)
      return;
    else {
      paramMap.settings[p].mod = v;
      paramMap.settings[p].modified = true;
#ifdef CACHE_MODULES
    checkAndSetFlagForModule(paramMap.settings[p].module);
#endif
    }
  }

#ifdef CACHE_MODULES
  inline const bool ParameterManager::moduleIsDirty(eParamModule g) const {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(paramMutex);
#endif
    return paramMap.moduleMap[g].dirty;
  }

  inline void ParameterManager::moduleSetClean(eParamModule g) {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(paramMutex);
#endif
    paramMap.moduleMap[g].dirty = false;
  }
#endif

} /* end: namespace hotpants */
#endif /* GLOBAL_H_ */
