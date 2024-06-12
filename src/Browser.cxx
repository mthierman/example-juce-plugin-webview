#include "Browser.hxx"
#include "BinaryData.h"

#include <filesystem>

auto Browser::pageAboutToLoad(const juce::String& newUrl) -> bool
{
    return newUrl == "http://localhost:5173/" ||
           newUrl == juce::WebBrowserComponent::getResourceProviderRoot();
}

auto Browser::createResource(const juce::String& resourceName)
    -> juce::WebBrowserComponent::Resource
{
    juce::WebBrowserComponent::Resource resource;

    int dataSize{};
    auto namedResource{BinaryData::getNamedResource(resourceName.toUTF8(), dataSize)};

    resource.data.resize(dataSize);
    std::memcpy(resource.data.data(), namedResource, dataSize);

    resource.mimeType =
        lookUpMimeType(BinaryData::getNamedResourceOriginalFilename(resourceName.toUTF8()));

    return resource;
}

auto Browser::lookUpMimeType(const juce::String& filename,
                             const juce::String& defaultMimeType) -> juce::String
{
    if (auto iterator{s_mimeTypes.find(
            std::filesystem::path(filename.toStdString()).extension().string().substr(1))};
        iterator != s_mimeTypes.end())
    {
        return iterator->second;
    }

    else
    {
        return defaultMimeType;
    }
}

auto Browser::lookUpResource(const juce::String& url)
    -> std::optional<juce::WebBrowserComponent::Resource>
{
    const auto requestedUrl{url == "/" ? juce::String{"/index.html"} : url};

    for (const auto& [route, resource] : s_resources)
    {
        if (requestedUrl == route)
        {
            return resource;
        }
    }

    return std::nullopt;
}
