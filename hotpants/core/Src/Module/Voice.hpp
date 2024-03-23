/*
 * Voice.hpp
 *
 * Encapsulates a single (monophonic)
 * synthesiser "voice", following the main
 * synthesiser signal flow:
 *
 * Oscillators -> Filters -> Amplifier
 *
 * Modulator section is run at the start of a block
 * to modify the necessary global getParameters, before
 * rendering the components.
 *
 *  Created on: 18 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */


#ifndef VOICE_H_
#define VOICE_H_

#include "../../Include/TypesConstants.hpp"
#include "../Interface/Interfaces.hpp"
#include "VoiceModules.hpp"

namespace hotpants {

  class ModuleCache;

  class Voice: public ComponentSetup
  {
    public:
                          Voice(HotPantsCore& c);
      void                initialise(SamplingRate);
      void                attack(MidiNote, MidiNote, MidiVelocity);
      void                release()             { ampModule.release(); }
      void                fastRelease()         { ampModule.fastRelease(); }
      void                kill()                { ampModule.kill(); }
      void                reset()               { ampModule.reset(); }
      SampleInternal      getCurrentAmp() const { return ampModule.getCurrentAmp(); }
      bool                isSilent() const      { return ampModule.isSilent(); }
      SampleExternal*     getRenderedBuffer(BlockSize);

#ifdef CACHE_MODULES
      ModuleCache&        voiceGetCoreModuleCache();
#endif
    private:
      // sections
      OscModule           oscModule;
      FilterModule        filterModule;
      AmpModule           ampModule;
      ModModule           modModule;
      // buffer
      BufferMono          buffer;
      SamplingRate        samplingRate;
  };

} /* end: namespace hotpants */
#endif /* VOICE_H_ */
