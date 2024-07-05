#include "Processor.hxx"
#include "Editor.hxx"

Editor::Editor(Processor& processor) : AudioProcessorEditor{&processor}, m_processor{processor}
{
    juce::ignoreUnused(m_processor);

    addAndMakeVisible(m_browser);

    m_browser.goToURL(juce::WebBrowserComponent::getResourceProviderRoot());

    setSize(400, 300);
}

Editor::~Editor() {}

auto Editor::paint(juce::Graphics& graphics) -> void
{
    graphics.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

auto Editor::resized() -> void
{
    m_browser.setBounds(getLocalBounds());
}
