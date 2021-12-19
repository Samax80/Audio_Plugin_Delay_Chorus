/*
  ==============================================================================

    KAPALfo.cpp
    Created: 2 Apr 2019 8:35:17pm
    Author:  samax

  ==============================================================================
*/

#include "KAPALfo.h"
#include "JuceHeader.h"//Included to get access to the zeromem function!



KAPALfo::KAPALfo()
{
	reset();
}

KAPALfo::~KAPALfo()
{
	
}

void KAPALfo::reset()
{
	mPhase = 0.0f;
	juce::zeromem(mBuffer, sizeof(float)*maxBufferDelaySize);
}

void KAPALfo::setSampleRate(double inSampleRate)
{
	mSamplerate = inSampleRate;
}

void KAPALfo::process(float inRate, float inDepth, int inNumSamples)
{
	const float rate = juce::jmap(inRate,0.0f, 1.0f, 0.01f, 10.0f);

	for (int i = 0;i < inNumSamples;i++) {
		mPhase = mPhase + (rate / mSamplerate);
		
		if (mPhase > 1.0f) {
			mPhase = mPhase - 1.0f;
		}

		const float lfoPosition = sinf(mPhase*K2Pi)*inDepth;
		mBuffer[i] = lfoPosition;
	}
	
}

float * KAPALfo::getBuffer()
{
	return mBuffer;
}
