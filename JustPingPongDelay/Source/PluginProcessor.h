/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CircularBufferOptimized.h"

// 1 for MONO, 2 for STEREO
const unsigned int DELAY_BUFFERS = 2;
// maximum number of seconds for delay
const unsigned int DELAY_BUFFER_SIZE_SEC = 2;

// index of delay buffer left channel
const unsigned int LEFT_CHANNEL_IDX = 0;
// index of delay buffer right channel
const unsigned int RIGHT_CHANNEL_IDX = 1;

//==============================================================================
/**
*/
class JustPingPongDelayAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    JustPingPongDelayAudioProcessor();
    ~JustPingPongDelayAudioProcessor() override;

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

private:

    CircularBufferOptimized delayBuffer[DELAY_BUFFERS];

    juce::AudioProcessorValueTreeState parameters;
    juce::UndoManager undoManager;

    std::atomic<float>* delayTimeMsParam;
    std::atomic<float>* feedbackParam;
    std::atomic<float>* mixParam;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JustPingPongDelayAudioProcessor)
};
