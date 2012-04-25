/*
 *  HotPants.hpp
 *
 *  Main AudioUnit header file
 *
 *  Framework Template:
 *  -------------------
 *  Created by Mehul Trivedi on 9/12/06.
 *  Copyright 2006 Apple Inc. All rights reserved.
 *
 *  Customisations:
 *  ---------------
 *  From May 2010, Jonathan Crooke (jc9873@bris.ac.uk)
 */

#include "AUInstrumentBase.h"
#include "HotPantsVersion.h"
#include "../CoreInclude.hpp"
#include "ParamMapping.h"

class HotPants: public AUMonotimbralInstrumentBase
{
  public:
                            HotPants(ComponentInstance inComponentInstance);
    OSStatus                Initialize();
    OSStatus                Version() { return kHotPantsVersion; }
    // parameters
	  OSStatus                GetParameterInfo(AudioUnitScope, AudioUnitParameterID, AudioUnitParameterInfo&);
    OSStatus                GetParameterValueStrings(AudioUnitScope, AudioUnitParameterID, CFArrayRef*);
    // note life-cycle
    OSStatus                Render(AudioUnitRenderActionFlags&, const AudioTimeStamp&, UInt32);
    OSStatus                RealTimeStartNote(SynthGroupElement*, NoteInstanceID, UInt32, const MusicDeviceNoteParams&);
    OSStatus                RealTimeStopNote(MusicDeviceGroupID, NoteInstanceID, UInt32);
    // midi input
    OSStatus                HandleControlChange(UInt8, UInt8, UInt8, UInt32);
    OSStatus                HandlePitchWheel(UInt8,UInt8,UInt8,UInt32);
    // properties
    bool                    SupportsTail()  { return true; }
    Float64                 GetTailTime()   { return hotpants::kMaxTailTime; }
    // presets
    OSStatus                GetPresets(CFArrayRef *) const;
    OSStatus                NewFactoryPresetSet (const AUPreset&);
  private:
    // instrument object
    hotpants::HotPantsCore  core;
    void                    setDefaultParameters();
    void                    refreshAllParameters();
    void                    checkAUmapping();
};

inline void HotPants::refreshAllParameters()
{
  AudioUnitParameterValue paramVal;
  for(hotpants::eParameter p = hotpants::kFirstParam;
                           p < hotpants::kNumOfParams;
                           p = static_cast<hotpants::eParameter>(p + 1)) {
    GetParameter(static_cast<AudioUnitParameterID>(p), kAudioUnitScope_Global, 0, paramVal);
    core.setParam(p, static_cast<hotpants::ParamValue>(paramVal));
  }
}
