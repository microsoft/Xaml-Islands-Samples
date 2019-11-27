#include "pch.h"
#include "MyUserControl.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::SampleUserControl::implementation
{
    MyUserControl::MyUserControl()
    {
        InitializeComponent();
    }

    winrt::hstring MyUserControl::MyProperty()
    {
        return Text1().Text();
    }

    void MyUserControl::MyProperty(winrt::hstring value)
    {
        Text1().Text(value);
    }

    void MyUserControl::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        Text1().Text(sender.as<winrt::Windows::UI::Xaml::Controls::Button>().Name());
    }
}

