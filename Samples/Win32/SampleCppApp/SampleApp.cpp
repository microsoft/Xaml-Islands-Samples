#include "pch.h"

#include "framework.h"
#include "SampleApp.h"
#include "XamlBridge.h"
#include <ShellScalingApi.h>
#include <winrt/Microsoft.Toolkit.Win32.UI.XamlHost.h>
#include <winrt/SampleLibraryCS.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst = nullptr; // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

class MyWindow : public DesktopWindowT<MyWindow>
{
public:
    MyWindow(HINSTANCE hInstance, int nCmdShow) noexcept
    {
        LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
        LoadStringW(hInstance, IDC_SAMPLECPPAPP, szWindowClass, MAX_LOADSTRING);

        WNDCLASSEXW wcex = {};
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = DLGWINDOWEXTRA;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAMPLECPPAPP));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SAMPLECPPAPP);
        wcex.lpszClassName = szWindowClass;
        wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
        WINRT_VERIFY(RegisterClassEx(&wcex));
        WINRT_ASSERT(!GetHandle());

        const auto wnd = InitInstance(hInstance, nCmdShow);
        WINRT_ASSERT(wnd);
    }

    LRESULT MessageHandler(UINT const message, WPARAM const wParam, LPARAM const lParam) noexcept
    {
        HRESULT hr = S_OK;

        switch (message)
        {
            HANDLE_MSG(GetHandle(), WM_CREATE, OnCreate);
            HANDLE_MSG(GetHandle(), WM_COMMAND, OnCommand);
            HANDLE_MSG(GetHandle(), WM_DESTROY, OnDestroy);
            HANDLE_MSG(GetHandle(), WM_SIZE, OnResize);
        default:
            return base_type::MessageHandler(message, wParam, lParam);
        }

        return base_type::MessageHandler(message, wParam, lParam);
    }

private:

    wil::unique_hwnd m_hButton1 = nullptr;
    wil::unique_hwnd m_hButton2 = nullptr;
    wil::unique_hwnd m_hWndXamlIsland = nullptr;
    wil::unique_hwnd m_hWndXamlButton1 = nullptr;
    winrt::MyApp::MainUserControl m_mainUserControl = nullptr;
    winrt::SampleLibraryCS::CustomUserControl m_managedControl = nullptr;
    winrt::Windows::UI::Xaml::Controls::Button m_xamlBt1 = nullptr;
    winrt::Windows::UI::Xaml::Controls::Button::Click_revoker m_xamlBt1ClickEventRevoker;

    HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
    {
        hInst = hInstance; // Store instance handle in our global variable
        HWND hMainWnd = CreateWindow(
            szWindowClass,
            szTitle,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, InitialWidth, InitialHeight,
            nullptr, nullptr, hInstance, this);

        if (!hMainWnd)
        {
            winrt::check_hresult(E_FAIL);
        }

        ShowWindow(hMainWnd, nCmdShow);
        UpdateWindow(hMainWnd);
        SetFocus(hMainWnd);
        return hMainWnd;
    }

    const static WPARAM IDM_ButtonID1 = 0x1001;
    const static WPARAM IDM_ButtonID2 = 0x1002;

    bool OnCreate(HWND, LPCREATESTRUCT)
    {
        m_hButton1 = wil::unique_hwnd(CreateWindow(TEXT("button"), TEXT("Button &1"),
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
            (ButtonMargin + InitialWidth - ButtonWidth) / 2, ButtonMargin,
            ButtonWidth, ButtonHeight,
            GetHandle(), (HMENU)IDM_ButtonID1, hInst, NULL));

        DEVICE_SCALE_FACTOR scaleFactor = {};
        winrt::check_hresult(GetScaleFactorForMonitor(MonitorFromWindow(GetHandle(), 0), &scaleFactor));
        const auto dpi = static_cast<int>(scaleFactor) / 100.0f;


        m_managedControl = winrt::SampleLibraryCS::CustomUserControl();
        m_managedControl.Height(ButtonHeight / dpi);
        m_managedControl.Width(ButtonWidth / dpi);
        m_hWndXamlButton1 = wil::unique_hwnd(CreateDesktopWindowsXamlSource(WS_TABSTOP, m_managedControl));

        //m_xamlBt1 = LoadXamlControl<winrt::Windows::UI::Xaml::Controls::Button>(IDR_XAML_BUTTON1);
        //m_xamlBt1.Height(ButtonHeight / dpi);
        //m_xamlBt1.Width(ButtonWidth / dpi);
        //m_xamlBt1ClickEventRevoker = m_xamlBt1.Click(winrt::auto_revoke, { this, &MyWindow::OnXamlButtonClick });
        //m_hWndXamlButton1 = wil::unique_hwnd(CreateDesktopWindowsXamlSource(WS_TABSTOP, m_xamlBt1));

        m_mainUserControl = winrt::MyApp::MainUserControl();
        m_hWndXamlIsland = wil::unique_hwnd(CreateDesktopWindowsXamlSource(WS_TABSTOP, m_mainUserControl));

        m_hButton2 = wil::unique_hwnd(CreateWindow(TEXT("button"), TEXT("Button &2"),
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
            (ButtonMargin + InitialWidth - ButtonWidth) / 2, InitialHeight - ButtonMargin - ButtonHeight,
            ButtonWidth, ButtonHeight,
            GetHandle(), (HMENU)IDM_ButtonID2, hInst, NULL));

        return true;
    }

    void OnCommand(HWND, int id, HWND hwndCtl, UINT codeNotify)
    {
        switch (id)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), GetHandle(), About);
            break;
        case IDM_EXIT:
            PostQuitMessage(0);
            break;
        case IDM_ButtonID1:
        case IDM_ButtonID2:
            if (m_mainUserControl)
            {
                const auto string = (id == IDM_ButtonID1) ? winrt::hstring(L"Native button 1") : winrt::hstring(L"Native button 2");
                m_mainUserControl.MyProperty(string);
            }
            break;
        }
    }

    void OnDestroy(HWND hwnd)
    {
        if (m_xamlBt1ClickEventRevoker)
        {
            m_xamlBt1ClickEventRevoker.revoke();
        }

        base_type::OnDestroy(hwnd);
    }

    void OnResize(HWND, UINT state, int cx, int cy)
    {
        const auto newHeight = cy;
        const auto newWidth = cx;
        const auto islandHeight = newHeight - (ButtonHeight * 2) - ButtonMargin;
        const auto islandWidth = newWidth - (ButtonMargin * 2);
        SetWindowPos(m_hButton1.get(), 0, ButtonWidth * 2, ButtonMargin, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
        SetWindowPos(m_hWndXamlButton1.get(), m_hButton1.get(), newWidth - (ButtonWidth * 2), ButtonMargin, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
        SetWindowPos(m_hWndXamlIsland.get(), m_hWndXamlButton1.get(), 0, XamlIslandMargin, islandWidth, islandHeight, SWP_SHOWWINDOW);
        SetWindowPos(m_hButton2.get(), m_hWndXamlIsland.get(), (ButtonMargin + newWidth - ButtonWidth) / 2, newHeight - ButtonMargin - ButtonHeight, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
    }

    void OnXamlButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        m_mainUserControl.MyProperty(winrt::hstring(L"Xaml K Button 1"));
    }
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    ::MessageBox(NULL, L"Press ENTER to continue", L"Debug", 0);

    winrt::init_apartment(winrt::apartment_type::single_threaded);
    winrt::MyApp::App app;

    MyWindow myWindow(hInstance, nCmdShow);
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAMPLECPPAPP));
    int retValue = myWindow.MessageLoop(hAccelTable);

    app.Close();
    app = nullptr;

    return retValue;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
