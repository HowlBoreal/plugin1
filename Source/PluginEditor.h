#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SimpleGainAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit SimpleGainAudioProcessorEditor (SimpleGainAudioProcessor&);
    ~SimpleGainAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SimpleGainAudioProcessor& audioProcessor;

    juce::Slider gainSlider;
    juce::Label gainLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleGainAudioProcessorEditor)
};
