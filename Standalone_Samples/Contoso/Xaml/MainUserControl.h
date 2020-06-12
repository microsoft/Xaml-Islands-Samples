//
// Declaration of the MainUserControl class.
//

#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "MainUserControl.g.h"
#include <winrt/Contoso.Interop.h>

namespace winrt::MyApp::implementation
{
    struct MainUserControl : MainUserControlT<MainUserControl>
    {
        MainUserControl(winrt::Contoso::Interop::IMainFormInterop interop);

        void OnGotoWeb(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void OnShare(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::Contoso::Interop::IMainFormInterop mainFormInterop;
        winrt::Windows::ApplicationModel::DataTransfer::DataTransferManager dataTransferManager{ nullptr };
        winrt::event_token dataRequestedEventToken;
        void OnDataRequested(winrt::Windows::ApplicationModel::DataTransfer::DataTransferManager const& sender, winrt::Windows::ApplicationModel::DataTransfer::DataRequestedEventArgs const& e);
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct MainUserControl : MainUserControlT<MainUserControl, implementation::MainUserControl>
    {
    };
}
