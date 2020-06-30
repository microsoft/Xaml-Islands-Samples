#include "pch.h"
#include "MainUserControl.h"
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <Windows.ApplicationModel.DataTransfer.h>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::ApplicationModel::DataTransfer;

namespace winrt::MyApp::implementation
{
    MainUserControl::MainUserControl(winrt::Contoso::Interop::IMainFormInterop interop)
        : mainFormInterop(interop)
    {
        InitializeComponent();

        dtmInterop = winrt::get_activation_factory<DataTransferManager, IDataTransferManagerInterop>();

        HWND mainWindow = reinterpret_cast<HWND>(mainFormInterop.WindowHandle());
        winrt::check_hresult(dtmInterop->GetForWindow(mainWindow, winrt::guid_of<ABI::Windows::ApplicationModel::DataTransfer::IDataTransferManager>(), winrt::put_abi(dataTransferManager)));

        dataRequestedEventToken = dataTransferManager.DataRequested({ this, &MainUserControl::OnDataRequested });
    }

    MainUserControl::~MainUserControl()
    {
        dataTransferManager.DataRequested(dataRequestedEventToken);
    }


    void MainUserControl::OnDataRequested(DataTransferManager const& sender, DataRequestedEventArgs const& e)
    {
        auto request = e.Request();
        request.Data().Properties().Title(L"Share Text Example");
        request.Data().Properties().Description(L"An example of how to share text.");
        request.Data().SetText(L"Hello World!");
    }

    void MainUserControl::OnGotoWeb(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        mainFormInterop.SwitchUI();
    }

    void MainUserControl::OnShare(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        HWND mainWindow = reinterpret_cast<HWND>(mainFormInterop.WindowHandle());
        winrt::check_hresult(dtmInterop->ShowShareUIForWindow(mainWindow));
    }

}