/*
 * AllWaveTables.hpp
 *
 * All the available wavetable types,
 * including "virtual" wavetables, which are real-
 * time oscillators, wrapped with the required
 * wavetable methods.
 *
 *  Created on: 21 Jun 2010
 *      Author: Jonathan Crooke (jc9873@bris.ac.uk)
 */

#ifndef ALLWAVETABLES_H_
#define ALLWAVETABLES_H_

/* signal generator */
#include "Direct/SineDirect.hpp"
#include "Fourier/SawPartial.hpp"
#include "Fourier/TriPartial.hpp"
#include "Fourier/SquarePartial.hpp"

/* LFO */
#include "Direct/PulseFixed.hpp"
#include "Direct/SawDirect.hpp"
#include "Direct/TriDirect.hpp"

/* virtual wavetable */
#include "Virtual/NoiseWrapper.hpp"
#include "Virtual/PulsePWM.hpp"

#endif /* ALLWAVETABLES_H_ */
