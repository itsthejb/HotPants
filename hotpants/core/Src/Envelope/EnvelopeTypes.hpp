/*
 * EnvelopeTypes.hpp
 *
 * Static data and types for envelopes.
 *
 *  Created on: 9 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef ENVELOPETYPES_H_
#define ENVELOPETYPES_H_

namespace hotpants {

  // stages of a note's life-cycle
  // could be extended for more intersting envelopes
  enum EnvelopeStage
  {
    EnvStageAttack = 0, EnvStageDecay, EnvStageSustain, EnvStageRelease,
    _EnvStageNoteOff_,  _EnvStageMaxStages_
  };

  // releases
  // normal - key off
  // fast/kill - note stealing
  enum ReleaseType { Release_Normal = 0, Release_Fast, Release_Kill };

  // note state data structre
  typedef struct _envState
  {
      _envState():      duration(0), scale1(0.0), scale2(0.0), range(0.0), offset(0.0),
                        finalAmp(0.0), sustainFlag(false), nextState(_EnvStageNoteOff_) { }

      SampleDuration    duration;
      Percentage        scale1;
      Percentage        scale2;
      Percentage        range;
      SampleInternal    offset;
      Percentage        finalAmp;       // amp at the END of this stage
      bool              sustainFlag;
      EnvelopeStage     nextState;
  } StateStructure;

} /* end namespace hotpants */
#endif /* ENVELOPETYPES_H_ */
