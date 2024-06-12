#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

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

  private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Processor)
};
