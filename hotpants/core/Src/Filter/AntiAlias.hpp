/*
 * AntiAlias.hpp
 *
 * Anti-aliasing filter.
 * Composed of RBJ low-pass and high-pass
 * fixed filters in series.
 *
 *  Created on: 22 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef ANTIALIAS_H_
#define ANTIALIAS_H_

#include "Filters.hpp"
#include "../../Include/TypesConstants.hpp"

namespace hotpants {

  class AntiAlias: public FilterFixed
  {
    public:
      explicit      AntiAlias(HotPantsCore& c)
                    : FilterFixed(c), hipass(c), lowpass(c) {}
      void          initialise(SamplingRate);
      void          renderMono(Buffer*, BlockSize);
    private:
      FilterFixed   hipass;
      FilterFixed   lowpass;
  };
}
#endif /* ANTIALIAS_H_ */
