/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JustFlangerAudioProcessorEditor::JustFlangerAudioProcessorEditor (JustFlangerAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    rateLabel.setText("Rate, Hz", juce::dontSendNotification);
    addAndMakeVisible(rateLabel);
    addAndMakeVisible(rateSlider);
    rateAttachment.reset(new SliderAttachment(valueTreeState, "rate", rateSlider));

    depthLabel.setText("Depth, %", juce::dontSendNotification);
    addAndMakeVisible(depthLabel);
    addAndMakeVisible(depthSlider);
    depthAttachment.reset(new SliderAttachment(valueTreeState, "depth", depthSlider));

    feedbackLabel.setText("Feedback, %", juce::dontSendNotification);
    addAndMakeVisible(feedbackLabel);
    addAndMakeVisible(feedbackSlider);
    feedbackAttachment.reset(new SliderAttachment(valueTreeState, "feedback", feedbackSlider));

    mixLabel.setText("Mix, %", juce::dontSendNotification);
    addAndMakeVisible(mixLabel);
    addAndMakeVisible(mixSlider);
    mixAttachment.reset(new SliderAttachment(valueTreeState, "mix", mixSlider));

    setSize(paramSliderWidth + paramLabelWidth, juce::jmax(100, paramControlHeight * 4));
}

JustFlangerAudioProcessorEditor::~JustFlangerAudioProcessorEditor()
{
}

//==============================================================================
void JustFlangerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void JustFlangerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto r = getLocalBounds();

    auto rateRect = r.removeFromTop(paramControlHeight);
    rateLabel.setBounds(rateRect.removeFromLeft(paramLabelWidth));
    rateSlider.setBounds(rateRect);

    auto depthRect = r.removeFromTop(paramControlHeight);
    depthLabel.setBounds(depthRect.removeFromLeft(paramLabelWidth));
    depthSlider.setBounds(depthRect);

    auto feedbackRect = r.removeFromTop(paramControlHeight);
    feedbackLabel.setBounds(feedbackRect.removeFromLeft(paramLabelWidth));
    feedbackSlider.setBounds(feedbackRect);

    auto mixRect = r.removeFromTop(paramControlHeight);
    mixLabel.setBounds(mixRect.removeFromLeft(paramLabelWidth));
    mixSlider.setBounds(mixRect);
}
