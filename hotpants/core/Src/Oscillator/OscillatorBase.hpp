/*
 * OscillatorBase.hpp
 *
 * Abstract base class for wavetable oscillators.
 * Require specialisations to model the component
 * that they actually represent.
 *
 *  Created on: 27 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef OSCBASE_H_
#define OSCBASE_H_

#include "../../Include/TypesConstants.hpp"
#include "../Interface/Interfaces.hpp"
#include "../../Include/ParamTypes.hpp"
#include <cmath>

// Macros for heavy use routines
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Get amp and wave
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define _MACRO_GET_AMP_WAVE_ {                                                          \
    amp  = core.getParamManager().getValue(getThisOsc().amp);                           \
    wave = static_cast<eWaveform>(core.getParamManager().getValue(getThisOsc().wave));  \
  }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace hotpants {

  class WaveTableContainer;

  class OscillatorBase: public ComponentSetup, DynamicComponent
  {
    public:
      explicit                OscillatorBase(HotPantsCore& c);
      virtual void            initialise(SamplingRate);
    protected:
      virtual void            refresh(eRefreshType);
      virtual const _oscMap&  getThisOsc() const =0;
      void                    calcIndexInc() { indexInc = tableFreq * frequency; }
      // render cycle values
      NoteFrequency           frequency;
      ParamValue              amp;
      double                  tuningScale;
      eWaveform               wave;
      // index counter variables
      IndexFPValue            indexInc;
      IndexFPValue            indexFP;
      // caching - current sample
      SampleInternal          sample;
      // core's wavetable container
      WaveTableContainer*     wavetables;
      // fundamental frequency of wavetable at current sampling rate
      double                  tableFreq;
  };

} /* end namespace hotpants */
#endif /* OSCBASE_H_ */
