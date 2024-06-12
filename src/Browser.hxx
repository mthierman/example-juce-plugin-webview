#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

struct Browser : juce::WebBrowserComponent
{
    using juce::WebBrowserComponent::WebBrowserComponent;

    auto pageAboutToLoad(const juce::String& newUrl) -> bool override;

    static auto
    createResource(const juce::String& resourceName) -> juce::WebBrowserComponent::Resource;

    static auto lookUpMimeType(const juce::String& filename,
                               const juce::String& defaultMimeType = "application/octet-stream")
        -> juce::String;

    static auto
    lookUpResource(const juce::String& url) -> std::optional<juce::WebBrowserComponent::Resource>;

    // clang-format off
    static inline std::unordered_map<juce::String, juce::String> s_mimeTypes{
        {"aac", "audio/aac"},
        {"aif", "audio/aiff"},
        {"aiff", "audio/aiff"},
        {"avif", "image/avif"},
        {"bmp", "image/bmp"},
        {"css", "text/css"},
        {"csv", "text/csv"},
        {"flac", "audio/flac"},
        {"gif", "image/gif"},
        {"htm", "text/html"},
        {"html", "text/html"},
        {"ico", "image/vnd.microsoft.icon"},
        {"jpeg", "image/jpeg"},
        {"jpg", "image/jpeg"},
        {"js", "text/javascript"},
        {"json", "application/json"},
        {"md", "text/markdown"},
        {"mid", "audio/midi"},
        {"midi", "audio/midi"},
        {"mjs", "text/javascript"},
        {"mp3", "audio/mpeg"},
        {"mp4", "video/mp4"},
        {"mpeg", "video/mpeg"},
        {"ogg", "audio/ogg"},
        {"otf", "font/otf"},
        {"pdf", "application/pdf"},
        {"png", "image/png"},
        {"rtf", "application/rtf"},
        {"svg", "image/svg+xml"},
        {"svgz", "image/svg+xml"},
        {"tif", "image/tiff"},
        {"tiff", "image/tiff"},
        {"ttf", "font/ttf"},
        {"txt", "text/plain"},
        {"wasm", "application/wasm"},
        {"wav", "audio/wav"},
        {"weba", "audio/webm"},
        {"webm", "video/webm"},
        {"webp", "image/webp"},
        {"woff", "font/woff"},
        {"woff2", "font/woff2"},
        {"xml", "application/xml"},
        {"zip", "application/zip"},
    };
    // clang-format on

    static inline std::unordered_map<juce::String, juce::WebBrowserComponent::Resource> s_resources{
        {"/index.html", createResource("index_html")},
        {"/index.js", createResource("index_js")},
        {"/index.css", createResource("index_css")},
        {"/favicon.ico", createResource("favicon_ico")},
    };
};
