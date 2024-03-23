/*
 * HotPantsCore.hpp
 *
 * Synthesiser core object
 *
 *  Created on: 11 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef HOTPANTSCORE_H_
#define HOTPANTSCORE_H_

#include "ParameterManager.hpp"
#include "VoiceManager.hpp"
#include "../../Include/Compilation.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../Module/Voice.hpp"
#include "../Effect/FXModule.hpp"
#include "../WaveTable/WaveTableContainer.hpp"
#include <stdint.h>

#ifdef CACHE_MODULES
  #include "../Module/ModuleCache.hpp"
#endif
#ifdef UNIT_TEST
  #include "../../Test/UnitTest.hpp"
#endif

namespace hotpants {

  class HotPantsCore
  {
    public:
                            HotPantsCore();
      bool                  initialise(SamplingRate);
      // note life-cycle
      bool                  startNote(NoteUniqueId  ID,
                                      MidiNote      notePitch,
                                      MidiVelocity  noteVelocity);
      bool                  stopNote (NoteUniqueId ID);
      // output stereo audio rendering
      bool                  render(float* leftBuffer,
                                   float* rightBuffer,
                                   u_int32_t numOfFrames);
      // additional MIDI data
      bool                  pitchBend(MidiValue v)          { return _paramManager.pitchBend(v); }
      bool                  midiCC(MidiCC c, MidiValue v)   { return _paramManager.midiCC(c, v); }
      // sub-module access
      WaveTableContainer&   getWavetables()                 { return _wavetables; }
      ParameterManager&     getParamManager()               { return _paramManager; }
      TrigTable&            getTrigTable()                  { return _trigTable;  }
#ifdef CACHE_MODULES
      friend ModuleCache&   Voice::voiceGetCoreModuleCache();
#endif
      // external parameter access
      const _parameterMap   getParamMap(eParameter p) const { return _paramManager.getParamMap(p); }
      ParamValue            getParamVal(eParameter p) const { return _paramManager.getValue(p); }
      bool                  setParam(eParameter p,
                                     ParamValue v)          { return _paramManager.setValue(p, v); }
    private:

#ifdef UNIT_TEST
      friend class UnitTest;
      size_t                _countActiveVoices()            { return voices.countActiveVoices(); }
#endif
      // modules
      VoiceManager          voices;
      FXModule              fx;
#ifndef VOL_IN_FXMODULE
      StereoVolume          masterVol;
#endif
#ifdef CACHE_MODULES
      // cached modules
      ModuleCache           _cache;
#endif
      // master modules
      ParameterManager      _paramManager;
      WaveTableContainer    _wavetables;
      TrigTable             _trigTable;
      // midi
      MidiNote              _lastNote;
      bool                  _initialised;

#ifndef SOUND_QUALITY_IN_FX
      AntiAlias           antiAliasFilter;
      DCFilter            dcFilter;
#endif
  };
}
#endif /* HOTPANTSCORE_H_ */
