#include "Processor.hxx"
#include "Editor.hxx"

Editor::Editor(Processor& processor) : AudioProcessorEditor{&processor}, m_processor{processor}
{
    juce::ignoreUnused(m_processor);

    addAndMakeVisible(m_browser);

#if defined(HOT_RELOAD)
    // Dev URL
    m_browser.goToURL("http://localhost:5173/");

    // Preview URL
    // m_browser.goToURL("http://localhost:4173/");

    // ResourceProvider
    // m_browser.goToURL(juce::WebBrowserComponent::getResourceProviderRoot());
#else
    m_browser.goToURL(juce::WebBrowserComponent::getResourceProviderRoot());
#endif

    setResizable(true, true);
    setResizeLimits(200, 100, 1920, 1080);
    setSize(200, 100);
}

Editor::~Editor() {}

auto Editor::paint(juce::Graphics& graphics) -> void
{
    graphics.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

auto Editor::resized() -> void { m_browser.setBounds(getLocalBounds()); }
