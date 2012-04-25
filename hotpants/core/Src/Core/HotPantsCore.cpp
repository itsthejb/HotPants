/*
 * HotPantsCore.cpp
 *
 *  Created on: 11 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "HotPantsCore.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../../Include/Presets.hpp"
#include <cassert>

namespace hotpants {

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Constructor / setSamplingRate / destructor
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  HotPantsCore::HotPantsCore()
  : voices(*this), fx(*this),
#ifndef VOL_IN_FXMODULE
    masterVol(*this),
#endif
#ifdef CACHE_MODULES
    _cache(*this),
#endif
    _paramManager(*this), _wavetables(*this), _trigTable(*this),
    _lastNote(kMidiNotANote), _initialised(false)
#ifndef SOUND_QUALITY_IN_FX
    ,antiAliasFilter(*this), dcFilter(*this)
#endif
  {
    // check that all presets are correctly configured
    for(eFactoryPreset i = kFirstPreset;
                       i < kNumOfPresets;
                       i = static_cast<eFactoryPreset>(i+1))
    {
      // presets in correct order?
      if(kFactoryPresets[i].enumVal != i) {
        fprintf(stderr, "kFactoryPresets enum correlation error: preset %d\n", i);
        assert(false);
      }

      // check each parameter setting is in order
      for(eParameter p = kFirstParam; p != kNumOfParams; p = static_cast<eParameter>(p+1)) {
        if(kFactoryPresets[i].parameter[p].enumVal != p)
        {
          fprintf(stderr, "kFactoryPresets correlation error: preset %d, parameter %d\n", i, p);
          assert(false);
        }
      }
    }
    // initialise static utilities
    Utility::initialise();
  }

  bool HotPantsCore::initialise(SamplingRate r)
  {
    if(r <= 0.0)
      return false;
    voices.initialise(r);
    fx.initialise(r);

#ifndef SOUND_QUALITY_IN_FX
    antiAliasFilter.initialise(r);
    dcFilter.initialise(r);
#endif

    _initialised = true;
    return _initialised;
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Render
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  bool HotPantsCore::render(float* leftBuffer, float* rightBuffer, u_int32_t numOfFrames)
  {
    if(!_initialised)
      return false;

    // prepare parameters
    _paramManager.prepareForRender();
    // render all notes
    voices.renderAllVoices(leftBuffer, numOfFrames);
#ifndef SOUND_QUALITY_IN_FX
    // sound quality filtering
    antiAliasFilter.renderMono(leftBuffer, numOfFrames);
    dcFilter.renderMono(leftBuffer, numOfFrames);
#endif

    // external effects
    fx.renderMonoToStereo(leftBuffer,  rightBuffer, numOfFrames);

#ifndef VOL_IN_FXMODULE
    // master output volume control
    masterVol.renderStereo(leftBuffer, rightBuffer, numOfFrames);
#endif
    return true;
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Note creation / destruction
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  bool HotPantsCore::startNote (NoteUniqueId  ID,
                                MidiNote      notePitch,
                                MidiVelocity  noteVelocity)
  {
    if(!_initialised)
      return false;

    // change note is valid
    if(notePitch < kMidiNoteMin || notePitch > kMidiNoteMax)
      return false;

    assert(_initialised);
    Voice* newVoice = 0;

    // is the note already active?
    if(voices.isNoteActive(ID))
      return false;

    newVoice = voices.getVoice(ID);
    // should always have a voice now!
    assert(newVoice);

    // activate
    newVoice->attack(notePitch, _lastNote, noteVelocity);
    _lastNote = notePitch;
    return true;
  }

  bool HotPantsCore::stopNote(NoteUniqueId ID)
  {
    if(!_initialised)
      return false;
    return voices.stopVoice(ID);
  }

}
