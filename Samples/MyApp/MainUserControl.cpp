#include "pch.h"
#include "MainUserControl.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::MyApp::implementation
{
    MainUserControl::MainUserControl()
    {  

        InitializeComponent();
    }

    winrt::hstring MainUserControl::MyProperty()
    {
        return userControl().MyProperty();
    }

    void MainUserControl::MyProperty(winrt::hstring value)
    {
        userControl().MyProperty(value);
    }
}
