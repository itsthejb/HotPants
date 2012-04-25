/*
 * WaveTableContainer.hpp
 *
 * Object which constructs and stores
 * an array of all the available wavetables.
 *
 *  Created on: 23 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef WAVETABLES_H_
#define WAVETABLES_H_

#include "../../Include/TypesConstants.hpp"
#include "../../Include/Enums.hpp"
#include "../Interface/Interfaces.hpp"
#include "WaveTableBase.hpp"

namespace hotpants {

  class WaveTableContainer: public Component
  {
    public:
      explicit          WaveTableContainer(HotPantsCore&);
      virtual           ~WaveTableContainer();
      SampleInternal    getFrameFromTableAtIndex(eWaveform, IndexedValue);
    private:
      WaveTableBase*    _allTables[kNumOfAllWaves];
  };

  inline SampleInternal WaveTableContainer::getFrameFromTableAtIndex(eWaveform t, IndexedValue i)
  {
    return _allTables[t]->getFrameAtIndex(i);
  }

}
#endif /* WAVE_H_ */
