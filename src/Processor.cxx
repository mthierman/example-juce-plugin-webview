#include "Processor.hxx"
#include "Editor.hxx"

Processor::Processor()
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
      )
{
}

Processor::~Processor() {}

auto Processor::getName() const -> const juce::String
{
    return JucePlugin_Name;
}

auto Processor::acceptsMidi() const -> bool
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

auto Processor::producesMidi() const -> bool
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

auto Processor::isMidiEffect() const -> bool
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

auto Processor::getTailLengthSeconds() const -> double
{
    return 0.0;
}

auto Processor::getNumPrograms() -> int
{
    return 1;
}

auto Processor::getCurrentProgram() -> int
{
    return 0;
}

auto Processor::setCurrentProgram(int index) -> void
{
    juce::ignoreUnused(index);
}

auto Processor::getProgramName(int index) -> const juce::String
{
    juce::ignoreUnused(index);

    return {};
}

auto Processor::changeProgramName(int index, const juce::String& newName) -> void
{
    juce::ignoreUnused(index, newName);
}

auto Processor::prepareToPlay(double sampleRate, int samplesPerBlock) -> void
{
    juce::ignoreUnused(sampleRate, samplesPerBlock);
}

auto Processor::releaseResources() -> void {}

auto Processor::isBusesLayoutSupported(const BusesLayout& layouts) const -> bool
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);

    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
    {
        return false;
    }
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    {
        return false;
    }
#endif
    return true;
#endif
}

auto Processor::processBlock(juce::AudioBuffer<float>& buffer,
                             juce::MidiBuffer& midiMessages) -> void
{
    juce::ignoreUnused(midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        juce::ignoreUnused(channelData);
    }
}

auto Processor::hasEditor() const -> bool
{
    return true;
}

auto Processor::createEditor() -> juce::AudioProcessorEditor*
{
    return new Editor(*this);
}

auto Processor::getStateInformation(juce::MemoryBlock& destData) -> void
{
    juce::ignoreUnused(destData);
}

auto Processor::setStateInformation(const void* data, int sizeInBytes) -> void
{
    juce::ignoreUnused(data, sizeInBytes);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Processor();
}
