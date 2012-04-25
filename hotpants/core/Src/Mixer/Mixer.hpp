/*
 * MonoMixer.hpp
 *
 * Voice mixer.
 * Receives pointers to rendered buffers,
 * until the render method is called, at which
 * point it will mix the stored buffers to the
 * provided output array.
 *
 *  Created on: 13 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef MIXER_H_
#define MIXER_H_

#include "../../Include/TypesConstants.hpp"
#include "../Interface/Interfaces.hpp"
#include "../../Include/Compilation.hpp"
#include <cassert>
#include <vector>

#ifdef THREAD_SAFE
  #include <boost/thread/thread.hpp>
#endif

namespace hotpants {

  // simple mixer container
  struct MixerInputMono {
      MixerInputMono(SampleExternal* b, float a): buffer(b), amp(a) {}
      SampleExternal*   buffer;
      float             amp;
  };
  typedef std::vector<MixerInputMono> BufferList;

  class MonoMixer: public ComponentSetup, MonoRenderer
  {
    public:
      explicit      MonoMixer(HotPantsCore& c): ComponentSetup(c) {}
      MonoMixer&    operator=(const MonoMixer&);
                    MonoMixer(const MonoMixer&);
      void          addBuffer(SampleExternal*, float);
      void          renderMono(Buffer*, BlockSize);
      void          initialise(SamplingRate r) { _MACRO_SETSAMPLINGRATE_(r); }
    private:
      BufferList    buffers;

#ifdef THREAD_SAFE
      mutable boost::mutex mutex;
#endif
  };

}
#endif /* MIXER_H_ */
