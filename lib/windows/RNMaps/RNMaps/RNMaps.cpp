#include "pch.h"
#include "JSValueXaml.h"
#include "RNMaps.h"
#include "RNMapsModule.g.cpp"

namespace winrt
{
    using namespace Microsoft::ReactNative;
    using namespace Windows::Data::Json;
    using namespace Windows::Foundation;
    using namespace Windows::UI;
    using namespace Windows::UI::Popups;
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Controls;
    using namespace Windows::UI::Xaml::Controls::Maps;
    using namespace Windows::UI::Xaml::Input;
    using namespace Windows::UI::Xaml::Media;
} // namespace winrt

namespace winrt::RNMaps::implementation
{

    RNMapsModule::RNMapsModule(winrt::IReactContext const& reactContext) : m_reactContext(reactContext)
    {
        m_mapControl = Windows::UI::Xaml::Controls::Maps::MapControl();
        m_mapControl.MapServiceToken(/*put your token here for testing*/);
        this->Children().Append(m_mapControl);
    }

    winrt::Windows::Foundation::Collections::
        IMapView<winrt::hstring, winrt::Microsoft::ReactNative::ViewManagerPropertyType>
        RNMapsModule::NativeProps() noexcept
    {
        // TODO: define props here
        auto nativeProps = winrt::single_threaded_map<hstring, ViewManagerPropertyType>();
        nativeProps.Insert(L"sampleProp", ViewManagerPropertyType::String);
        return nativeProps.GetView();
    }

    void RNMapsModule::UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const& propertyMapReader) noexcept
    {
    }

    winrt::Microsoft::ReactNative::ConstantProviderDelegate RNMapsModule::ExportedCustomBubblingEventTypeConstants() noexcept
    {
        return nullptr;
    }

    winrt::Microsoft::ReactNative::ConstantProviderDelegate RNMapsModule::ExportedCustomDirectEventTypeConstants() noexcept
    {
        return nullptr;
    }

    winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> RNMapsModule::Commands() noexcept
    {
        // TODO: deifne commands supported by the control
        auto commands = winrt::single_threaded_vector<hstring>();
        commands.Append(L"sampleCommand");
        return commands.GetView();
    }

    void RNMapsModule::DispatchCommand(winrt::hstring const& commandId, winrt::Microsoft::ReactNative::IJSValueReader const& commandArgsReader) noexcept
    {
        // TODO: handle commands here
    }

    void RNMapsModule::AddFeature(winrt::Windows::UI::Xaml::UIElement child, int64_t index)
    {
        m_children.InsertAt(index, child);
        if (auto childModule = child.try_as<winrt::RNMaps::RNPolylineModule>())
        {
            childModule.AddToMap(m_mapControl, index);
        }
        else if (auto childModule = child.try_as<winrt::RNMaps::RNMapIconModule>())
        {
            childModule.AddToMap(m_mapControl, index);
        }
    }

    void RNMapsModule::RemoveAllFeatures() {
        m_children.Clear();
        m_mapControl.MapElements().Clear();
    }

    void RNMapsModule::RemoveFeature(int64_t index) {
        m_children.RemoveAt(index);
        m_mapControl.MapElements().RemoveAt(index);
    }

    void RNMapsModule::ReplaceFeature(winrt::Windows::UI::Xaml::UIElement oldChild, winrt::Windows::UI::Xaml::UIElement newChild) {
        uint32_t index;
        if (m_children.IndexOf(oldChild, index)) {
            m_mapControl.MapElements().RemoveAt(index);
            AddFeature(newChild, index);
        }
    }
}