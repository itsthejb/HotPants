/*
 * Compilation.hpp
 *
 * Preprocessor conditional compilation
 * options; performance, debugging, multi-threading.
 *
 *  Created on: 24 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef CONDITIONALCOMPILATION_H_
#define CONDITIONALCOMPILATION_H_

// Compilation options
#define TRIG_TABLE                  // do trigonometry using internal wavetables?
#define REFRESH_CHECK               // enable refresh performance enhancements
#define TRIG_INTERPOLATE            // perform interpolation on these results?
#define CACHE_MODULES               // cache voice modules??
#define PARAM_SMOOTHING             // low-pass filter parameter changes?
#define VOL_IN_FXMODULE             // master volume control in fx or hotpantscore?
#define SOUND_QUALITY_IN_FX         // sound quality filters in FX module? or core?

// Disabled options
//#define CACHE_ENV                   // cache individual envelope stages?
//#define DEDICATED_TRIG_TABLE        // TrigTable class has its own sine wave table
//#define SCALE_DOWN_OSCS             // divid oscillator vol by number of oscs?
//#define WTABLE_CONST_HARMONICS      // use fixed harmonics defined in TypesConstants.hpp

// Boost library:
#ifdef BOOST
  #define THREAD_SAFE                 // thread-safe version (mutex locking)
  #ifdef THREAD_SAFE
    //#define MULTITHREAD               // Boost multi-thread voice rendering
    #undef DEDICATED_TRIG_TABLE       // seems to conflict with boost mutexing
  #endif
#endif

#endif /* CONDITIONALCOMPILATION_H_ */
