//
// Declaration of the InternalUserControl class.
//

#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "InternalUserControl.g.h"

namespace winrt::SampleUserControl::implementation
{
    struct InternalUserControl : InternalUserControlT<InternalUserControl>
    {
        InternalUserControl();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::SampleUserControl::factory_implementation
{
    struct InternalUserControl : InternalUserControlT<InternalUserControl, implementation::InternalUserControl>
    {
    };
}
