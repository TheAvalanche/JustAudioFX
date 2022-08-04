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
class JustFlangerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JustFlangerAudioProcessorEditor (JustFlangerAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~JustFlangerAudioProcessorEditor() override;

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
    JustFlangerAudioProcessor& audioProcessor;

    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Label rateLabel;
    juce::Label depthLabel;
    juce::Label feedbackLabel;
    juce::Label mixLabel;
    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider feedbackSlider;
    juce::Slider mixSlider;
    std::unique_ptr<SliderAttachment> rateAttachment;
    std::unique_ptr<SliderAttachment> depthAttachment;
    std::unique_ptr<SliderAttachment> feedbackAttachment;
    std::unique_ptr<SliderAttachment> mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JustFlangerAudioProcessorEditor)
};
