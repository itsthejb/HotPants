/*
 * Noise.hpp
 *
 * Simple white noise generator,
 * using C-standard library rand() functionality.
 *
 *  Created on: 18 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef NOISE_H_
#define NOISE_H_

#include "../Interface/Interfaces.hpp"
#include "../../Include/TypesConstants.hpp"
#include <ctime>
#include <cstdlib>

namespace hotpants {

  class Noise
  {
    public:
                      Noise() { std::srand( time(NULL) ); }
      SampleInternal  getNextSample() const;
  };

  inline SampleInternal Noise::getNextSample() const
  {
    return (rand() / static_cast<SampleInternal>(RAND_MAX / kAmpRange) - kAmpMax);
  }

} /* end namespace hotpants */
#endif /* NOISE_H_ */
