/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
/**
*/
class JustDelayAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JustDelayAudioProcessorEditor (JustDelayAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~JustDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    enum
    {
        paramControlHeight = 40,
        paramLabelWidth = 80,
        paramSliderWidth = 300
    };

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JustDelayAudioProcessor& audioProcessor;

    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Label timeLabel;
    juce::Label feedbackLabel;
    juce::Label mixLabel;
    juce::Slider timeSlider;
    juce::Slider feedbackSlider;
    juce::Slider mixSlider;
    std::unique_ptr<SliderAttachment> timeAttachment;
    std::unique_ptr<SliderAttachment> feedbackAttachment;
    std::unique_ptr<SliderAttachment> mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JustDelayAudioProcessorEditor)
};
