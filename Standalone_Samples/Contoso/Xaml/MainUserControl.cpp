#include "pch.h"
#include "MainUserControl.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::MyApp::implementation
{
    MainUserControl::MainUserControl(winrt::Contoso::Interop::IMainFormInterop interop)
        : mainFormInterop(interop)
    {
        InitializeComponent();
    }

    void MainUserControl::OnGotoWeb(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        mainFormInterop.SwitchUI();
    }
}