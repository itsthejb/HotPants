/*
 * MonoMixer.cpp
 *
 *  Created on: 13 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "Mixer.hpp"

#ifdef THREAD_SAFE
  #include <boost/thread/thread.hpp>
#endif

namespace hotpants {

  MonoMixer& MonoMixer::operator=(const MonoMixer& m)
  {
    if(this != &m) {
      this->buffers = m.buffers;
    }
    return *this;
  }

  MonoMixer::MonoMixer(const MonoMixer& m): ComponentSetup(m.core)
  {
    this->buffers = m.buffers;
  }

  void MonoMixer::addBuffer(SampleExternal* buffer, float amp)
  {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(mutex);
#endif
    buffers.push_back(MixerInputMono(buffer, amp));
  }

  void MonoMixer::renderMono(Buffer* outBuffer, BlockSize numFrames)
  {
#ifdef THREAD_SAFE
    boost::mutex::scoped_lock lock(mutex);
#endif

    // mix all voices to the output buffer
    BufferList::const_iterator iter;
    for(BlockSize i = 0; i < numFrames; i++)
    {
      outBuffer[i] = 0.0;
      // mix all voices
      for(iter = buffers.begin(); iter != buffers.end(); ++iter) {
        outBuffer[i] += ((*iter).buffer[i] * (*iter).amp);
      }
    }

    // clear the vector for the next cycle
    buffers.clear();
  }

}
