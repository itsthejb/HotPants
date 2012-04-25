/*
 * EnvelopeBase.hpp
 *
 * Base class and interface for all kinds of
 * envelopes
 *
 *  Created on: 24 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef ENVELOPEBASE_H_
#define ENVELOPEBASE_H_

#include "../../Include/TypesConstants.hpp"
#include "../Interface/Interfaces.hpp"
#include "EnvelopeTypes.hpp"

namespace hotpants {

  class EnvelopeBase
  {
    public:
                              EnvelopeBase(): currentAmp(0.0), currentState(_EnvStageNoteOff_),
                                              released(false), timeScale(1.0) { }
      virtual                 ~EnvelopeBase() {}
      SampleInternal          getCurrentAmp() const       { return currentAmp; }
      virtual bool            isSilent() const =0;
      virtual void            release() =0;
      virtual void            fastRelease() =0;
      virtual void            kill() =0;
      virtual void            reset() =0;
      // static helper & constants
      static SampleDuration   timeToSampleDuration(SamplingRate, TimeDuration);
    protected:
      StateStructure          stateMachine[_EnvStageMaxStages_];
      SampleInternal          currentAmp;
      EnvelopeStage           currentState;
      bool                    released;
      double                  timeScale;
      static const double     EnvFastReleaseScale;
      static const double     EnvKillReleaseScale;
  };

  inline SampleDuration EnvelopeBase::timeToSampleDuration(SamplingRate rate, TimeDuration t)
  {
    return static_cast<SampleDuration>((static_cast<float>(t) * static_cast<float>(rate)));
  }

} /* end namespace hotpants */
#endif /* ENVELOPEBASE_H_ */
