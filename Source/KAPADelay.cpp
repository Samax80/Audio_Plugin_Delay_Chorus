/*
  ==============================================================================

    KAPADelay.cpp
    Created: 2 Apr 2019 8:27:41pm
    Author:  samax

  ==============================================================================
*/

#include "KAPADelay.h"

#include "JuceHeader.h"

#include "KAPAaudioHelpers.h"




KAPADelay::KAPADelay()
	: mSampleRate(-1),//initiliaze just for check if crash
	mFeedbackSample(0.0),
	mTimeSmoothed(0),
	mDelayIndex(0)
{
	
	
}
KAPADelay::~KAPADelay()
{

}

void KAPADelay::setSampleRate(double inSampleRate) 
{

	
	mSampleRate = inSampleRate;

	//Added by me!!
	juce::zeromem(mBuffer, (sizeof(float) * maxBufferDelaySize));
	

}


void KAPADelay::reset()
{
	mTimeSmoothed = 0.0f;
	juce::zeromem(mBuffer,( sizeof(float) * maxBufferDelaySize));
}

void KAPADelay::process(float* inAudio,
						float inTime,
						float inFeedback,
						float inWetdry,
						float inType,
						float * inModulationBuffer,
						float* outAudio,
						int inNumsamplesToRender)
{
	const float wet = inWetdry;
	const float dry = 1.0f - wet;
	
	
	
	float feedbackMapped = 0;
	//DBG(inType);
	if(inType ==kKAPDelayType_Delay){
		feedbackMapped= juce::jmap (inFeedback, 0.0f, 1.0f, 0.0f, 1.2f);
		//DBG(feedbackMapped);
	}
	
	for (int i = 0; i < inNumsamplesToRender; i++) {
	
		if ((int)inType == kKAPDelayType_Delay) {
			mTimeSmoothed = mTimeSmoothed - kParameterSmoothingcoeff_Generic * (mTimeSmoothed - inTime);
			//DBG(mTimeSmoothed);
		}
		else {
			const float delayTimemodulation = (0.003 + (0.002*inModulationBuffer[i]));
			mTimeSmoothed = mTimeSmoothed - kParameterSmoothingcoeff_Generic * (mTimeSmoothed - delayTimemodulation);
		}

				
		const float delayTimeInSamples = (mTimeSmoothed * mSampleRate);

	  	const float sample=getInterpolatedSample(delayTimeInSamples);
						                                        
		mBuffer[mDelayIndex] = 
			tanh_clip (inAudio[i] + (mFeedbackSample *feedbackMapped));
				
 		mFeedbackSample = sample;
	
		outAudio[i] = (inAudio[i] * dry + sample * wet);

		mDelayIndex = mDelayIndex + 1;

		if (mDelayIndex >= maxBufferDelaySize) {
			mDelayIndex = mDelayIndex - maxBufferDelaySize;
		}

	}

}

float KAPADelay::getInterpolatedSample(float inDelayTimeSamples)
{

	float readPosition = (float)mDelayIndex - inDelayTimeSamples;

	if (readPosition < 0.0f) {
		readPosition = readPosition + maxBufferDelaySize;
	}

	int index_y0 = (int)readPosition - 1;

	if (index_y0 <= 0) {
		index_y0 = index_y0 + maxBufferDelaySize;
	}

	int index_Y1 = readPosition;

	if (index_Y1 > maxBufferDelaySize) {
		index_Y1 = index_Y1 - maxBufferDelaySize;
	}
	
	const float sample_y0 = mBuffer[index_y0];
	const float sample_Y1 = mBuffer[index_Y1];

	const float t = readPosition -(int)readPosition ;

	float outSAmple = kap_linear_interp(sample_y0,
		sample_Y1,t);

	return  outSAmple;

}


