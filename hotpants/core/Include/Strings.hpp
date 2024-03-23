/*
 * ParamStrings.hpp
 *
 * Parameter preprocessor name strings and menu items
 *
 *  Created on: 30 Jul 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef PARAMSTRINGS_HPP_
#define PARAMSTRINGS_HPP_

// a little macro trickey
// to allow defined parameter names
// to be duplicated/reused
#define _DUPE_(x) x
#define DUPE(x) _DUPE_(x)

// amp envelope
#define kParamName_AmpAttack            "AMP attack"
#define kParamName_AmpDecay             "decay"
#define kParamName_AmpSustain           "sustain"
#define kParamName_AmpRelease           "release"
#define kParamName_AmpScaling           "depth"
#define kParamName_Velocity             "velocity"
  // oscillators
#define kParamName_Osc1Wave             "OSC1 wave"
#define kParamName_Osc1Tuning           "tuning"
#define kParamName_Osc1Amp              "amp"
#define kParamName_Osc2Wave             "OSC2 wave"
#define kParamName_Osc2Tuning           "tuning"
#define kParamName_Osc2Fine             "fine"
#define kParamName_Osc2Amp              "amp"
#define kParamName_Osc3Wave             "OSC3 wave"
#define kParamName_Osc3Tuning           "tuning"
#define kParamName_Osc3Amp              "amp"
#define kParamName_OscMod               "o2->o1 mod"
#define kParamName_OscAnalogue          "analogue"
#define kParamName_PulseWidth           "pulse width"
  // filters
#define kParamName_Filt1Type            "FILT1 type"
#define kParamName_Filt1Cutoff          "cutoff"
#define kParamName_Filt1Q               "bandwidth"
#define kParamName_Filt1EQGain          "eq gain"
#define kParamName_Filt2Type            "FILT2 type"
#define kParamName_Filt2Cutoff          "cutoff"
#define kParamName_Filt2Q               "bandwidth"
#define kParamName_Filt2EQGain          "eq gain"
#define kParamName_FiltConnect          "connection"
#define kParamName_FiltMix              "mix"
#define kParamName_FiltKeyTrack         "key track"
  // LFOS
#define kParamName_LFO1Target           "LFO1 target"
#define kParamName_LFO1Wave             "wave"
#define kParamName_LFO1Rate             "rate"
#define kParamName_LFO1Amount           "amount"
#define kParamName_LFO2Target           "LFO2 target"
#define kParamName_LFO2Wave             "wave"
#define kParamName_LFO2Rate             "rate"
#define kParamName_LFO2Amount           "amount"
  // Envelopes
#define kParamName_Env1Target           "ENV1 target"
#define kParamName_Env1Amount           "amount"
#define kParamName_Env1Attack           "attack"
#define kParamName_Env1Decay            "decay"
#define kParamName_Env1Sustain          "sustain"
#define kParamName_Env1Release          "release"
#define kParamName_Env2Target           "ENV2 target"
#define kParamName_Env2Amount           "amount"
#define kParamName_Env2Attack           "attack"
#define kParamName_Env2Decay            "decay"
  // effects
#define kParamName_DistortType          "DISTORTION"
#define kParamName_DistortGain          "gain"
  // delay
#define kParamName_DelayL_Mix           "DELAY L mix"
#define kParamName_DelayL_Time          "L time"
#define kParamName_DelayL_FB            "L feedback"
#define kParamName_DelayR_Mix           "DELAY R mix"
#define kParamName_DelayR_Time          "R time"
#define kParamName_DelayR_FB            "R feedback"
  // delay filter
#define kParamName_DelayHP              "high-pass"
#define kParamName_DelayLP              "low-pass"
  // mod wheel
#define kParamName_WheelTarget          "MOD WHEEL"
#define kParamName_WheelAmount          "amount"
  // velocity modulation
#define kParamName_VeloTarget           "VELOCITY"
#define kParamName_VeloAmount           "amount"
  // globals
#define kParamName_PitchBend            "bend depth"
#define kParamName_Portamento           "portamento"
#define kParamName_Polyphony            "polyphony"
#define kParamName_GlobalTuning         "global tuning"
#define kParamName_GlobalVolume         "gain"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Factory presets
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define kPresetName_Factory1            "factory preset1"
#define kPresetName_Factory2            "factory preset2"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Menu Items
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define kMenuItem_Off                   "- off -"
  // oscs
#define kMenuItem_Osc_Sine              "sine"
#define kMenuItem_Osc_Tri               "triangle"
#define kMenuItem_Osc_Saw               "sawtooth"
#define kMenuItem_Osc_Square            "pulse"
#define kMenuItem_Osc_PulsePWM          "pulse pwm"
#define kMenuItem_Osc_Noise             "noise"
  // osc mod types
#define kMenuItem_OscMod_None           DUPE(kMenuItem_Off)
#define kMenuItem_OscMod_FM             "FM"
#define kMenuItem_OscMod_AM             "AM"
#define kMenuItem_OscMod_RM             "ring mod"
  // filters
#define kMenuItem_Filt_Off              DUPE(kMenuItem_Off)
#define kMenuItem_Filt_LP               "low-pass"
#define kMenuItem_Filt_HP               "high-pass"
#define kMenuItem_Filt_BP_CSG           "band-pass csg"
#define kMenuItem_Filt_BP_CZPG          "band-pass czpg"
#define kMenuItem_Filt_Notch            "notch"
#define kMenuItem_Filt_AllPass          "all-pass"
#define kMenuItem_Filt_Peaking          "peaking"
#define kMenuItem_Filt_LowShelf         "low-shelf"
#define kMenuItem_Filt_HiShelf          "high-shelf"
  // LFOs
#define kMenuItem_LFO_Sine              DUPE(kMenuItem_Osc_Sine)
#define kMenuItem_LFO_Tri               DUPE(kMenuItem_Osc_Tri)
#define kMenuItem_LFO_Saw               DUPE(kMenuItem_Osc_Saw)
#define kMenuItem_LFO_Square            DUPE(kMenuItem_Osc_Square)
#define kMenuItem_LFO_SandH             "sample & hold"
  // LFO connection
#define kMenuItem_ConnectSerial         "serial"
#define kMenuItem_ConnectParallel       "parallel"
  // distortion
#define kMenuItem_Distort_Off           DUPE(kMenuItem_Off)
#define kMenuItem_Distort_HardC         "hard clip"
#define kMenuItem_Distort_Fold          "fold-back"
  // Mod Ts
#define kMenuItem_Mod_None              DUPE(kMenuItem_Off)
#define kMenuItem_Mod_GlobalVol         "global volume"
#define kMenuItem_Mod_GlobalTune        DUPE(kParamName_GlobalTuning)
#define kMenuItem_Mod_Osc1Tuning        "osc1 tuning"
#define kMenuItem_Mod_Osc1Amp           "osc1 amp"
#define kMenuItem_Mod_Osc2Tuning        "osc2 tuning"
#define kMenuItem_Mod_Osc2Fine          "osc2 fine"
#define kMenuItem_Mod_Osc2Amp           "osc2 amp"
#define kMenuItem_Mod_Osc3Tuning        "osc3 tuning"
#define kMenuItem_Mod_Osc3Amp           "osc3 amp"
#define kMenuItem_Mod_PulseWidth        "pulse width"
#define kMenuItem_Mod_Filt1Cutoff       "filt1 cutoff"
#define kMenuItem_Mod_Filt1Q            "filt1 bandwidth"
#define kMenuItem_Mod_Filt1Reso         "filt1 resonance"
#define kMenuItem_Mod_Filt2Cutoff       "filt2 cutoff"
#define kMenuItem_Mod_Filt2Q            "filt2 bandwidth"
#define kMenuItem_Mod_Filt2Reso         "filt2 resonance"
#define kMenuItem_Mod_FiltMix           "filter mix"
#define kMenuItem_Mod_LFO1Amount        "lfo1 amount"
#define kMenuItem_Mod_LFO1Rate          "lfo1 rate"
#define kMenuItem_Mod_LFO2Amount        "lfo2 amount"
#define kMenuItem_Mod_LFO2Rate          "lfo2 rate"
#define kMenuItem_Mod_Env1Amount        "env1 amount"
#define kMenuItem_Mod_Env2Amount        "env2 amount"

#endif /* PARAMSTRINGS_HPP_ */
