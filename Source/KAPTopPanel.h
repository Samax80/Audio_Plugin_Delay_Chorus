/*
  ==============================================================================

    KAPTopPanel.h
    Created: 9 Apr 2019 1:36:02pm
    Author:  j_samaca

  ==============================================================================
*/

#pragma once
#include "KAPPanelBase.h"


class   KAPTopPanel
	:public KAPAPanelBase,
	public juce::Button::Listener,
	public juce::ComboBox::Listener


{


public:


	KAPTopPanel(Samax_pluginAudioProcessor* inProcessor);
	~KAPTopPanel();

	void paint(juce::Graphics& g) override;

	void buttonClicked(juce::Button* b)  override;
		
	void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;


private:


	void displaySaveAsPopup();

	void updatePresetComboBox();


	juce::ScopedPointer<juce::ComboBox> mPresetDisplay;
	
	juce::ScopedPointer<juce::TextButton> mNewPreset,mSavePreset,mSaveAspreset;



};