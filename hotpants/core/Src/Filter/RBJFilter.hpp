/*
 * RBJFilter.hpp
 *
 * Implementation of Robert Bristow-Johnson's <rbj@audioimagination.com>
 * Audio EQ Cook Book filters.
 * Code adapted from that provided by arguru@smartelectronix.com.
 * For more information, see note below.
 *
 * NB: This module is cited/non-original code!
 *
 *  Created on: 22 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */
/*
 * RBJ Audio EQ Cook book:
 * http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt
 * Original implementation:
 * http://www.musicdsp.org/files/CFxRbjFilter.h
 */

#ifndef RBJFILTER_H_
#define RBJFILTER_H_

#include "../Interface/Interfaces.hpp"
#include "../../Include/Enums.hpp"
#include "../../Include/ParamTypes.hpp"
#include "../../Include/TypesConstants.hpp"

namespace hotpants {

  class RBJFilter: public ComponentSetup, MonoRenderer
  {
    public:
      explicit              RBJFilter(HotPantsCore&);
      void                  initialise(SamplingRate);
      virtual void          renderMono(Buffer*, BlockSize);
    protected:
      virtual _filtMap      getThisFilter() const =0;
      void                  recalculate(eFilterType, ParamValue, ParamValue, ParamValue);
      // in/out history
      float                 ou1,ou2,in1,in2;
      // filter coeffs
      float                 b0a0,b1a0,b2a0,a1a0,a2a0;
    private:
      // temp coef vars
      double                alpha,a0,a1,a2,b0,b1,b2;
  };
}
#endif /* RBJFILTER_H_ */
