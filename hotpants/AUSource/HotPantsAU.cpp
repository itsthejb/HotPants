 /*
 *	File:		HotPants.cpp
 *	
 *	Version:	1.0
 * 
 *	Created:	9/6/2010
 *	
 *	Copyright:  Copyright � 2010 Jonathan Crooke (jc9873@bris.ac.uk), All Rights Reserved
 * 
 *	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc. ("Apple") in 
 *				consideration of your agreement to the following terms, and your use, installation, modification 
 *				or redistribution of this Apple software constitutes acceptance of these terms.  If you do 
 *				not agree with these terms, please do not use, install, modify or redistribute this Apple 
 *				software.
 *
 *				In consideration of your agreement to abide by the following terms, and subject to these terms, 
 *				Apple grants you a personal, non-exclusive license, under Apple's copyrights in this 
 *				original Apple software (the "Apple Software"), to use, reproduce, modify and redistribute the 
 *				Apple Software, with or without modifications, in source and/or binary forms; provided that if you 
 *				redistribute the Apple Software in its entirety and without modifications, you must retain this 
 *				notice and the following text and disclaimers in all such redistributions of the Apple Software. 
 *				Neither the name, trademarks, service marks or logos of Apple Computer, Inc. may be used to 
 *				endorse or promote products derived from the Apple Software without specific prior written 
 *				permission from Apple.  Except as expressly stated in this notice, no other rights or 
 *				licenses, express or implied, are granted by Apple herein, including but not limited to any 
 *				patent rights that may be infringed by your derivative works or by other works in which the 
 *				Apple Software may be incorporated.
 *
 *				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO WARRANTIES, EXPRESS OR 
 *				IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY 
 *				AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE 
 *				OR IN COMBINATION WITH YOUR PRODUCTS.
 *
 *				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL 
 *				DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 *				OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, 
 *				REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER 
 *				UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN 
 *				IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "HotPantsAU.h"
#include "CoreInclude.hpp"
#include "ComponentBase.h"

AUDIOCOMPONENT_ENTRY(AUBaseFactory, HotPants)
//COMPONENT_ENTRY(HotPants)

#pragma mark Counstructor & Initialiser

HotPants::HotPants(ComponentInstance inComponentInstance)
: AUMonotimbralInstrumentBase(inComponentInstance,
                              hotpants::kNumOfInputs,
                              hotpants::kNumOfOutputs)
{
  checkAUmapping();
  CreateElements();	
  Globals()->UseIndexedParameters(hotpants::kNumOfParams);
  setDefaultParameters();
}

OSStatus HotPants::Initialize()
{	
  AUMonotimbralInstrumentBase::Initialize();
  // initialise the instrument
  core.initialise(GetOutput(0)->GetStreamFormat().mSampleRate);
  return noErr;
}

#pragma mark -
#pragma mark MIDI input

OSStatus HotPants::RealTimeStartNote(SynthGroupElement            *inGroup,
                                     NoteInstanceID               inNoteInstanceID, 
                                     UInt32                       inOffsetSampleFrame, 
                                     const MusicDeviceNoteParams& inParams)
{
  // refresh parameters before note on
  refreshAllParameters();
  core.startNote(inNoteInstanceID, inParams.mPitch, inParams.mVelocity);
  return noErr;
}

OSStatus HotPants::RealTimeStopNote(MusicDeviceGroupID  inGroupID, 
                                    NoteInstanceID 		  inNoteInstanceID,
                                    UInt32 				      inOffsetSampleFrame)
{
  core.stopNote(inNoteInstanceID);
  return noErr;
}


OSStatus HotPants::HandleControlChange(UInt8    inChannel,  UInt8    inController,
                                       UInt8    inValue,    UInt32   inStartFrame)
{
  core.midiCC(inController, inValue);
  return noErr;
}

OSStatus HotPants::HandlePitchWheel(UInt8   inChannel,  UInt8   inPitch1,
                                    UInt8   inPitch2,   UInt32	inStartFrame)
{
  core.pitchBend(inPitch2);
  return noErr;
}

#pragma mark -
#pragma mark Render

OSStatus HotPants::Render(AudioUnitRenderActionFlags& ioActionFlags,
                          const AudioTimeStamp&       inTimeStamp,
                          UInt32                      inNumberFrames)
{
  PerformEvents(inTimeStamp);
  refreshAllParameters();
  
  // clear the buffer
  AudioBufferList& bufferList = GetOutput(0)->GetBufferList();
  for (UInt32 k = 0; k < bufferList.mNumberBuffers; ++k)
    memset(bufferList.mBuffers[k].mData, 0, bufferList.mBuffers[k].mDataByteSize);

  // write to the buffer
  core.render(reinterpret_cast<float*>(bufferList.mBuffers[0].mData), 
              reinterpret_cast<float*>(bufferList.mBuffers[1].mData),
              inNumberFrames);
  
  mAbsoluteSampleFrame += inNumberFrames;
  return noErr;
}

#pragma mark -
#pragma mark Parameters

void HotPants::setDefaultParameters()
{
  for(hotpants::eParameter  p = hotpants::kFirstParam;
      p < hotpants::kNumOfParams;
      p = static_cast<hotpants::eParameter>(p + 1)) 
  {
    Globals()->SetParameter(static_cast<AudioUnitParameterID>(p), 
                            static_cast<AudioUnitParameterValue>(core.getParamMap(p).defValue), 
                            false);
  }  
}

OSStatus HotPants::GetParameterInfo(AudioUnitScope          inScope, 
                                    AudioUnitParameterID    inParameterID, 
                                    AudioUnitParameterInfo  &outParameterInfo)
{
  // parameters are only defined for the global scope
  if (inScope != kAudioUnitScope_Global) return kAudioUnitErr_InvalidScope;
  
  OSStatus result = noErr;

  if(inParameterID <  static_cast<AudioUnitParameterID>(hotpants::kFirstParam) ||
     inParameterID >= static_cast<AudioUnitParameterID>(hotpants::kNumOfParams))
     return kAudioUnitErr_InvalidParameter;  
  
  // get parameters from global settings manager
  hotpants::eParameter p         = static_cast<hotpants::eParameter>(inParameterID);
  hotpants::_parameterMap map    = core.getParamMap(p);
  outParameterInfo.flags         = kAudioUnitParameterFlag_IsWritable 
                                  |kAudioUnitParameterFlag_IsReadable
                                  |AUflagMap[map.flag].AUvalue;
  outParameterInfo.unit          = AUunitMap[map.unit].AUvalue;
  outParameterInfo.defaultValue  = map.defValue;
  outParameterInfo.maxValue      = map.maxValue;
  outParameterInfo.minValue      = map.minValue;
  AUBase::FillInParameterName(outParameterInfo, AUstringMap[p].string, false);
  
  return result;
}

// report instrument strings to the audio framework
OSStatus HotPants::GetParameterValueStrings(AudioUnitScope        inScope,
                                            AudioUnitParameterID  inParameterID,
                                            CFArrayRef *          outStrings)
{
  if(inScope != kAudioUnitScope_Global) return kAudioUnitErr_InvalidProperty;
     
  int arraySize = (sizeof(AUmenuItemMap) / sizeof(AUmenuItemMap[0]));
  for(int i = 0; i < arraySize; ++i) {
    if (static_cast<UInt32>(AUmenuItemMap[i].enumVal) == inParameterID) {
      if (outStrings == NULL) return noErr;
      *outStrings = CFArrayCreate(NULL, (const void **) AUmenuItemMap[i].array, AUmenuItemMap[i].size, NULL);      
      return noErr; 
    }
  }
  return kAudioUnitErr_InvalidProperty;
}

// check parameter configuration
void HotPants::checkAUmapping()
{
  // is a string mapped for each menu item?
  assert(sizeof(AUmenu_OscWaveforms) / sizeof(AUmenu_OscWaveforms[0])  == hotpants::kNumOfOscWaves);
  assert(sizeof(AUmenu_OscMods)      / sizeof(AUmenu_OscMods[0])       == hotpants::kNumOfOscMods);
  assert(sizeof(AUmenu_LFOwaveforms) / sizeof(AUmenu_LFOwaveforms[0])  == hotpants::kNumOfLFOwaves);
  assert(sizeof(AUmenu_filterTypes)  / sizeof(AUmenu_filterTypes[0])   == hotpants::kNumOfFiltTypes);
  assert(sizeof(AUmenu_modTargets)   / sizeof(AUmenu_modTargets[0])    == hotpants::kNumOfModTargets);
  assert(sizeof(AUmenu_disortTypes)  / sizeof(AUmenu_disortTypes[0])   == hotpants::kNumOfDistorts);

  // do the parameter strings match up with all the parameters?
  for(hotpants::eParameter i = hotpants::kFirstParam;
                           i < hotpants::kNumOfParams;
                           i = static_cast<hotpants::eParameter>(i+1))
  {
    if(AUstringMap[i].enumVal != i) {
      fprintf(stderr, "AUstringmap correlation error: parameter %d\n", i);
      assert(false);
    }
  }
}

#pragma mark -
#pragma mark Factory Presets 

ComponentResult HotPants::GetPresets (CFArrayRef *outData ) const 
{
  if (outData == NULL) return noErr;

  CFMutableArrayRef presetsArray = CFArrayCreateMutable(NULL, hotpants::kNumOfPresets, NULL);
  for (unsigned int i = 0; i < hotpants::kNumOfPresets; ++i) {
    CFArrayAppendValue(presetsArray, &AUpresetMap[i]);
  }
  *outData = (CFArrayRef) presetsArray;
  return noErr;
}

OSStatus HotPants::NewFactoryPresetSet(const AUPreset &inNewFactoryPreset)
{
  // invalid preset?
  if(inNewFactoryPreset.presetNumber > hotpants::kNumOfPresets &&
     inNewFactoryPreset.presetNumber < 0)
    return kAudioUnitErr_InvalidProperty;

  // apply all settings for the preset
  for(hotpants::eParameter p =  hotpants::kFirstParam;
                           p != hotpants::kNumOfParams;
                           p =  static_cast<hotpants::eParameter>(p+1))
  {
    Globals()->
        SetParameter(
            static_cast<AudioUnitParameterID>(p),
            static_cast<AudioUnitParameterValue>(
                hotpants::kFactoryPresets[inNewFactoryPreset.presetNumber].parameter[p].value
                ),
            false);
  }
  return noErr;
}
 
