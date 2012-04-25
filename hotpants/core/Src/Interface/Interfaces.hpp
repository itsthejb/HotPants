/*
 * Interfaces.hpp
 *
 * Base interfaces for internal components
 *
 *  Created on: 22 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef INTERFACES_H_
#define INTERFACES_H_

#include "../../Include/TypesConstants.hpp"
#include <cassert>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// samplingRate setting macro
#define _MACRO_SETSAMPLINGRATE_(x) {      \
    assert(r > 0.0); samplingRate = r; }  \
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace hotpants {

  class HotPantsCore;

  /*
   * class Component
   *
   * Base class for the majority of instrument components.
   * Must be constructed with a reference back to the HotPantsCore
   * object at the top of the tree.
   * Assignment operator need do nothing since the core reference
   * will never need to be reassigned; the core object will exist
   * throughout the life of the instrument.
   */
  class Component
  {
    public:
      explicit                Component(HotPantsCore& c): core(c) {}
      virtual                 ~Component() {}
      Component&              operator=(const Component& c)   { return *this; }
    protected:
      HotPantsCore&           core;
  };

  /*
   * class ComponentSetup
   *
   * Base class for most rendering components, which must be initialised
   * with a sampling rate in hertz, at some point after construction.
   */
  class ComponentSetup: public Component
  {
    public:
      explicit                ComponentSetup(HotPantsCore& c): Component(c) {}
      virtual                 ~ComponentSetup() {}
      virtual void            initialise(SamplingRate) =0;
    protected:
      SamplingRate            samplingRate;
  };

  /*
   * Pure virtual interfaces
   */

  // Mono input and output component
  class MonoRenderer {
    public:
      virtual                 ~MonoRenderer() {}
      virtual void            renderMono(Buffer*, BlockSize) =0;
  };

  // Component which takes mono input (left channel), and renders
  // a stereo output, including the right channel
  class MonoToStereoRenderer {
    public:
      virtual                 ~MonoToStereoRenderer() {}
      virtual void            renderMonoToStereo(Buffer*, Buffer*, BlockSize) =0;
  };

  // Stereo input and output
  class StereoRenderer {
    public:
      virtual                 ~StereoRenderer() {}
      virtual void            renderStereo(Buffer*, Buffer*, BlockSize) =0;
  };

  // component which responds to the specific midi note or velocity in
  // some way
  class NoteResponder {
    public:
      virtual                 ~NoteResponder() {}
      virtual void            noteOn(MidiNote, MidiVelocity) =0;
  };

  // modules which can be stored by a ModuleCache, checked and re-assigned,
  // or refreshed from the parameter manager using the refresh() method
  class CacheableModule {
    public:
      virtual                 ~CacheableModule() {}
      virtual void            refresh() =0;
  };

  // interface for most of the modules
  class Module: public CacheableModule, public ComponentSetup, MonoRenderer, NoteResponder {
    public:
      explicit                Module(HotPantsCore& c): ComponentSetup(c) {}
      virtual                 ~Module() {}
  };

  // components which have parameters that be be user-modified in real-time
  // thus, before each render cycle these parameters must be checked and refreshed.
  // at initialisation a refresh can be forced - see enum eRefreshType
  class DynamicComponent {
    public:
      virtual                 ~DynamicComponent() {}
    protected:
      virtual void            refresh(eRefreshType) =0;
  };

  // modulators which produce a single sample for the start of a rendering block
  class Modulator {
    public:
      virtual                 ~Modulator() {}
      virtual SampleInternal  getModValueForBlock(BlockSize) =0;
  };

}
#endif /* INTERFACES_H_ */
