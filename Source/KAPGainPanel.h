/*
  ==============================================================================

    KAPGainPanel.h
    Created: 9 Apr 2019 1:34:58pm
    Author:  j_samaca

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterSlider.h"
#include "KAPVuMeter.h"


class   KAPGainPanel
	:public KAPAPanelBase

{


public:
	KAPGainPanel(Samax_pluginAudioProcessor* inProcessor);
	~KAPGainPanel();

	void paint(juce::Graphics& g) override;

	void setParameterID (int inparameterID);

private:
	
	juce::ScopedPointer<KAPVuMeter>mVuMeter;
	juce::ScopedPointer<KAPParameterSlider>mSlider;

};