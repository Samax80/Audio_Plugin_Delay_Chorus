/*
  ==============================================================================

    KAPCenterPanelMenuBar.h
    Created: 9 Apr 2019 1:32:55pm
    Author:  j_samaca

  ==============================================================================
*/

#pragma once
#include "KAPPanelBase.h"
#include"KAPParameterComboBox.h"


class   KAPCenterPanelMenuBar
	:public KAPAPanelBase

{
public:
	KAPCenterPanelMenuBar(Samax_pluginAudioProcessor* inProcessor);
	~KAPCenterPanelMenuBar();


	void addFxTypeComboBoxListener(juce::ComboBox::Listener *inListener);
	void RemoveFxTypeComboBoxListener(juce::ComboBox::Listener* inListener);


	
private:

	juce::ScopedPointer<KAPParameterComboBox> mFxTypeComboBox;


};