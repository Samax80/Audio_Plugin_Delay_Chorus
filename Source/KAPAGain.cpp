/*
  ==============================================================================

    KAPAGain.cpp
    Created: 2 Apr 2019 8:34:15pm
    Author:  samax

  ==============================================================================
*/

#include "KAPAGain.h"
#include "KAPAaudioHelpers.h"


KAPAGain::KAPAGain()
	:mOutputSmoothed(0)
{

}
KAPAGain::~KAPAGain()
{

}

 void KAPAGain::process(float * inAudio,
						float inGain,
						float * outAudio,
						int inNumsamplesToRender)
{

	 for (int i = 0; i < inNumsamplesToRender; i++) {

		 float gainmapped = juce::jmap(inGain, 0.0f, 1.0f, -24.0f, 24.0f);

		 gainmapped = juce::Decibels::decibelsToGain(gainmapped, -24.0f);
		 outAudio[i] = inAudio[i] * gainmapped;

		
	 };

	 float absValue = fabs(outAudio[0]);
	 mOutputSmoothed = kMeterSmoothCoeff * (mOutputSmoothed - absValue) + absValue;

}

 float KAPAGain::getMeterLevel()
 {
	 return mOutputSmoothed;
 }

