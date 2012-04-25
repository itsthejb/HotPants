/*
 * Wave.cpp
 *
 *  Created on: 23 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "WaveTableContainer.hpp"
#include "AllWaveTables.hpp"
#include "../../Include/Enums.hpp"

namespace hotpants {

  WaveTableContainer::WaveTableContainer(HotPantsCore& c): Component(c)
  {
    // indexed available getWavetables
    _allTables[kWave_SineDirect]  = new SineDirect();
    _allTables[kWave_TriPartial]  = new TriPartial();
    _allTables[kWave_SawPartial]  = new SawPartial();
    _allTables[kWave_SquareFixed] = new SquarePartial();
    // wrapped
    _allTables[kWave_PulsePWM]    = new PulsePWM(c);
    _allTables[kWave_Noise]       = new NoiseWrapper();
    // LFO-only waveforms
    _allTables[kWave_TriDirect]   = new TriDirect();
    _allTables[kWave_SawDirect]   = new SawDirect();

    for(eWaveform i  = kFirstWaveform;
                  i != kNumOfAllWaves;
                  i  = static_cast<eWaveform>(i + 1))
    {
      // tables should match up in the array
      assert(_allTables[i]->getWaveForm() == i);
    }
  }

  WaveTableContainer::~WaveTableContainer()
  {
    for(eWaveform i  = kFirstWaveform;
                  i != kNumOfAllWaves;
                  i  = static_cast<eWaveform>(i + 1))
    {
      delete _allTables[i];
    }
  }

}
