/*
  ==============================================================================

    KAPParameterSlider.h
    Created: 10 Apr 2019 7:34:47pm
    Author:  samax

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class  KAPParameterSlider
	: public juce::Slider
{

public:

	KAPParameterSlider(juce::AudioProcessorValueTreeState& stateToControl,
					   const juce::String& parameterID,
		               const juce::String& parameterLabel);

	~KAPParameterSlider();
private:


	juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment> mAttachment;
	//juce::JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPParameterSlider);
};