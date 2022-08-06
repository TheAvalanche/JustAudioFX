/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CircularBufferOptimized.h"
#include "LFO.h"

// 1 for MONO, 2 for STEREO
const unsigned int DELAY_BUFFERS = 2;
// maximum number of seconds for delay
const unsigned int DELAY_BUFFER_SIZE_SEC = 1;
// minimum delay time for modulation
const double CHORUS_MIN_DELAY_TIME_MS = 10.0;
// maximum delay time for modulation
const double CHORUS_MAX_DELAY_TIME_MS = 30.0;

//==============================================================================
/**
*/
class JustChorusAudioProcessor  : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    JustChorusAudioProcessor();
    ~JustChorusAudioProcessor() override;

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

    void parameterChanged(const juce::String& parameterID, float newValue) override;


private:
    CircularBufferOptimized delayBuffer[DELAY_BUFFERS];
    std::unique_ptr<LFO> lfo;

    juce::AudioProcessorValueTreeState parameters;
    juce::UndoManager undoManager;

    std::atomic<float>* rateHzParam;
    std::atomic<float>* depthParam;
    std::atomic<float>* mixParam;

    double modulate(double modulationValue, double minValue, double maxValue);


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JustChorusAudioProcessor)
};
