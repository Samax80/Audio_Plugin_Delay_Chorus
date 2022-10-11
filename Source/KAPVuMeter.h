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
	
	KAPVuMeter(std::function<float()>&& valueFunction);	

	void paint(juce::Graphics& g) override;
	
	void  timerCallback()override;

	void resized() override;

	void  setParameterID(int inParameterID);


private:

	int mParameterID{ -1 };

	float mCh0Level{ 0 };
	float mCh1Level{ 0 };

	
	std::function<float()> valueSupplier;
	juce::ColourGradient gradient{};



};