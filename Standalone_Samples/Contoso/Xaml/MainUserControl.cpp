#include "pch.h"
#include "MainUserControl.h"
#include <winrt/Windows.ApplicationModel.DataTransfer.h>

//#define SHGDNF enum
//#include <Shobjidl_core.h>

MIDL_INTERFACE("3E68D4BD-7135-4D10-8018-9FB6D9F33FA1")
IInitializeWithWindow : public IUnknown
{
public:
    virtual HRESULT STDMETHODCALLTYPE Initialize(
        /* [in] */ __RPC__in HWND hwnd) = 0;

};

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::ApplicationModel::DataTransfer;

namespace winrt::MyApp::implementation
{
    MainUserControl::MainUserControl(winrt::Contoso::Interop::IMainFormInterop interop)
        : mainFormInterop(interop)
    {
        InitializeComponent();

        dataTransferManager = DataTransferManager::GetForCurrentView();
        auto initWithWindow = dataTransferManager.as<IInitializeWithWindow>();
        HWND mainWindow = reinterpret_cast<HWND>(mainFormInterop.WindowHandle());
        initWithWindow->Initialize(mainWindow);

        static auto ev = dataRequestedEventToken = dataTransferManager.DataRequested({ this, &MainUserControl::OnDataRequested });
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
        dataTransferManager.ShowShareUI();
    }

}