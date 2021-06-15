#include "pch.h"

#include "framework.h"
#include "SampleApp.h"
#include "XamlBridge.h"
#include <ShellScalingApi.h>
#include <winrt/Microsoft.Toolkit.Win32.UI.XamlHost.h>

const wchar_t c_WindowClass[] = L"SimpleCppAppWindowClass";

class AppWindow : public DesktopWindowT<AppWindow>
{
public:
    static int Show(HINSTANCE hInstance, int nCmdShow)
    {
        auto window = AppWindow(hInstance);
        window.CreateAndShowWindow(nCmdShow);
        return window.MessageLoop(window.m_accelerators.get());
    }

    LRESULT MessageHandler(UINT message, WPARAM wParam, LPARAM lParam) noexcept
    {
        switch (message)
        {
            HANDLE_MSG(WindowHandle(), WM_CREATE, OnCreate);
            HANDLE_MSG(WindowHandle(), WM_COMMAND, OnCommand);
            HANDLE_MSG(WindowHandle(), WM_DESTROY, OnDestroy);
            HANDLE_MSG(WindowHandle(), WM_SIZE, OnResize);
        default:
            return base_type::MessageHandler(message, wParam, lParam);
        }

        return base_type::MessageHandler(message, wParam, lParam);
    }

private:
    AppWindow(HINSTANCE hInstance) noexcept : m_instance(hInstance)
    {
    }

    void CreateAndShowWindow(int nCmdShow)
    {
        m_accelerators.reset(LoadAcceleratorsW(m_instance, MAKEINTRESOURCE(IDC_SAMPLECPPAPP)));

        WNDCLASSEXW wcex = { sizeof(wcex) };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.hInstance = m_instance;
        wcex.hIcon = LoadIconW(m_instance, MAKEINTRESOURCE(IDI_SAMPLECPPAPP));
        wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SAMPLECPPAPP);
        wcex.lpszClassName = c_WindowClass;
        wcex.hIconSm = LoadIconW(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
        RegisterClassExW(&wcex); // don't test result, handle error at CreateWindow

        wchar_t title[64];
        LoadStringW(m_instance, IDS_APP_TITLE, title, ARRAYSIZE(title));

        HWND window = CreateWindowW(c_WindowClass, title, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, InitialWidth, InitialHeight,
            nullptr, nullptr, m_instance, this);
        THROW_LAST_ERROR_IF(!window);

        ShowWindow(window, nCmdShow);
        UpdateWindow(window);
        SetFocus(window);
    }

    const static WPARAM IDM_ButtonID1 = 0x1001;
    const static WPARAM IDM_ButtonID2 = 0x1002;

    bool OnCreate(HWND, LPCREATESTRUCT) noexcept
    {
        PCWSTR buttonClass = L"button";

        m_button1 = wil::unique_hwnd(CreateWindowW(buttonClass, L"Button &1",
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
            (ButtonMargin + InitialWidth - ButtonWidth) / 2, ButtonMargin,
            ButtonWidth, ButtonHeight,
            WindowHandle(), reinterpret_cast<HMENU>(IDM_ButtonID1), m_instance, nullptr));

        DEVICE_SCALE_FACTOR scaleFactor{};
        winrt::check_hresult(GetScaleFactorForMonitor(MonitorFromWindow(WindowHandle(), 0), &scaleFactor));
        const auto dpi = static_cast<int>(scaleFactor) / 100.0f;

        // Demonstrate loading Xaml from a Win32 resource
        // m_xamlButton = LoadXamlControl<winrt::Windows::UI::Xaml::Controls::Button>(IDR_XAML_BUTTON1);
        // m_xamlButton.Height(ButtonHeight / dpi);
        // m_xamlButton.Width(ButtonWidth / dpi);
        // m_buttonClickRevoker = m_xamlButton.Click(winrt::auto_revoke, { this, &AppWindow::OnXamlButtonClick });
        // m_hWndXamlButton1 = wil::unique_hwnd(CreateDesktopWindowsXamlSource(WS_TABSTOP, m_xamlButton));

        m_mainUserControl = winrt::MyApp::MainUserControl();
        m_hWndXamlIsland = CreateDesktopWindowsXamlSource(WS_TABSTOP, m_mainUserControl);

        m_button2 = wil::unique_hwnd(CreateWindowW(buttonClass, L"Button &2",
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | WS_TABSTOP,
            (ButtonMargin + InitialWidth - ButtonWidth) / 2, InitialHeight - ButtonMargin - ButtonHeight,
            ButtonWidth, ButtonHeight,
            WindowHandle(), reinterpret_cast<HMENU>(IDM_ButtonID2), m_instance, nullptr));

        return true;
    }

    void OnCommand(HWND, int id, HWND hwndCtl, UINT codeNotify) noexcept
    {
        switch (id)
        {
        case IDM_ABOUT:
            DialogBoxW(m_instance, MAKEINTRESOURCE(IDD_ABOUTBOX), WindowHandle(), [](HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) -> INT_PTR
            {
                switch (message)
                {
                case WM_INITDIALOG:
                    return TRUE;

                case WM_COMMAND:
                    if ((LOWORD(wParam) == IDOK) || (LOWORD(wParam) == IDCANCEL))
                    {
                        EndDialog(hDlg, LOWORD(wParam));
                        return TRUE;
                    }
                    break;
                }
                return FALSE;
            });
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

    void OnDestroy(HWND hwnd) noexcept
    {
        m_buttonClickRevoker.revoke();
        base_type::OnDestroy(hwnd);
    }

    void OnResize(HWND, UINT state, int cx, int cy) noexcept
    {
        const auto newHeight = cy;
        const auto newWidth = cx;
        const auto islandHeight = newHeight - (ButtonHeight * 2) - ButtonMargin;
        const auto islandWidth = newWidth - (ButtonMargin * 2);
        SetWindowPos(m_button1.get(), 0, ButtonWidth * 2, ButtonMargin, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
        SetWindowPos(m_hWndXamlButton1.get(), m_button1.get(), newWidth - (ButtonWidth * 2), ButtonMargin, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
        SetWindowPos(m_hWndXamlIsland.get(), m_hWndXamlButton1.get(), 0, XamlIslandMargin, islandWidth, islandHeight, SWP_SHOWWINDOW);
        SetWindowPos(m_button2.get(), m_hWndXamlIsland.get(), (ButtonMargin + newWidth - ButtonWidth) / 2, newHeight - ButtonMargin - ButtonHeight, ButtonWidth, ButtonHeight, SWP_SHOWWINDOW);
    }

    void OnXamlButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        m_mainUserControl.MyProperty(winrt::hstring(L"Xaml K Button 1"));
    }

    const HINSTANCE m_instance;
    wil::unique_hwnd m_button1;
    wil::unique_hwnd m_button2;
    wil::unique_hwnd m_hWndXamlIsland;
    wil::unique_hwnd m_hWndXamlButton1;
    wil::unique_haccel m_accelerators;
    winrt::MyApp::MainUserControl m_mainUserControl{ nullptr };
    winrt::Windows::UI::Xaml::Controls::Button m_xamlButton{nullptr};
    winrt::Windows::UI::Xaml::Controls::Button::Click_revoker m_buttonClickRevoker;
};

// use ComCtl32 v6 for better UI.
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
// Note, the app manifest specifies DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR lpCmdLine, int nCmdShow)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);

    winrt::MyApp::App app;

    const auto result = AppWindow::Show(hInstance, nCmdShow);

    app.Close();

    return result;
}
