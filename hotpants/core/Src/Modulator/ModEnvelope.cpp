/*
 * ModEnvelope.cpp
 *
 *  Created on: 27 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "ModEnvelope.hpp"
#include "../Utility/Utility.hpp"

namespace hotpants {

  SampleInternal ModEnvelope::getModValueForBlock(BlockSize b)
  {
    BufferUtils::resizeBuffer(buffer, b);
    buffer[0] = 1.0;
    renderMono(&buffer[0], b);
    return buffer[0];
  }

}
