#pragma once

#include "pch.h"
#include "winrt/Microsoft.ReactNative.h"
#include "NativeModules.h"
#include "RNMapsModule.g.h"

#include <map>

namespace winrt::RNMaps::implementation
{

    class RNMapsModule : public RNMapsModuleT<RNMapsModule>
    {
    public:
        RNMapsModule(Microsoft::ReactNative::IReactContext const &reactContext);

        static winrt::Windows::Foundation::Collections::
            IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType>
            NativeProps() noexcept;
        void UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const &propertyMapReader) noexcept;

        static winrt::Microsoft::ReactNative::ConstantProviderDelegate
        ExportedCustomBubblingEventTypeConstants() noexcept;
        static winrt::Microsoft::ReactNative::ConstantProviderDelegate
        ExportedCustomDirectEventTypeConstants() noexcept;

        static winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> Commands() noexcept;
        void DispatchCommand(
            winrt::hstring const &commandId,
            winrt::Microsoft::ReactNative::IJSValueReader const &commandArgsReader) noexcept;

        void AddFeature(winrt::Windows::UI::Xaml::UIElement child, int64_t index);
    private:
        Microsoft::ReactNative::IReactContext m_reactContext{nullptr};
        Windows::UI::Xaml::Controls::Maps::MapControl m_mapControl;
        std::map<int64_t, winrt::Windows::UI::Xaml::UIElement&> m_features;
        
        Windows::UI::Xaml::Controls::TextBlock mTextBlock;
        hstring mText;
    };
}

namespace winrt::RNMaps::factory_implementation
{
    struct RNMapsModule : RNMapsModuleT<RNMapsModule, implementation::RNMapsModule>
    {
    };
}
