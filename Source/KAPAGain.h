/*
  ==============================================================================

    KAPAGain.h
    Created: 2 Apr 2019 8:34:15pm
    Author:  samax

  ==============================================================================
*/

#pragma once


class KAPAGain
{
public:
	KAPAGain();
	~KAPAGain();

	void process(float *inAudio,
				  float inGain,
				float *outGain,
				int inNumsamplesToRender);

	float getMeterLevel();

private:


	float mOutputSmoothed;


};