/*
 * OscillatorBase.cpp
 *
 *  Created on: 27 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "OscillatorBase.hpp"
#include "../Core/HotPantsCore.hpp"
#include "../Utility/Utility.hpp"
#include "../../Include/Compilation.hpp"

namespace hotpants {

  OscillatorBase::OscillatorBase(HotPantsCore& c)
  : ComponentSetup(c), frequency(0.0), amp(0.0), tuningScale(1.0),
    wave(kWave_SineDirect), indexInc(0.0), indexFP(0.0), sample(0.0), tableFreq(0.0)
  {
    // pointer to the core object's wavetables
    wavetables = &core.getWavetables();
  }

  void OscillatorBase::refresh(eRefreshType force)
  {
    assert(samplingRate && tableFreq);

    // these values are stored to prevent parameter access
    // during rendering cycle
    _MACRO_GET_AMP_WAVE_

    // refresh local tuning
    if(force || core.getParamManager().paramModified(getThisOsc().tuning))
    {
#ifdef EXPECT_NO_PARAM_CHANGES
      if(!force)
        fprintf(stderr, "OscillatorBase::refresh() - parameter refresh when unexpected and unforced!\n");
#endif

      tuningScale = Utility::calcTuning(core.getParamManager().getValue(getThisOsc().tuning));
      calcIndexInc();
    }
  }

  void OscillatorBase::initialise(SamplingRate r)
  {
    _MACRO_SETSAMPLINGRATE_(r);
    tableFreq = static_cast<double>(kTableLength) / r;
    assert(tableFreq > 0.0);
  }

}
