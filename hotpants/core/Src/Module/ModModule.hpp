/*
 * ModModule.hpp
 *
 * Modulator module. Contains 2 x LFO,
 * 2 x envelopes. Some performance optimisation
 * particular with the LFOs, only updating
 * getParameters at the beginning of a rendering
 * block.
 *
 *  Created on: 6 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef MODSECTION_H_
#define MODSECTION_H_

#include "../../Include/TypesConstants.hpp"
#include "../Modulator/LFO.hpp"
#include "../Modulator/ModEnvelope.hpp"
#include "../Interface/Interfaces.hpp"

namespace hotpants {

  class ModModule: public ComponentSetup, CacheableModule, NoteResponder
  {
    public:
      explicit        ModModule(HotPantsCore&);
      void            initialise(SamplingRate);
      void            noteOn(MidiNote note, MidiVelocity velo);
      void            refresh();
      void            processBlock(BlockSize);
    private:
      LFO1            lfo1;
      LFO2            lfo2;
      ModEnvelope     env1;
      ModEnvelope     env2;
      float           veloMod;
      void            _initBuffer();
      void            _wipeBuffer();
  };
}
#endif /* MODSECTION_H_ */
