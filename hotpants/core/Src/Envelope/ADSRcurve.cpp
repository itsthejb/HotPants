/*
 * ARSRcurve.cpp
 *
 *  Created on: 26 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "ADSRcurve.hpp"
#include "EnvelopeTypes.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../../Include/Compilation.hpp"
#include "../Core/HotPantsCore.hpp"
#include <cmath>

#ifdef CACHE_ENV
  #include <string.h>   // memcpy()
#endif

namespace hotpants {

  void ADSRcurve::createEnvelope(ADSRcurveParams& inParams)
  {
    // parameter check
    assert(inParams.sustainLevel >= 0.0   &&
           inParams.sustainLevel <= 100.0 &&
           inParams.timeScale    >= 0.0);

    // percent to decimal
    inParams.timeScale    *= kPercToDec;
    inParams.sustainLevel *= kPercToDec;

#ifdef CACHE_ENV

    /*
     * Envelope stage caching system:
     *
     * The previously used input parameters are stored
     * as lastParams, the previously calculated envelope
     * stages are stored in lastStateMachine[].
     *
     * Received input parameters are compared to those
     * stored from the last calculation, and re-used if
     * they haven't changed.
     *
     * NB: Due to the introduction of the ModuleCache,
     * this functionality's usefulness has been significantly
     * reduced. It may not be obsolete.
     */

    timeScaleUnchanged = attackUnchanged = decayUnchanged =
        sustainUnchanged = releaseUnchanged   = false;

    timeScaleUnchanged = Utility::fpEqual(inParams.timeScale,     lastParams.timeScale);
    // A time scale changes requires a full recalculation
    if(timeScaleUnchanged) {
      // examine individual stages
      attackUnchanged    = Utility::fpEqual(inParams.attackTime,  lastParams.attackTime);
      decayUnchanged     = Utility::fpEqual(inParams.decayTime,   lastParams.decayTime);
      sustainUnchanged   = Utility::fpEqual(inParams.sustainLevel,lastParams.sustainLevel);
      releaseUnchanged   = Utility::fpEqual(inParams.releaseTime, lastParams.releaseTime);
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif
    
    /*
     * ATTACK
     */
#ifdef CACHE_ENV
    // compare input to previous values
    if(timeScaleUnchanged && attackUnchanged && sustainUnchanged)
    {
      // A. no change - use cached values
      memcpy(&stateMachine[EnvStageAttack], 
             &lastStateMachine[EnvStageAttack], 
             sizeof(StateStructure));
    } else {
#endif
      // B1. changed - calculate for these input settings
      stateMachine[EnvStageAttack].nextState    = EnvStageDecay;
      stateMachine[EnvStageAttack].finalAmp     = kAmpMax;
      stateMachine[EnvStageAttack].range        = kAmpMax;
      stateMachine[EnvStageAttack].offset       = 0.0;
      stateMachine[EnvStageAttack].duration     = timeToSampleDuration(samplingRate,
                                                                       inParams.attackTime);
      if(stateMachine[EnvStageAttack].duration) {
        stateMachine[EnvStageAttack].scale1    =
        std::pow( static_cast<double>(inParams.timeScale/(inParams.timeScale+1)),
                 static_cast<double>(1.0/stateMachine[EnvStageAttack].duration));
        stateMachine[EnvStageAttack].scale2     = inParams.timeScale + 1;
      }
#ifdef CACHE_ENV
      // B2. cache the new values
      memcpy(&lastStateMachine[EnvStageAttack],
             &stateMachine[EnvStageAttack],
             sizeof(StateStructure));
    }
#endif

    /*
     * DECAY
     */
#ifdef CACHE_ENV
    // compare
    if(timeScaleUnchanged && decayUnchanged && sustainUnchanged)
    {
      // A.
      memcpy(&stateMachine[EnvStageDecay], 
             &lastStateMachine[EnvStageDecay], 
             sizeof(StateStructure));
    } else {      
#endif
      // B1.
      stateMachine[EnvStageDecay].nextState     = EnvStageSustain;
      stateMachine[EnvStageDecay].finalAmp      = inParams.sustainLevel;
      stateMachine[EnvStageDecay].range         = 1.0 - inParams.sustainLevel;
      stateMachine[EnvStageDecay].offset        = inParams.sustainLevel;
      stateMachine[EnvStageDecay].duration      = timeToSampleDuration(samplingRate,
                                                                       inParams.decayTime);
      if(stateMachine[EnvStageDecay].duration) {
        stateMachine[EnvStageDecay].scale1      =
            std::pow( static_cast<double>((timeScale+1)/inParams.timeScale),
                      static_cast<double>(1.0/stateMachine[EnvStageDecay].duration));
        stateMachine[EnvStageDecay].scale2      = inParams.timeScale;
      }
#ifdef CACHE_ENV
      // B2.
      memcpy(&lastStateMachine[EnvStageDecay],
             &stateMachine[EnvStageDecay],
             sizeof(StateStructure));
    }
#endif

    /*
     * SUSTAIN
     */
#ifdef CACHE_ENV
    // as before...
    if(sustainUnchanged)
    {
      // A.
      memcpy(&stateMachine[EnvStageSustain], 
             &lastStateMachine[EnvStageSustain], 
             sizeof(StateStructure));
    } else {  
#endif
      // B1.
      stateMachine[EnvStageSustain].nextState   = EnvStageRelease;
      stateMachine[EnvStageSustain].finalAmp    = inParams.sustainLevel;
      stateMachine[EnvStageSustain].duration    = kSustained;
      stateMachine[EnvStageSustain].sustainFlag = true;
      stateMachine[EnvStageSustain].scale1      = 1.0;
      stateMachine[EnvStageSustain].scale2      = 1.0;
#ifdef CACHE_ENV
      // B2.
      memcpy(&lastStateMachine[EnvStageSustain],
             &stateMachine[EnvStageSustain],
             sizeof(StateStructure));
    }
#endif

    /*
     * RELEASE
     */
#ifdef CACHE_ENV
    // ....
    if(timeScaleUnchanged && releaseUnchanged && sustainUnchanged)
    {
      // ...
      memcpy(&stateMachine[EnvStageRelease], 
             &lastStateMachine[EnvStageRelease], 
             sizeof(StateStructure));
    } else {  
#endif
      // ...
      stateMachine[EnvStageRelease].nextState   = _EnvStageNoteOff_;
      stateMachine[EnvStageRelease].finalAmp    = 0.0;
      stateMachine[EnvStageRelease].offset      = 0.0;      
      stateMachine[EnvStageRelease].duration    = timeToSampleDuration(samplingRate,
                                                                       inParams.releaseTime);
      calcRelease(inParams.sustainLevel,
                  inParams.timeScale,
                  Release_Normal);
#ifdef CACHE_ENV
      // ...
      memcpy(&lastStateMachine[EnvStageRelease],
             &stateMachine[EnvStageRelease],
             sizeof(StateStructure));
    }
#endif

    // Note off - final stage
    stateMachine[_EnvStageNoteOff_].nextState   = _EnvStageNoteOff_;
    stateMachine[_EnvStageNoteOff_].finalAmp    = 0.0;
    stateMachine[_EnvStageNoteOff_].duration    = kSustained;
    stateMachine[_EnvStageNoteOff_].scale1      = 0.0;
    stateMachine[_EnvStageNoteOff_].scale2      = 0.0;
    
    // general
    timeScale = inParams.timeScale;
    // ready for note on
    reset();
    
#ifdef CACHE_ENV
    // cache the last params
    memcpy(&lastParams, &inParams, sizeof(inParams));
#endif
  }
  
  void ADSRcurve::reset()
  {
    currentAmp   = 0.0;
    currentState = EnvStageAttack;
    released     = false;
  }

  void ADSRcurve::renderMono(Buffer* buffer, BlockSize numFrames)
  {
    for(BlockSize i = 0; i < numFrames; ++i)
    {
      // sustain or note off
      if(currentState == _EnvStageNoteOff_) currentAmp = 0.0;
      else if(stateMachine[currentState].sustainFlag && !released);
      else {
        // update amp
        currentAmp = (timeScale - stateMachine[currentState].scale2 + 1.0)
                      * stateMachine[currentState].range
                      + stateMachine[currentState].offset;

        // update state
        while( stateMachine[currentState].duration == 0 ||            // this stage has reached zero
              (stateMachine[currentState].sustainFlag && released))   // sustain stage reached
        {
          currentState = stateMachine[currentState].nextState;
        }

        // update scaling
        stateMachine[currentState].scale2 *= stateMachine[currentState].scale1;
        if(!stateMachine[currentState].sustainFlag)
          stateMachine[currentState].duration--;
      }

      // apply envelope
      buffer[i] *= currentAmp;
    }
  }

  void ADSRcurve::calcRelease(Percentage startLevel, double timeScale, ReleaseType speed)
  {
    if(speed == Release_Fast)
      stateMachine[EnvStageRelease].duration = static_cast<SampleDuration>(
          stateMachine[EnvStageRelease].duration / EnvFastReleaseScale);
    if(speed == Release_Kill)
      stateMachine[EnvStageRelease].duration = static_cast<SampleDuration>(
          stateMachine[EnvStageRelease].duration / EnvKillReleaseScale);

    // calculate the release
    stateMachine[EnvStageRelease].range       = startLevel;
    if(stateMachine[EnvStageRelease].duration > 0) {
      stateMachine[EnvStageRelease].scale1      =
        std::pow( static_cast<double>((timeScale+1)/timeScale),
                  static_cast<double>(1.0/stateMachine[EnvStageRelease].duration));
      stateMachine[EnvStageRelease].scale2      = timeScale;
    }
  }

  void ADSRcurve::release()
  {
    if(released)
      return;
    if(currentState < EnvStageSustain) {
      // early release - recalculate release stage
      calcRelease(currentAmp, timeScale, Release_Normal);
    }
    released = true;
    currentState = EnvStageRelease;
  }

  void ADSRcurve::fastRelease()
  {
    released = true;
    calcRelease(currentAmp, timeScale, Release_Fast);
    currentState = EnvStageRelease;
  }

  void ADSRcurve::kill()
  {
    // too abrupt?
    released = true;
    currentState = _EnvStageNoteOff_;
  }

} /* end namespace hotpants */
