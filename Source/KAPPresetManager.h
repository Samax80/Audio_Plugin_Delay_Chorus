/*
  ==============================================================================

    KAPPresetManager.h
    Created: 20 Apr 2019 3:42:27pm
    Author:  samax

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#define PRESET_FILE_EXTENSION ".kpf"

class KAPPresetManager
{
public:
	KAPPresetManager(juce::AudioProcessor * inprocessor);
	~KAPPresetManager();

	void getXmlForPreset(juce::XmlElement * inElement);

	void LoadPresetForXml(juce::XmlElement * inElement);

	int getNumberOfPresets();

	juce::String getPresetName(int inPresetIndex);
	
	void createNewPreset();

	void SavePreset();

	void saveAsPreset(juce::String inPresetName);

	void loadPreset(int inPresetIndex);
	
	bool getisCurrentPresetSaved();

	juce::String getCurrentPresetName();


private: 

	void storeLocalPreset();

	bool mCurrentPresetIsSaved;

	juce::File mCurrentlyLoadedPreset;

	juce::Array <juce::File>mLocalPresets;

	juce::String mCurrentPresetName;
	
	juce::String mPresetDirectory;

	juce::XmlElement*  mCurrentPresetXml;

	juce::AudioProcessor * mProcessor;

	


};