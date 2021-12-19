/*
  ==============================================================================

    KAPVuMeter.h
    Created: 29 Apr 2019 1:25:52pm
    Author:  j_samaca

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "pluginprocessor.h"


class KAPVuMeter
	:public juce::Component,
	public juce::Timer
{

public:

	KAPVuMeter(Samax_pluginAudioProcessor* inprocessor);
	~KAPVuMeter();

	void paint(juce::Graphics& g) override;
	
	void  timerCallback()override;

	void  setParameterID(int inParameterID);


private:

	int mParameterID;

	float mCh0Level;
	float mCh1Level;


	Samax_pluginAudioProcessor* mProcessor;



};