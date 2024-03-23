/*
 * OscModule.hpp
 *
 * Oscillator module. Contains 3 wavetable
 * oscillators, hard mixed.
 *
 *  Created on: 27 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef OSCSECTION_H_
#define OSCSECTION_H_

#include "../../Include/Enums.hpp"
#include "../Interface/Interfaces.hpp"
#include "../Oscillator/AudioOsc.hpp"

namespace hotpants {

  class OscModule: public Module
  {
    public:
      explicit              OscModule(HotPantsCore &c)
                            : Module(c), osc1(c), osc2(c), osc3(c), note(0) {}
      void                  initialise(SamplingRate);
      void                  refresh() { /* no functionality required */ }
      void                  noteOn(MidiNote, MidiVelocity);
      void                  setBend(MidiNote, SampleDuration);
      void                  renderMono(Buffer*, BlockSize);
    private:
      Osc1                  osc1;
      Osc2                  osc2;
      Osc3                  osc3;
      MidiNote              note;
  };

} /* end namespace hotpants */
#endif /* OSCSECTION_H_ */
