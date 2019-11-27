//
// Declaration of the MyUserControl class.
//

#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "MyUserControl.g.h"

namespace winrt::SampleUserControl::implementation
{
    struct MyUserControl : MyUserControlT<MyUserControl>
    {
        MyUserControl();

        hstring MyProperty();
        void MyProperty(hstring value);
		void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
	};
}

namespace winrt::SampleUserControl::factory_implementation
{
    struct MyUserControl : MyUserControlT<MyUserControl, implementation::MyUserControl>
    {
    };
}
