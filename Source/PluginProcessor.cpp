#include "PluginProcessor.h"
#include "PluginEditor.h"

SimpleGainAudioProcessor::SimpleGainAudioProcessor()
    : AudioProcessor (BusesProperties().withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      parameters (*this, nullptr, "PARAMETERS", createParameterLayout())
{
}

void SimpleGainAudioProcessor::prepareToPlay (double, int)
{
}

void SimpleGainAudioProcessor::releaseResources()
{
}

bool SimpleGainAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto& mainInLayout  = layouts.getMainInputChannelSet();
    const auto& mainOutLayout = layouts.getMainOutputChannelSet();

    if (mainInLayout != mainOutLayout)
        return false;

    return mainOutLayout == juce::AudioChannelSet::mono()
        || mainOutLayout == juce::AudioChannelSet::stereo();
}

void SimpleGainAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    const auto gainDb = parameters.getRawParameterValue ("gain")->load();
    const auto linearGain = juce::Decibels::decibelsToGain (gainDb);

    buffer.applyGain (linearGain);
}

juce::AudioProcessorEditor* SimpleGainAudioProcessor::createEditor()
{
    return new SimpleGainAudioProcessorEditor (*this);
}

bool SimpleGainAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String SimpleGainAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleGainAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleGainAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleGainAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleGainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleGainAudioProcessor::getNumPrograms()
{
    return 1;
}

int SimpleGainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleGainAudioProcessor::setCurrentProgram (int)
{
}

const juce::String SimpleGainAudioProcessor::getProgramName (int)
{
    return {};
}

void SimpleGainAudioProcessor::changeProgramName (int, const juce::String&)
{
}

void SimpleGainAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto state = parameters.copyState(); auto xml = state.createXml())
        copyXmlToBinary (*xml, destData);
}

void SimpleGainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xmlState = getXmlFromBinary (data, sizeInBytes))
    {
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout SimpleGainAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> layout;

    layout.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { "gain", 1 },
        "Gain",
        juce::NormalisableRange<float> (-24.0f, 24.0f, 0.1f),
        0.0f,
        "dB"));

    return { layout.begin(), layout.end() };
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleGainAudioProcessor();
}
