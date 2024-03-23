/*
 * AudioOsc.hpp
 *
 * OscillatorBase specialisations for the 3 built-in
 * oscillators. Oscillator 1 has special functionality
 * to support inter-oscillator modulations (FM/RM/AM).
 * Over-rides the renderMono() method to apply the
 * relevant function.
 *
 *  Created on: 20 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef OSCS_H_
#define OSCS_H_

#include "OscillatorBase.hpp"
#include "../Interface/Interfaces.hpp"
#include "../../Include/ParamMaps.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../WaveTable/WaveTableContainer.hpp"
#include <cassert>

namespace hotpants {

  class AudioOsc: public OscillatorBase, MonoRenderer
  {
    public:
      explicit            AudioOsc(HotPantsCore& c)
                          : OscillatorBase(c),
                            globalTuning(1.0),  analogueRandom(0.0),
                            portoIndexInc(0.0), portoDuration(0),
                            portoCounter(0),    lastTableReadPos(0) { }
      void                setFrequency(NoteFrequency);
      void                setBend(NoteFrequency, SampleDuration);
      virtual void        renderMono(Buffer*, BlockSize);
    protected:
      virtual void        refresh(eRefreshType);
      virtual void        advanceFrames(IndexFPValue);
      void                getNextSample();
      // tuning
      ParamValue          globalTuning;
      double              analogueRandom;
      // portamento
      IndexFPValue        portoIndexInc;
      SampleDuration      portoDuration;
      SampleDuration      portoCounter;
      // caching
      IndexedValue        lastTableReadPos;
  };

  // heavy use function
  inline void AudioOsc::advanceFrames(IndexFPValue f) {
    // portamento
    if(portoCounter < portoDuration) {
      indexInc += portoIndexInc; portoCounter++;
    }

    // advance the index position
    indexFP += (indexInc + f) * globalTuning;
    // reset phase if necessary
    while(indexFP >= kTableLength) {
      indexFP -= kTableLength;
      lastTableReadPos = 0;
    }
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // Get next wavetable sample, or re-use cached value
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  inline void AudioOsc::getNextSample() {
    if((indexFP - lastTableReadPos) >= 1.0) {                                                                                   \
      lastTableReadPos = static_cast<IndexedValue>(indexFP);
      sample           = wavetables->getFrameFromTableAtIndex(wave, lastTableReadPos);
    }
  }

  class Osc1: public AudioOsc {
    public:
      explicit          Osc1(HotPantsCore& c): AudioOsc(c) {}
      void              renderMono(Buffer*, BlockSize);
    private:
      // osc modulations
      void              renderAM(Buffer*, BlockSize);
      void              renderRM(Buffer*, BlockSize);
      void              renderFM(Buffer*, BlockSize);
      const _oscMap&    getThisOsc() const { return kOscMap[kOsc1]; }
  };

  class Osc2: public AudioOsc {
    public:
      explicit          Osc2(HotPantsCore& c): AudioOsc(c) {}
    protected:
      void              refresh(eRefreshType);
    private:
      const _oscMap&    getThisOsc() const { return kOscMap[kOsc2]; }
  };

  class Osc3: public AudioOsc {
    public:
      explicit          Osc3(HotPantsCore& c): AudioOsc(c) {}
    private:
      const _oscMap&    getThisOsc() const { return kOscMap[kOsc3]; }
  };

} /* end namespace hotpants */
#endif
