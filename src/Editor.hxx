#pragma once

#include "Browser.hxx"
#include "Processor.hxx"

struct Editor final : public juce::AudioProcessorEditor
{
    explicit Editor(Processor& processor);
    ~Editor() override;

    auto paint(juce::Graphics& graphics) -> void override;
    auto resized() -> void override;

  private:
    Processor& m_processor;

    Browser m_browser{
        juce::WebBrowserComponent::Options{}
            .withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
            .withWinWebView2Options(
                juce::WebBrowserComponent::Options::WinWebView2{}.withUserDataFolder(
                    juce::File::getSpecialLocation(juce::File::SpecialLocationType::tempDirectory)))
            .withNativeIntegrationEnabled()
            .withResourceProvider([this](const auto& url) { return Browser::lookUpResource(url); },
                                  juce::URL{"http://localhost:5173/"}.getOrigin())};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Editor)
};
