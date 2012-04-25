/*
 * AmpModule.hpp
 *
 * The amplifier module. Wraps a single ADSRcurve
 * envelope, although also provides velocity
 * sensitivity control.
 *
 *  Created on: 6 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef AMPSECTION_H_
#define AMPSECTION_H_

#include "../Interface/Interfaces.hpp"
#include "../Envelope/ADSRcurve.hpp"
#include "../../Include/TypesConstants.hpp"
#include <cmath>

namespace hotpants {

  class AmpModule: public Module
  {
    public:
      explicit              AmpModule(HotPantsCore& c)
                            : Module(c), ampEnvelope(c), velocityScale(1.0) {}
      void                  initialise(SamplingRate);
      void                  refresh();
      void                  noteOn(MidiNote, MidiVelocity);
      void                  release()             { ampEnvelope.release(); }
      void                  fastRelease()         { ampEnvelope.fastRelease(); }
      void                  kill()                { ampEnvelope.kill(); }
      void                  reset()               { ampEnvelope.reset(); }
      void                  renderMono(Buffer*, BlockSize);
      SampleInternal        getCurrentAmp() const { return ampEnvelope.getCurrentAmp(); }
      bool                  isSilent() const      { return ampEnvelope.isSilent(); }
    private:
      void                  calcVelocty(MidiVelocity);
      ADSRcurve             ampEnvelope;
      double                velocityScale;
  };
}
#endif /* AMPSECTION_H_ */
