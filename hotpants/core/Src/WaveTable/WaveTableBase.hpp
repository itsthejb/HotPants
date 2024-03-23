/*
 * WavetableBase.hpp
 *
 * Abstract base class for all kinds of getWavetables
 * Subclasses fill the protected table[] array when
 * constructed, using their own algorithm.
 *
 *  Created on: 10 June 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef WAVETABLE_H_
#define WAVETABLE_H_

#include "../../Include/TypesConstants.hpp"
#include "../../Include/Enums.hpp"
#include "../Interface/Interfaces.hpp"

#ifdef THREAD_SAFE
  #include <boost/thread/thread.hpp>
#endif

namespace hotpants
{
  class WaveTableBase
  {
    public:
                              WaveTableBase() {}
      virtual                 ~WaveTableBase() {}
      virtual eWaveform       getWaveForm() const =0;
      virtual SampleInternal  getFrameAtIndex(IndexedValue) const;
    protected:
      static unsigned int     calcMaxHarmonic() { return static_cast<unsigned int>(
                                                  kTableLength / 2 / kHarmonicScale); }
      // wavetable
      SampleInternal	        table[kTableLength];
#ifdef THREAD_SAFE
      // concurrency lock
      mutable boost::mutex    tableMutex;
#endif
  };

  inline SampleInternal WaveTableBase::getFrameAtIndex(IndexedValue i) const
  {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(tableMutex);
#endif
    return table[i % kTableLength];
  }

} /* end: namespace hotpants */
#endif /* WAVETABLE_H_ */
