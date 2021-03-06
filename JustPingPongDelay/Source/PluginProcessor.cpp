/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JustPingPongDelayAudioProcessor::JustPingPongDelayAudioProcessor()
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
            std::make_unique<juce::AudioParameterInt>("spatial", "Spatial", 0, 100, 50),
            std::make_unique<juce::AudioParameterInt>("mix", "Mix", 0, 100, 50),
            std::make_unique<juce::AudioParameterBool>("invertSide", "Invert Side", false),

        })
{
    delayTimeMsParam = parameters.getRawParameterValue("time");
    feedbackParam = parameters.getRawParameterValue("feedback");
    spatialParam = parameters.getRawParameterValue("spatial");
    invertSideParam = parameters.getRawParameterValue("invertSide");
    mixParam = parameters.getRawParameterValue("mix");
}

JustPingPongDelayAudioProcessor::~JustPingPongDelayAudioProcessor()
{
}

//==============================================================================
const juce::String JustPingPongDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JustPingPongDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JustPingPongDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JustPingPongDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JustPingPongDelayAudioProcessor::getTailLengthSeconds() const
{
    return 5.0;
}

int JustPingPongDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JustPingPongDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JustPingPongDelayAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JustPingPongDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void JustPingPongDelayAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JustPingPongDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    // init circular buffers for delay
    for (int i = 0; i < DELAY_BUFFERS; i++) {
        delayBuffer[i].init(sampleRate * DELAY_BUFFER_SIZE_SEC);
    }
}

void JustPingPongDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JustPingPongDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void JustPingPongDelayAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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


    auto* leftChannelData = buffer.getWritePointer(LEFT_CHANNEL_IDX);
    auto* rightChannelData = buffer.getWritePointer(RIGHT_CHANNEL_IDX);

    // spatial will make ping-pong effect more distinguishable by attenuating one channel input to delay buffer
    // with spatial == 100 only one channel will ping pong. Left by default, or right if invertSide == true.
    auto invertSide = *invertSideParam > 0.5f;
    auto spatialLeft = invertSide ? (1 - (*spatialParam / 100)) : 1;
    auto spatialRight = invertSide ? 1 : (1 - (*spatialParam / 100));

    for (int i = 0; i < numberOfSamples; ++i) {
        // read input signal
        const float inputL = leftChannelData[i];
        const float inputR = rightChannelData[i];

        // read delayed signal
        float delayL = delayBuffer[LEFT_CHANNEL_IDX].read(*delayTimeMsParam * sampleRate / 1000);
        float delayR = delayBuffer[RIGHT_CHANNEL_IDX].read(*delayTimeMsParam * sampleRate / 1000);

        // create input for delay line and write feedback to opposite channel buffer
        delayBuffer[LEFT_CHANNEL_IDX].write(inputL * spatialLeft + (*feedbackParam / 100) * delayR);
        delayBuffer[RIGHT_CHANNEL_IDX].write(inputR * spatialRight + (*feedbackParam / 100) * delayL);

        // write output mix
        leftChannelData[i] = (1 - (*mixParam / 100)) * inputL + (*mixParam / 100) * delayL;
        rightChannelData[i] = (1 - (*mixParam / 100)) * inputR + (*mixParam / 100) * delayR;

    }
}

//==============================================================================
bool JustPingPongDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JustPingPongDelayAudioProcessor::createEditor()
{
    return new JustPingPongDelayAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void JustPingPongDelayAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void JustPingPongDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new JustPingPongDelayAudioProcessor();
}
