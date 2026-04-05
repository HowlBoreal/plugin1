#include "PluginEditor.h"

SimpleGainAudioProcessorEditor::SimpleGainAudioProcessorEditor (SimpleGainAudioProcessor& p)
    : AudioProcessorEditor (&p),
      audioProcessor (p)
{
    gainSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 72, 20);
    gainSlider.setTextValueSuffix (" dB");
    addAndMakeVisible (gainSlider);

    gainLabel.setText ("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (gainLabel);

    gainAttachment = std::make_unique<SliderAttachment> (audioProcessor.parameters, "gain", gainSlider);

    setSize (220, 260);
}

void SimpleGainAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (18.0f, juce::Font::bold));
    g.drawFittedText ("Simple Gain", getLocalBounds().removeFromTop (36), juce::Justification::centred, 1);
}

void SimpleGainAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (20);
    area.removeFromTop (26);

    gainLabel.setBounds (area.removeFromTop (24));
    area.removeFromTop (8);

    gainSlider.setBounds (area.withSizeKeepingCentre (160, 160));
}
