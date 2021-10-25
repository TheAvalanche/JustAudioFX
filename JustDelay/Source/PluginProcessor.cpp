/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JustDelayAudioProcessor::JustDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
    parameters(*this, &undoManager, juce::Identifier("Delay"),
        {
            std::make_unique<juce::AudioParameterInt>("time", "Time", 30, DELAY_BUFFER_SIZE_SEC * 1000, 200),
            std::make_unique<juce::AudioParameterInt>("feedback", "Feedback", 0, 100, 50),
            std::make_unique<juce::AudioParameterInt>("mix", "Mix", 0, 100, 50),

        })
{
    delayTimeMsParam = parameters.getRawParameterValue("time");
    feedbackParam = parameters.getRawParameterValue("feedback");
    mixParam = parameters.getRawParameterValue("mix");
}

JustDelayAudioProcessor::~JustDelayAudioProcessor()
{
}

//==============================================================================
const juce::String JustDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JustDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JustDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JustDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JustDelayAudioProcessor::getTailLengthSeconds() const
{
    return 5.0;
}

int JustDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JustDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JustDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JustDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void JustDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JustDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    for (int i = 0; i < DELAY_BUFFERS; i++) {
        delayBuffer[i].init(sampleRate * DELAY_BUFFER_SIZE_SEC);
    }
}

void JustDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JustDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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

void JustDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    const int sampleRate = getSampleRate();
    const int numberOfSamples = buffer.getNumSamples();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        // ..do something to the data...

        for (int i = 0; i < numberOfSamples; ++i) {
            const float input = channelData[i];

            // read delay
            float yn = delayBuffer[channel].read(*delayTimeMsParam * sampleRate / 1000);

            // create input for delay line and write to buffer
            float dn = input + (*feedbackParam / 100) * yn;
            delayBuffer[channel].write(dn);

            // output
            float output = (1 - (*mixParam / 100)) * input + (*mixParam / 100) * yn;
            channelData[i] = output;

        }
    }
}

//==============================================================================
bool JustDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JustDelayAudioProcessor::createEditor()
{
    return new JustDelayAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void JustDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void JustDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JustDelayAudioProcessor();
}
