/*
 * RBJFilter.cpp
 *
 * NB: Please see note in RBJFilter.hpp regarding the
 * origin of this code.
 *
 *  Created on: 22 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "RBJFilter.hpp"
#include "../../Include/Compilation.hpp"

#ifdef TRIG_TABLE
  #include "../Core/HotPantsCore.hpp"
  #define TRIG(x) core.getTrigTable().x
#else
  #include <cmath>
  #define TRIG(x) std::x
#endif

namespace hotpants {

  RBJFilter::RBJFilter(HotPantsCore& c)
  : ComponentSetup(c),
    ou1(0.0), ou2(0.0), in1(0.0), in2(0.0),
    b0a0(0.0), b1a0(0.0), b2a0(0.0), a1a0(0.0), a2a0(0.0),
    alpha(0.0), a0(0.0), a1(0.0), a2(0.0), b0(0.0), b1(0.0), b2(0.0)
  { }

  void RBJFilter::initialise(SamplingRate r)
  {
    _MACRO_SETSAMPLINGRATE_(r);
    // reset co-efficients
    b0a0=b1a0=b2a0=a1a0=a2a0=0.0;
  }

  void RBJFilter::renderMono(Buffer* buffer, BlockSize numFrames)
  {
    // render the filter
    float yn;
    for(IndexedValue i = 0; i < numFrames; ++i)
    {
      yn = b0a0*buffer[i] + b1a0*in1 + b2a0*in2 - a1a0*ou1 - a2a0*ou2;

      // push in/out buffers
      in2=in1;
      in1=buffer[i];
      ou2=ou1;
      ou1=yn;

      // write output
      buffer[i] = yn;
    }
  }

  void RBJFilter::recalculate(eFilterType type,
                              ParamValue  frequency,
                              ParamValue  q,
                              ParamValue  gain)
  {
    // this can be a parameter
    const bool q_is_bandwidth = true;

    // peaking, lowshelf and hishelf
    if(type == kFiltType_Peaking  ||
       type == kFiltType_LowShelf ||
       type == kFiltType_HiShelf)
    {
      double const A     = pow(10.0,(gain/40.0));
      double const omega = 2.0*kPi*frequency/samplingRate;

      double const tsin  = TRIG(sin(omega));
      double const tcos  = TRIG(cos(omega));

      if(q_is_bandwidth)
        alpha=tsin*sinh(log(2.0)/2.0*q*omega/tsin);
      else
        alpha=tsin/(2.0*q);

      double const beta = sqrt(A)/q;

      // peaking
      if(type == kFiltType_Peaking)
      {
        b0 = static_cast<float>(1.0+alpha*A);
        b1 = static_cast<float>(-2.0*tcos);
        b2 = static_cast<float>(1.0-alpha*A);
        a0 = static_cast<float>(1.0+alpha/A);
        a1 = static_cast<float>(-2.0*tcos);
        a2 = static_cast<float>(1.0-alpha/A);
      }

      // lowshelf
      if(type == kFiltType_LowShelf)
      {
        b0 = static_cast<float>(A*((A+1.0)-(A-1.0)*tcos+beta*tsin));
        b1 = static_cast<float>(2.0*A*((A-1.0)-(A+1.0)*tcos));
        b2 = static_cast<float>(A*((A+1.0)-(A-1.0)*tcos-beta*tsin));
        a0 = static_cast<float>((A+1.0)+(A-1.0)*tcos+beta*tsin);
        a1 = static_cast<float>(-2.0*((A-1.0)+(A+1.0)*tcos));
        a2 = static_cast<float>((A+1.0)+(A-1.0)*tcos-beta*tsin);
      }

      // hishelf
      if(type == kFiltType_HiShelf)
      {
        b0 = static_cast<float>(A*((A+1.0)+(A-1.0)*tcos+beta*tsin));
        b1 = static_cast<float>(-2.0*A*((A-1.0)+(A+1.0)*tcos));
        b2 = static_cast<float>(A*((A+1.0)+(A-1.0)*tcos-beta*tsin));
        a0 = static_cast<float>((A+1.0)-(A-1.0)*tcos+beta*tsin);
        a1 = static_cast<float>(2.0*((A-1.0)-(A+1.0)*tcos));
        a2 = static_cast<float>((A+1.0)-(A-1.0)*tcos-beta*tsin);
      }
    }
    else
    {
      // other filters
      double const omega = 2.0*kPi*frequency/samplingRate;
      double const tsin  = TRIG(sin(omega));
      double const tcos  = TRIG(cos(omega));

      if(q_is_bandwidth)
        alpha=tsin*sinh(log(2.0)/2.0*q*omega/tsin);
      else
        alpha=tsin/(2.0*q);

      // lowpass
      if(type == kFiltType_LP)
      {
        b0=(1.0-tcos)/2.0;
        b1=1.0-tcos;
        b2=(1.0-tcos)/2.0;
        a0=1.0+alpha;
        a1=-2.0*tcos;
        a2=1.0-alpha;
      }

      // hipass
      if(type == kFiltType_HP)
      {
        b0=(1.0+tcos)/2.0;
        b1=-(1.0+tcos);
        b2=(1.0+tcos)/2.0;
        a0=1.0+ alpha;
        a1=-2.0*tcos;
        a2=1.0-alpha;
      }

      // bandpass csg
      if(type == kFiltType_BP_CSG)
      {
        b0=tsin/2.0;
        b1=0.0;
        b2=-tsin/2;
        a0=1.0+alpha;
        a1=-2.0*tcos;
        a2=1.0-alpha;
      }

      // bandpass czpg
      if(type == kFiltType_BP_CZPG)
      {
        b0=alpha;
        b1=0.0;
        b2=-alpha;
        a0=1.0+alpha;
        a1=-2.0*tcos;
        a2=1.0-alpha;
      }

      // notch
      if(type == kFiltType_Notch)
      {
        b0=1.0;
        b1=-2.0*tcos;
        b2=1.0;
        a0=1.0+alpha;
        a1=-2.0*tcos;
        a2=1.0-alpha;
      }

      // allpass
      if(type == kFiltType_AllPass)
      {
        b0=1.0-alpha;
        b1=-2.0*tcos;
        b2=1.0+alpha;
        a0=1.0+alpha;
        a1=-2.0*tcos;
        a2=1.0-alpha;
      }
    }

    // set filter coeffs
    b0a0 = static_cast<float>(b0/a0);
    b1a0 = static_cast<float>(b1/a0);
    b2a0 = static_cast<float>(b2/a0);
    a1a0 = static_cast<float>(a1/a0);
    a2a0 = static_cast<float>(a2/a0);
  }

} /* end namespace hotpants */
