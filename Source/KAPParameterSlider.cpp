/*
  ==============================================================================

    KAPParameterSlider.cpp
    Created: 10 Apr 2019 7:34:47pm
    Author:  samax

  ==============================================================================
*/

#include "KAPParameterSlider.h"

KAPParameterSlider::KAPParameterSlider(juce::AudioProcessorValueTreeState & stateToControl,
									   const juce::String& parameterID ,
									   const juce::String& parameterLabel)
	: juce::Slider (parameterLabel)
  {

	setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
	setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
	setRange(0.f, 1.f, 0.001f);

	mAttachment =
		new juce::AudioProcessorValueTreeState::
		SliderAttachment(stateToControl, parameterID, *this);

  };

  KAPParameterSlider::~KAPParameterSlider()
  {
  }

 
   