/*
 * Filters.hpp
 *
 * Concrete filters.
 * A filter must be either built-in
 * filter1 or 2, or a static/fixed
 * filter, such as the DC filter and
 * anti-aliasing filter.
 * Fixed filters do not check the parameter
 * map for changes.
 *
 *  Created on: 21 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef FILTERS_H_
#define FILTERS_H_

#include "RBJFilter.hpp"
#include "../../Include/TypesConstants.hpp"
#include "../../Include/Enums.hpp"
#include "../../Include/ParamMaps.hpp"
#include <cassert>

namespace hotpants {

  /*
   * User Filters:
   * The main two visible, user-controllable filters
   */

  class UserFilter: public RBJFilter, DynamicComponent
  {
    public:
      explicit      UserFilter(HotPantsCore& c)
                    : RBJFilter(c), note(0.0), cutoffAdjust(0.0) { }
      void          renderMono(Buffer*, BlockSize);
      void          refresh(eRefreshType);
      void          setKeyTrackNote(NoteFrequency n) { assert(n); note = n; }
    protected:
      // key tracking - user filters only
      NoteFrequency note;
      ParamValue    cutoffAdjust;
  };

  class Filter1: public UserFilter
  {
    public:
      explicit      Filter1(HotPantsCore& c): UserFilter(c) {}
    protected:
      _filtMap      getThisFilter() const { return kFilterMap[kFilt1]; }
  };

  class Filter2: public UserFilter
  {
    public:
      explicit      Filter2(HotPantsCore& c): UserFilter(c) {}
    protected:
      _filtMap      getThisFilter() const { return kFilterMap[kFilt2]; }
  };

  /*
   * Fixed filters
   * Used internally
   */

  class FilterFixed: public RBJFilter
  {
    public:
      explicit      FilterFixed(HotPantsCore &c): RBJFilter(c) {}
      void          recalculate(eFilterType t, ParamValue v1,
                                ParamValue v2, ParamValue v3)
                    { RBJFilter::recalculate(t, v1, v2, v3); }
    protected:
      _filtMap      getThisFilter() const       { return kFilterMap[kFiltFixed]; }
    private:
      // can't be refreshed
      void          refresh(eRefreshType force) { return; }
  };

  /*
   * Delay filters
   * Used as part of the delay unit
   */

  class DelayFilter: public RBJFilter, StereoRenderer
  {
    public:
      explicit            DelayFilter(HotPantsCore& c)
                          : RBJFilter(c), rOu1(0.0), rOu2(0.0), rIn1(0.0), rIn2(0.0) {}
      void                renderStereo(Buffer*, Buffer*, BlockSize);
      void                refresh(eRefreshType);
    protected:
      // in/out history for other channel
      float               rOu1, rOu2, rIn1, rIn2;
      virtual eFilterType filterType() const =0;
    private:
      void                renderMono(Buffer* b, BlockSize s) {}
  };

  class DelayHighPass: public DelayFilter
  {
    public:
      explicit      DelayHighPass(HotPantsCore& c): DelayFilter(c) {}
    private:
      _filtMap      getThisFilter() const     { return kFilterMap[kFiltDelayHP]; }
      eFilterType   filterType() const        { return kFiltType_HP; }
  };

  class DelayLowPass: public DelayFilter
  {
    public:
      explicit      DelayLowPass(HotPantsCore& c): DelayFilter(c) {}
    private:
      eFilterType   filterType() const        { return kFiltType_LP; }
      _filtMap      getThisFilter() const     { return kFilterMap[kFiltDelayLP]; }
  };

}
#endif /* FILTERS_H_ */
