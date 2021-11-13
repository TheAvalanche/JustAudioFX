/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JustPingPongDelayAudioProcessorEditor::JustPingPongDelayAudioProcessorEditor (JustPingPongDelayAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), audioProcessor(p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    timeLabel.setText("Time, ms", juce::dontSendNotification);
    addAndMakeVisible(timeLabel);
    addAndMakeVisible(timeSlider);
    timeAttachment.reset(new SliderAttachment(valueTreeState, "time", timeSlider));

    feedbackLabel.setText("Feedback, %", juce::dontSendNotification);
    addAndMakeVisible(feedbackLabel);
    addAndMakeVisible(feedbackSlider);
    feedbackAttachment.reset(new SliderAttachment(valueTreeState, "feedback", feedbackSlider));

    mixLabel.setText("Mix, %", juce::dontSendNotification);
    addAndMakeVisible(mixLabel);
    addAndMakeVisible(mixSlider);
    mixAttachment.reset(new SliderAttachment(valueTreeState, "mix", mixSlider));

    setSize(paramSliderWidth + paramLabelWidth, juce::jmax(100, paramControlHeight * 3));
}

JustPingPongDelayAudioProcessorEditor::~JustPingPongDelayAudioProcessorEditor()
{
}

//==============================================================================
void JustPingPongDelayAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void JustPingPongDelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto r = getLocalBounds();

    auto timeRect = r.removeFromTop(paramControlHeight);
    timeLabel.setBounds(timeRect.removeFromLeft(paramLabelWidth));
    timeSlider.setBounds(timeRect);

    auto feedbackRect = r.removeFromTop(paramControlHeight);
    feedbackLabel.setBounds(feedbackRect.removeFromLeft(paramLabelWidth));
    feedbackSlider.setBounds(feedbackRect);

    auto mixRect = r.removeFromTop(paramControlHeight);
    mixLabel.setBounds(mixRect.removeFromLeft(paramLabelWidth));
    mixSlider.setBounds(mixRect);
}
