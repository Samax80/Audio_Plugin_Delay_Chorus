/*
  ==============================================================================

    KAPPanelBase.h
    Created: 9 Apr 2019 1:31:23pm
    Author:  j_samaca

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "KAPInterfaceDefines.H"

class KAPAPanelBase
	:public juce::Component
{
public:

	KAPAPanelBase(Samax_pluginAudioProcessor* inProcessor);
	~KAPAPanelBase();

	
	//add this
	 void mouseEnter(const juce::MouseEvent& event) override;
	 //add this also
	 void mouseExit(const juce::MouseEvent& event) override;


	  void paint(juce::Graphics& g) override;

protected:

	Samax_pluginAudioProcessor *mProcessor;
};

	