/*
  ==============================================================================

    KAPVuMeter.cpp
    Created: 29 Apr 2019 1:25:52pm
    Author:  j_samaca

  ==============================================================================
*/
#include "KAPVuMeter.h"
#include "KAPInterfaceDefines.h"
#include "KAPParameters.h"
#include "KAPAaudioHelpers.h"




KAPVuMeter::KAPVuMeter(std::function<float()>&& valueFunction)
	:valueSupplier(std::move(valueFunction))
{
	startTimerHz(24);
}



void KAPVuMeter::paint(juce::Graphics& g)
{


		//New VU implementation
		const auto level = valueSupplier();
		auto bounds = getLocalBounds().toFloat();
		
		g.setColour(juce::Colours::black);
		g.fillRect(bounds);
		g.setGradientFill(gradient);
		const auto scaledY=juce::jmap(level, -60.f, 6.f, 0.f, static_cast<float>(getHeight()));

		g.fillRect(bounds.removeFromBottom(scaledY));
		

}


void KAPVuMeter::resized()
{
	auto bounds = getLocalBounds().toFloat();

	 gradient= juce::ColourGradient
	{
		juce::Colours::green,
		bounds.getBottomLeft(),
		juce::Colours::red,
		bounds.getTopLeft(),
		false
	};

}


void KAPVuMeter::timerCallback()
{
	
	repaint();
}


void KAPVuMeter::setParameterID(int inParameterID)
{
	mParameterID = inParameterID;
}
