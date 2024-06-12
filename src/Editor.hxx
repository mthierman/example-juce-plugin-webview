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

    juce::WebSliderRelay m_gainRelay{m_browser, "gain"};
    juce::WebToggleButtonRelay m_phaseRelay{m_browser, "invertPhase"};

    Browser m_browser{
        juce::WebBrowserComponent::Options{}
            .withBackend(juce::WebBrowserComponent::Options::Backend::webview2)
            .withWinWebView2Options(
                juce::WebBrowserComponent::Options::WinWebView2{}.withUserDataFolder(
                    juce::File::getSpecialLocation(juce::File::SpecialLocationType::tempDirectory)))
            .withNativeIntegrationEnabled()
            .withOptionsFrom(m_gainRelay)
            .withOptionsFrom(m_phaseRelay)
            .withResourceProvider([this](const auto& url) { return Browser::lookUpResource(url); },
                                  juce::URL{"http://localhost:5173/"}.getOrigin())};

    juce::WebSliderParameterAttachment m_gainAttachment{
        *m_processor.m_apvts.getParameter(m_processor.m_parameters.at(Parameters::gain).first),
        m_gainRelay, m_processor.m_apvts.undoManager};
    juce::WebToggleButtonParameterAttachment m_phaseAttachment{
        *m_processor.m_apvts.getParameter(
            m_processor.m_parameters.at(Parameters::invertPhase).first),
        m_phaseRelay, m_processor.m_apvts.undoManager};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Editor)
};
