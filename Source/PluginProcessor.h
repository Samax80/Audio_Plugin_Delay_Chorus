/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "KAPAGain.h"
#include "KAPADelay.h"
#include "KAPALfo.h"
#include "KAPPresetManager.h"

//==============================================================================
/**
*/
class Samax_pluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Samax_pluginAudioProcessor();
    ~Samax_pluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //new
    float getOutputGainMeterLevel(int inChannel);

    float getInputGainMeterLevel(int inChannel);

    juce::AudioProcessorValueTreeState parameters;

    KAPPresetManager* getPresetManager()
    {

        return mPresetManager.get();
    }

  

  
private:
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void initializeDSP();

    std::unique_ptr<KAPAGain>mInputGain[2];
    std::unique_ptr<KAPAGain>mOutputGain[2];
    std::unique_ptr<KAPADelay>mDelay[2];
    std::unique_ptr<KAPALfo>mLfo[2];

    std::unique_ptr<KAPPresetManager>mPresetManager;
  

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Samax_pluginAudioProcessor)
};
