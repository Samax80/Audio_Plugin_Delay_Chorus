/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "KAPParameters.h"

//==============================================================================
Samax_pluginAudioProcessor::Samax_pluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    parameters(*this,
        nullptr,
        juce::Identifier("KAP"),
        createParameterLayout())
#endif
{

    initializeDSP();




    mPresetManager = std::make_unique<KAPPresetManager>(this);

}

Samax_pluginAudioProcessor::~Samax_pluginAudioProcessor()
{
}

//==============================================================================
const juce::String Samax_pluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Samax_pluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Samax_pluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Samax_pluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Samax_pluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Samax_pluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Samax_pluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Samax_pluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Samax_pluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void Samax_pluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Samax_pluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    for (int i = 0; i < 2; i++) {
        mDelay[i]->setSampleRate(sampleRate);
        mLfo[i]->setSampleRate(sampleRate);
    }
}

void Samax_pluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    for (int i = 0; i < 2; i++) {
        mDelay[i]->reset();
        mLfo[i]->reset();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Samax_pluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Samax_pluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        float inputGain =
            *parameters.getRawParameterValue(KAPParameterID[kParameter_InputGain]);

        mInputGain[channel]->process(channelData,
            inputGain,
            channelData,
            buffer.getNumSamples());

        float rate = (channel == 0) ? 0 : getParameter(kParameter_ModulationRate); // if cahnnel=0 rate=0

        float ModulationDepth =
            *parameters.getRawParameterValue(KAPParameterID[kParameter_ModulationDepth]);

        mLfo[channel]->process(rate,
            ModulationDepth,
            buffer.getNumSamples());
                 



        float type_value = *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayType]);

        if (type_value == 0.5)
        {
            type_value = 0;
        }


        mDelay[channel]->process(channelData,
            *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayTime]),
            *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayFeedback]),
            *parameters.getRawParameterValue(KAPParameterID[kParameter_DelayWetDry]),
            type_value,
            mLfo[channel]->getBuffer(),
            channelData,
            buffer.getNumSamples());       


        mOutputGain[channel]->process(channelData,
            *parameters.getRawParameterValue(KAPParameterID[kParameter_OutputGain]),
            channelData,
            buffer.getNumSamples());

        // ..do something to the data...
    }
}

//==============================================================================
bool Samax_pluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Samax_pluginAudioProcessor::createEditor()
{
    return new Samax_pluginAudioProcessorEditor (*this);
}

//==============================================================================
void Samax_pluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    using  XmlElement = juce::XmlElement;
    XmlElement preset("KAP_StateInfo");

    XmlElement* presetBody = new  XmlElement("KAP_Preset");

    mPresetManager->getXmlForPreset(presetBody);

    preset.addChildElement(presetBody);
    copyXmlToBinary(preset, destData);
}

void Samax_pluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
        // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    //std::unique_ptr<juce::XmlElement> xmlState;
    //xmlState.reset(getXmlFromBinary(data, sizeInBytes));//NOT WORKING
	//if (xmlState != nullptr)
	//{
		//forEachXmlChildElement(*xmlState, subchild)
		//{
		//	mPresetManager->LoadPresetForXml(subchild);
		//}

	//}


    ///
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        forEachXmlChildElement(*xmlState, subchild)
        {
            mPresetManager->LoadPresetForXml(subchild);
        }
    }
}

float Samax_pluginAudioProcessor::getOutputGainMeterLevel(int inChannel)
{
    const float  normalizeddB = dBToNormalizedGain(mOutputGain[inChannel]->getMeterLevel());

    return normalizeddB;
}

float Samax_pluginAudioProcessor::getInputGainMeterLevel(int inChannel)
{
    const float  normalizeddB = dBToNormalizedGain(mInputGain[inChannel]->getMeterLevel());

    return normalizeddB;
}



juce::AudioProcessorValueTreeState::ParameterLayout Samax_pluginAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::AudioParameterFloat>> params;

    for (int i = 0; i < kParameter_TotalNumParameters; i++) {
               
        params.push_back(std::make_unique<juce::AudioParameterFloat>(KAPParameterID[i],
            KAPParameterLabel[i],
            juce::NormalisableRange<float>(0.0f, 1.0f),
            KAPParameterDefaultValue[i]));

        if ( i==4)
        {
            auto lbl = KAPParameterLabel[i];
            auto val = KAPParameterDefaultValue[i];
        }
    }
    

    return { params.begin(),params.end() };
}

void Samax_pluginAudioProcessor::initializeDSP()
{
    for (int i = 0; i < 2; i++)
    {
        mInputGain[i] = std::make_unique<KAPAGain>();
        mOutputGain[i] = std::make_unique<KAPAGain>();

        mDelay[i] = std::make_unique <KAPADelay>();
        mLfo[i] = std::make_unique <KAPALfo>();
    }

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Samax_pluginAudioProcessor();
}
