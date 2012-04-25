/*
 * DelayMono.hpp
 *
 * A single channel delay unit, containing a FIFO queue
 * to implement the delay buffer. This unit does not at
 * all write to the input buffer, merely uses it to
 * create a delayed version and provides a pointer.
 * This allows the delay to form a part of a large
 * delay unit such as the DelayStereo.
 *
 *  Created on: 17 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef MONODELAY_H_
#define MONODELAY_H_

#include "../Interface/Interfaces.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../Filter/Filters.hpp"

namespace hotpants {

  class DelayMono: public ComponentSetup, DynamicComponent
  {
    public:
      explicit            DelayMono(HotPantsCore& c, _delayMap ch)
                          : ComponentSetup(c), thisChannel(ch) { }
      void                initialise(SamplingRate);
      BufferMono&         getDelayBuffer(Buffer const*, BlockSize);
      void                refresh(eRefreshType);
    private:
      const _delayMap     thisChannel;
      DelayQueue          delayBuffer;
      BufferMono          output;
  };
}
#endif /* MONODELAY_H_ */
