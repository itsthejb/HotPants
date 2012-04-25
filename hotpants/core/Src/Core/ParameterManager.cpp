/*
 * ParameterManager.cpp
 *
 *  Created on: 21 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "../../Include/Enums.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../../Include/Compilation.hpp"
#include "../../Include/ParamMaps.hpp"
#include "../Core/HotPantsCore.hpp"
#include <cassert>

#ifdef THREAD_SAFE
  #include <boost/thread/thread.hpp>
#endif

namespace hotpants {

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Constructor
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  ParameterManager::ParameterManager(HotPantsCore& c)
  : Component(c), _globalTuningScale(1.0), _pitchBend(0), _modWheel(0) { }

  // Main parameter accessor
  ParamValue ParameterManager::getValue(eParameter p) const
  {
    assert(p != kParam_None);

#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(paramMutex);
#endif

    const _parameterMap& mapRow = paramMap.settings[p];
    ParamValue value = mapRow.value;

#ifdef PARAM_SMOOTHING
    if(mapRow.smooth)
    {
      // LP parameter smoothing for non-indexed values
      value = (value + mapRow.delayVal) * 0.5;
      // store previous value
      mapRow.delayVal = value;
    }
#endif

    // don't check for mod if this parameter isn't a possible mod target
    if(mapRow.modTarget)
    {
      // is this parameter the current modulation wheel target?
      if(kModMap[static_cast<eModT>(paramMap.settings[kParam_WheelTarget].value)].parameter == p)
      {
        value += (_modWheel  * paramMap.settings[kParam_WheelAmount].value *
                  kPercToDec * mapRow.maxValue);
      }
      // add other mod values
      value += (mapRow.maxValue * mapRow.mod);
    }

    // clip the return to the minimum or maximum for this parameter
    if(value > mapRow.maxValue) value = mapRow.maxValue;
    if(value < mapRow.minValue) value = mapRow.minValue;

    return value;
  }

  /*
   * Parameter mutator
   */
  bool ParameterManager::setValue(eParameter p, ParamValue val)
  {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(paramMutex);
#endif
    // invalid param?
    if(val > paramMap.settings[p].maxValue || val <  paramMap.settings[p].minValue)
      return false;
    // parameter unchanged?
    if (Utility::fpEqual(val, paramMap.settings[p].value)) {
      // doesn't need to be changed
      return true;
    }

    // modify value
    if(paramMap.settings[p].unit == kUnit_Index)
      paramMap.settings[p].value = static_cast<IndexedValue>(val);
    else
      paramMap.settings[p].value    = val;
    paramMap.settings[p].modified = true;

#ifdef CACHE_MODULES
    checkAndSetFlagForModule(paramMap.settings[p].module);
#endif

    return true;
  }

  /*
   * This function resets the 'modified' flag itself to ensure that this always happens.
   * A caller not acting on a parameter change is an easily spotted bug, whereas
   * unnecessary refreshing of local calculations drains efficiency and is hard to spot
   */
  bool ParameterManager::paramModified(eParameter p) const
  {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(paramMutex);
#endif

#ifdef REFRESH_CHECK
    if(paramMap.settings[p].modified) {
      paramMap.settings[p].modified = false;
      return true;
    } else {
      return false;
    }
#else
    return true;                          // refreshing forced
#endif
  }

  const double ParameterManager::getGlobalTuningScale() const
  {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(paramMutex);
#endif
    if(paramMap.settings[kParam_GlobalTuning].modified) {
      // recalculate scaling factor
      _globalTuningScale = Utility::calcTuning(getValue(kParam_GlobalTuning)
                            // include pitch bend
                            + (_pitchBend * paramMap.settings[kParam_PitchBend].value));
      // value updated
      paramMap.settings[kParam_GlobalTuning].modified = false;
    }
    return _globalTuningScale;
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Midi CC
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  bool ParameterManager::midiCC(MidiCC controller, MidiValue newValue)
  {
    // only supporting mod wheel ( cc == 1 )
    if(newValue < 0 || controller != kMidiCCModWheel)
      return false;

    // get current target if any
    eModT target = static_cast<eModT>(paramMap.settings[kParam_WheelTarget].value);
    if(target == eModT_None)
      return false;

    _modWheel = Utility::midiControlToFloat(newValue);
    paramMap.settings[kModMap[target].parameter].modified = true;
    return true;
  }

} /* end namespace hotpants */
