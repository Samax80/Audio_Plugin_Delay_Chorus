/*
  ==============================================================================

    KAPFxPanel.h
    Created: 9 Apr 2019 1:34:43pm
    Author:  j_samaca

  ==============================================================================
*/

#pragma once

#include "KAPPanelBase.h"
#include "KAPParameterSlider.h"



enum  KAPFxPanelStyle
{
	kKAPFxPAnelStyle_Delay,
	kKAPFxPAnelStyle_Chorus,
	kKAPFxPAnelStyle_TotalNumStyles

};


class kKAPFxPAnel
	:public KAPAPanelBase,
	public juce::ComboBox::Listener

{
public:

	kKAPFxPAnel(Samax_pluginAudioProcessor* inProcessor);
	~kKAPFxPAnel();

	void paint(juce::Graphics& g) override;

	void setFxPanelStyle(KAPFxPanelStyle inStyle);

	void comboBoxChanged(juce::ComboBox* comboBOxThatHasChanged)override;

	

private:
	
	KAPFxPanelStyle mStyle;
	juce::OwnedArray<KAPParameterSlider>mSliders;
	

};
