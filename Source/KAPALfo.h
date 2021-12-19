/*
  ==============================================================================

    KAPALfo.h
    Created: 2 Apr 2019 8:35:17pm
    Author:  samax

  ==============================================================================
*/

#pragma once
#include "KAPAaudioHelpers.h"
class KAPALfo
{
public:
	KAPALfo();
	~KAPALfo();
	
	void reset();

	void setSampleRate(double inSampleRate);

	void process(float inRate, float inDepth, int inNumSamples);

	float * getBuffer();

private:

	double mSamplerate;

	float mPhase;

	float mBuffer[maxBufferDelaySize];


};