/*
  ==============================================================================

    KAPADelay.h
    Created: 2 Apr 2019 8:27:41pm
    Author:  samax

  ==============================================================================
*/

#pragma once
#include "KAPAaudioHelpers.h"
enum KAPDelayType
{
	kKAPDelayType_Delay = 0,
    kKAPDelayType_Chorus,

};



class KAPADelay
{
public:
	KAPADelay();
	~KAPADelay();

	void setSampleRate(double inSampleRate);

		
	void  reset();

	void process(float* inAudio,
				float inTime,
				float inFeedback,
				float inWetdry,
		        float inType, 
				float * inModulationBuffer,
				float* outAudio,
				int inNumsamplesToRender);

private:
	/** Internal */
	float  getInterpolatedSample(float inDelayTimeSamples);

	float mSampleRate;
	float mBuffer[maxBufferDelaySize];
	float mFeedbackSample;

	int mDelayIndex;
	float mTimeSmoothed;	

};
