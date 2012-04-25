/*
 * DCFilter.cpp
 *
 *  Created on: 12 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "DCFilter.hpp"

namespace hotpants {

  // desired DC filter -3dB frequency - 30Hz
  const float DCFilter::DCFreq = 30.0;

  void DCFilter::renderMono(Buffer* buffer, BlockSize frames)
  {
    SampleExternal out;
    for(BlockSize i = 0; i < frames; ++i) {
      out = buffer[i] - delayIn + (R * delayOut);
      delayIn = buffer[i];
      delayOut = out;
      buffer[i] = out;
    }
  }
}
