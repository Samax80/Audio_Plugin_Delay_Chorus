/*
  ==============================================================================

    KAPParameterComboBox.h
    Created: 10 Apr 2019 7:35:37pm
    Author:  samax

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class  KAPParameterComboBox
	: public juce::ComboBox
{

public:

	KAPParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl,
			             const juce::String& parameterID);

	~KAPParameterComboBox();
private:


	juce::ScopedPointer<juce::AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;
	//juce::JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KAPParameterComboBox);
};