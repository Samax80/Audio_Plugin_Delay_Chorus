/*
  ==============================================================================

    KAPParameterComboBox.cpp
    Created: 10 Apr 2019 7:35:37pm
    Author:  samax

  ==============================================================================
*/

#include "KAPParameterComboBox.h"

KAPParameterComboBox::KAPParameterComboBox(juce::AudioProcessorValueTreeState& stateToControl, const juce::String& parameterID)
	: juce::ComboBox(parameterID)

{
	mAttachment=
		new juce::AudioProcessorValueTreeState::ComboBoxAttachment(stateToControl, parameterID, *this);
		
};

  KAPParameterComboBox::~KAPParameterComboBox()
  {
  }
