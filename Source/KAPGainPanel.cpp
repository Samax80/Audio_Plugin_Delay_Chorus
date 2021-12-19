/*
  ==============================================================================

    KAPGainPanel.cpp
    Created: 9 Apr 2019 1:34:59pm
    Author:  j_samaca

  ==============================================================================
*/

#include "KAPGainPanel.h"
#include "KAPParameters.h"
#include "KAPHelperFunctions.h"


KAPGainPanel::KAPGainPanel(Samax_pluginAudioProcessor* inProcessor)
	:KAPAPanelBase(inProcessor)
{

	setSize(GAIN_PANEL_WIDTH,
			GAIN_PANEL_HEIGHT);
	
	const int meter_width = 64;
	mVuMeter = new KAPVuMeter(mProcessor);
	
	
	
	mVuMeter->setBounds((getWidth()*0.5) - (meter_width*0.5),
					   (getHeight()*0.66) - (meter_width*0.5)-10, 
						meter_width,
						getHeight() * 0.45);
						
	addAndMakeVisible(mVuMeter);

						
}

KAPGainPanel::~KAPGainPanel()
{

}

void KAPGainPanel::paint(juce::Graphics & g)
{
	KAPAPanelBase::paint(g);
	
	if (mSlider) {
		paintComponentLabel(g, mSlider);
	}

	
}

void KAPGainPanel::setParameterID(int inparameterID)
{
	mSlider = new KAPParameterSlider(mProcessor->parameters,
									 KAPParameterID[inparameterID], KAPParameterLabel[inparameterID]);
	const int slider_size = 54;

	mSlider->setBounds(
						(getWidth()*0.5)-(slider_size*0.5),
						(getHeight()*0.25)-(slider_size*0.5),
						slider_size,
		                slider_size);

	addAndMakeVisible(mSlider);
	mVuMeter->setParameterID(inparameterID);

}
