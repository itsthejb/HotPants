/*
 * ARSRcurve.hpp
 *
 * Only concrete envelope type.
 * ADSR, with curved, logarithmic
 * stages.
 *
 *  Created on: 26 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef ARSRCURVE_H_
#define ARSRCURVE_H_

#include "EnvelopeBase.hpp"
#include "../Interface/Interfaces.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../../Include/Compilation.hpp"
#include <cassert>

namespace hotpants {

  // parameters required for creating a filter of this type
  struct ADSRcurveParams 
  {
    ADSRcurveParams(TimeDuration a, TimeDuration d, Percentage s,
                    TimeDuration r, double t)
                    : attackTime(a),  decayTime(d), sustainLevel(s),
                      releaseTime(r), timeScale(t) { }
    
    TimeDuration      attackTime;
    TimeDuration      decayTime;
    Percentage        sustainLevel;
    TimeDuration      releaseTime;
    double            timeScale;
  };
  
  class ADSRcurve: public ComponentSetup, public EnvelopeBase, MonoRenderer
  {
    public:
      explicit                ADSRcurve(HotPantsCore& c): ComponentSetup(c)
#ifdef CACHE_ENV
                              ,lastParams(0.0, 0.0, 0.0, 0.0, 0.0)
#endif
                              {}
      void                    initialise(SamplingRate r)  { _MACRO_SETSAMPLINGRATE_(r); }
      void                    createEnvelope(ADSRcurveParams&);
      bool                    isSilent() const;
      void                    fastRelease();
      void                    release();
      void                    kill();
      void                    reset();
      void                    renderMono(Buffer*, BlockSize);
    private:
      void                    calcRelease(Percentage, double, ReleaseType);

#ifdef CACHE_ENV
      // parameter checking bools
      bool timeScaleUnchanged, attackUnchanged, decayUnchanged,
           sustainUnchanged, releaseUnchanged;
      // cached values for efficiency savings
      ADSRcurveParams         lastParams;
      StateStructure          lastStateMachine[_EnvStageMaxStages_];
#endif
  };

  inline bool ADSRcurve::isSilent() const {
    return (currentState == _EnvStageNoteOff_ || currentAmp == 0.0);
  }

} // end namespace hotpants
#endif /* ARSRCURVE_H_ */
