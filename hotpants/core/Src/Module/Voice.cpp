/*
 * Voice.cpp
 *
 *  Created on: 18 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "Voice.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../../Include/Compilation.hpp"
#include "../Core/HotPantsCore.hpp"
#include <cassert>
#include <map>
#include <utility>

namespace hotpants {

  Voice::Voice(HotPantsCore& c)
    : ComponentSetup(c), oscModule(c), filterModule(c), ampModule(c), modModule(c)
  {
    // reserve space for an expected minimum block size
    buffer.reserve(kBlockSize);
  }

  void Voice::initialise(SamplingRate r)
  {
    _MACRO_SETSAMPLINGRATE_(r);
    oscModule.initialise(r);
    filterModule.initialise(r);
    modModule.initialise(r);
    ampModule.initialise(r);
  }

  void Voice::attack(MidiNote newNote, MidiNote lastNote, MidiVelocity velo)
  {
    /*
     * Module caching system:
     *
     * For the amplifier, filter and modulator modules,
     * it is not always necessary to recalculate on note on.
     * If no getParameters pertaining to these modules have
     * been modified since the last note on, then we can
     * just copy the previous (cached) module, held by the
     * ModuleCache class.
     *
     * The moduleIsDirty flag is raised by the parameter manager
     * whenever a module parameter is modified and this can
     * be checked at note on as below.
     */

    ParameterManager& p = core.getParamManager();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Modulation module
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifdef CACHE_MODULES
    ModuleCache& cache = voiceGetCoreModuleCache();
    if(p.moduleIsDirty(eModule_Mod)) {
#endif
      // module is "dirty" and must be refreshed
      modModule.refresh();
#ifdef CACHE_MODULES
      // cache the refreshed module
      cache.setModModule(modModule);
    } else {
      // module is "clean" and can be re-used
      modModule = cache.getModModule();
    }
#endif

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Amplifier module
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifdef CACHE_MODULES
    if(p.moduleIsDirty(eModule_Amp)) {
#endif
      ampModule.refresh();
#ifdef CACHE_MODULES
      cache.setAmpModule(ampModule);
    } else {
      ampModule = cache.getAmpModule();
    }
#endif

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Filter module
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Module caching for the filters is a little more difficult
    // since it only works is key-tracking is turned off and the
    // filters are static
#ifdef CACHE_MODULES
    ParamValue filterKeyTrack = p.getValue(kParam_FiltKeyTrack);
    if(filterKeyTrack || p.moduleIsDirty(eModule_Filt)) {
#endif
      // filter caching not useful with key-tracking on
      filterModule.noteOn(newNote, velo);
      filterModule.refresh();
#ifdef CACHE_MODULES
      cache.setFilterModule(filterModule);
    } else {
      filterModule = cache.getFilterModule();
    }
#endif

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Essential note set-up!
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // the oscillator module can't be cached
    // initialised here
    oscModule.noteOn(newNote, velo);
    // calculate/set up portamento
    ParamValue porto = p.getValue(kParam_Portamento);
    if(porto && lastNote != kMidiNotANote && lastNote != newNote) {
      oscModule.setBend(lastNote, static_cast<SampleDuration>(porto * samplingRate));
    }

    // mod module needs the note velocity
    modModule.noteOn(newNote, velo);
    // amp module performs velocity scaling
    ampModule.noteOn(newNote, velo);
  }

  SampleExternal* Voice::getRenderedBuffer(BlockSize numFrames)
  {
    // set up buffer
    BufferUtils::resizeBuffer(buffer, numFrames);
    BufferUtils::wipeBuffer(buffer);
    // set modulations for this block
    modModule.processBlock(numFrames);
    // signal chain
    oscModule.   renderMono(&buffer[0], numFrames);
    filterModule.renderMono(&buffer[0], numFrames);
    ampModule.   renderMono(&buffer[0], numFrames);
    // return pointer to buffer data
    return &buffer[0];
  }

#ifdef CACHE_MODULES
  ModuleCache& Voice::voiceGetCoreModuleCache() { return core._cache; }
#endif

} /* end namespace hotpants */
