/*
 * Filters.cpp
 *
 *  Created on: 26 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "Filters.hpp"
#include "../Core/HotPantsCore.hpp"
#include "../../Include/Enums.hpp"
#include "../../Include/Compilation.hpp"

namespace hotpants {

  void UserFilter::renderMono(Buffer* buffer, BlockSize numFrames)
  {
    // filter off?
    if(static_cast<eFilterType>(
        core.getParamManager().getValue(getThisFilter().type)) == kFiltType_Off)
      return;

    // settings need recalculating?
    refresh(kCHECK_FOR_UPDATES);
    RBJFilter::renderMono(buffer, numFrames);
  }

  void UserFilter::refresh(eRefreshType force)
  {
    // we need to have the user filter note
    assert(note);
    ParameterManager& p = core.getParamManager();

    // any getParameters changed?
    _filtMap thisFilt = getThisFilter();
    if(!force &&
       !p.paramModified(thisFilt.type)        &&   !p.paramModified(thisFilt.cutoff) &&
       !p.paramModified(thisFilt.q)           &&   !p.paramModified(thisFilt.gain)   &&
       !p.paramModified(kParam_FiltKeyTrack))
    {
      // parameters haven't changed
      return;
    }

#ifdef EXPECT_NO_PARAM_CHANGES
      if(!force)
        fprintf(stderr, "UserFilter::refresh() - parameter refresh when unexpected and unforced!\n");
#endif

    // recalculate the filter
    RBJFilter::recalculate(
          static_cast<eFilterType>(p.getValue(thisFilt.type)),
          // calculate cutoff with key-track scaling
          p.getValue(thisFilt.cutoff) + (note * p.getValue(kParam_FiltKeyTrack) * kPercToDec),
          kMaximumQ - p.getValue(thisFilt.q),     // Q is reversed
          p.getValue(thisFilt.gain)
          );
  }

  void DelayFilter::renderStereo(Buffer* l, Buffer* r, BlockSize s)
  {
    // superclass renders the left side
    RBJFilter::renderMono(l, s);
    float yn;
    for(IndexedValue i = 0; i < s; ++i) {
      // render the right channel
      yn = b0a0 * r[i] + b1a0 * rIn1 + b2a0 * rIn2 - a1a0 * rOu1 - a2a0 * rOu2;
      // push in/out buffers
      rIn2 = rIn1;
      rIn1 = r[i];
      rOu2 = rOu1;
      rOu1 = yn;
      // write output
      r[i] = yn;
    }
  }

  void DelayFilter::refresh(eRefreshType force)
  {
    if(force || core.getParamManager().paramModified(getThisFilter().cutoff))
    {
#ifdef EXPECT_NO_PARAM_CHANGES
      if(!force)
        fprintf(stderr, "DelayFilter::refresh() - parameter refresh when unexpected and unforced!\n");
#endif

      RBJFilter::recalculate(filterType(),
                             core.getParamManager().getValue(getThisFilter().cutoff),
                             kDelayFilterQ,
                             0.0);
    }
  }

} /* end namespace hotpants */
