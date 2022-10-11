/*
  ==============================================================================

    KAPAaudioHelpers.h
    Created: 2 Apr 2019 8:26:19pm
    Author:  samax

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define  kParameterSmoothingcoeff_Generic 1

#define  kParameterSmoothingcoeff_fine  0.002

#define  kMeterSmoothCoeff  0.2f

const static int maxBufferDelaySize = 192000;
const static double KPi = 3.14159265359;
const static double K2Pi = 6.28318530718;

static inline float dBToNormalizedGain(float inValue)
{

	float inValuedB = juce::Decibels::gainToDecibels(inValue+0.00001f);
	inValuedB = (inValuedB + 96.0f )/ 96.0f;

	return inValuedB;

}



inline float kap_linear_interp(float v0, float v1, float t)
{
	return (1 - t) * v0 + t * v1;
}
/// <summary>
/// https://www.musicdsp.org/ Rational tanh approximation
/// To allow feedback beyond 100%
/// </summary>
/// <param name="double x"></param>
/// <returns></returns>
inline double tanh_clip (double x)
{
	return x * (27 + x * x) / (27 + 9 * x*x);
}

inline float  tanh_clip(float x)
{
	return x * (27 + x * x) / (27 + 9 * x * x);
}

inline float kap_denormalize(float inValue)
{

	float absValue = fabs(inValue);


	//0.000000000000001
	if (absValue < 1e-15) {

		return 0.0f;
	}
	else {
		return inValue;
	}

}

