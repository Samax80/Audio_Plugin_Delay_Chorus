/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "KAPMainPanel.h"
#include "KAPLookAndFeel.h"

//==============================================================================
/**
*/
class Samax_pluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Samax_pluginAudioProcessorEditor (Samax_pluginAudioProcessor&);
    ~Samax_pluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Samax_pluginAudioProcessor& audioProcessor;   

    std::unique_ptr<KAPMainPanel> mMainPanel;
    std::unique_ptr <KAPLookAndFeel> mLookAndFeel;

    juce::Image mBackgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Samax_pluginAudioProcessorEditor)
};
