/*
 * FilterModule.hpp
 *
 * Filter module.
 * Contains two RBJ filters with switchable serial
 * or parallel connection and mix control.
 *
 *  Created on: 6 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef FILTERSECTION_H_
#define FILTERSECTION_H_

#include "../Interface/Interfaces.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../Filter/Filters.hpp"
#include "../Mixer/Mixer.hpp"

namespace hotpants {

  class FilterModule: public Module
  {
    public:
      explicit                FilterModule(HotPantsCore& c)
                              : Module(c), filt1(c), filt2(c), mixer(c) {}
      void                    initialise(SamplingRate);
      void                    refresh();
      void                    renderMono(Buffer*, BlockSize);
      void                    noteOn(MidiNote, MidiVelocity);
    private:
      Filter1                 filt1;
      Filter2                 filt2;
      MonoMixer               mixer;
      // parallel filtering requires local buffers
      BufferMono              filt1buffer;
      BufferMono              filt2buffer;
  };

}
#endif /* FILTERSECTION_H_ */
