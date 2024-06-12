#pragma once

#include "Global.hxx"

#include <juce_audio_processors/juce_audio_processors.h>
#include <utility>
#include <map>

struct Processor final : public juce::AudioProcessor
{
    Processor();
    ~Processor() override;

    auto prepareToPlay(double sampleRate, int samplesPerBlock) -> void override;
    auto releaseResources() -> void override;

    auto isBusesLayoutSupported(const BusesLayout& layouts) const -> bool override;

    auto processBlock(juce::AudioBuffer<float>& buffer,
                      juce::MidiBuffer& midiMessages) -> void override;
    using AudioProcessor::processBlock;

    auto createEditor() -> juce::AudioProcessorEditor* override;
    auto hasEditor() const -> bool override;

    auto getName() const -> const juce::String override;

    auto acceptsMidi() const -> bool override;
    auto producesMidi() const -> bool override;
    auto isMidiEffect() const -> bool override;
    auto getTailLengthSeconds() const -> double override;

    auto getNumPrograms() -> int override;
    auto getCurrentProgram() -> int override;
    auto setCurrentProgram(int index) -> void override;
    auto getProgramName(int index) -> const juce::String override;
    auto changeProgramName(int index, const juce::String& newName) -> void override;

    auto getStateInformation(juce::MemoryBlock& destData) -> void override;
    auto setStateInformation(const void* data, int sizeInBytes) -> void override;

    std::map<Parameters, std::pair<juce::String, juce::String>> m_parameters{
        {Parameters::gain, std::make_pair("gain", "Gain")},
        {Parameters::invertPhase, std::make_pair("invertPhase", "Invert Phase")}};
    juce::AudioProcessorValueTreeState m_apvts;
    float m_previousGain{};
    std::atomic<float>* m_phaseParameter{nullptr};
    std::atomic<float>* m_gainParameter{nullptr};

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Processor)
};
