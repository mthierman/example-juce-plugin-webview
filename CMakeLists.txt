cmake_minimum_required(VERSION 3.27)

project(WebViewTemplate VERSION 0.0.0)

include(FetchContent)

FetchContent_Declare(
    webview2
    URL https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2
        SOURCE_DIR
        "${CMAKE_BINARY_DIR}/_deps/Microsoft.Web.WebView2"
    )

FetchContent_MakeAvailable(webview2)

set(JUCE_WEBVIEW2_PACKAGE_LOCATION "${CMAKE_BINARY_DIR}/_deps")

add_subdirectory(libs/JUCE)

juce_add_plugin(
    ${PROJECT_NAME}
    PRODUCT_NAME
    ${PROJECT_NAME}
    PLUGIN_MANUFACTURER_CODE
    Juce
    PLUGIN_CODE
    Dem0
    FORMATS
    AU
    VST3
    Standalone
    COPY_PLUGIN_AFTER_BUILD
    FALSE
    NEEDS_WEBVIEW2
    TRUE
    )

target_sources(
    ${PROJECT_NAME}
    PRIVATE "src/Browser.cxx"
            "src/Editor.cxx"
            "src/Processor.cxx"
    )

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_compile_definitions(
    ${PROJECT_NAME}
    PUBLIC JUCE_WEB_BROWSER=1
           JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1
           JUCE_USE_CURL=0
           JUCE_VST3_CAN_REPLACE_VST2=0
    )

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE ${PROJECT_NAME}_BinaryData
            juce::juce_audio_utils
            juce::juce_gui_extra
    PUBLIC juce::juce_recommended_config_flags
           juce::juce_recommended_lto_flags
           juce::juce_recommended_warning_flags
    )

juce_add_binary_data(
    ${PROJECT_NAME}_BinaryData
    HEADER_NAME
    "BinaryData.h"
    NAMESPACE
    "BinaryData"
    SOURCES
    "index.html"
    )
