#include "pch.h"
#include "InternalUserControl.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::SampleUserControl::implementation
{
    InternalUserControl::InternalUserControl()
    {
        InitializeComponent();
    }

    int32_t InternalUserControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void InternalUserControl::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void InternalUserControl::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
