# C++/WinRT Win32 app that contains XAML Islands

This project contains a C++/WinRT Win32 Windows application with an entry point. This is the Win32 app that contains the __Xaml Islands__.


```C
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);
    winrt::MyApp::App app;

    ...
    // The DesktopWindowXamlSource object creates the Xaml Island
    winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource desktopSource;
    // Get handle to corewindow
    auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();
    // Parent the DesktopWindowXamlSource object to current window
    hr = interop->AttachToWindow(parentWindow);
    winrt::check_hresult(hr);

    // Get the new child window's hwnd. This is the Xaml Island's window 
    hr = interop->get_WindowHandle(&hWndXamlIsland);
    winrt::check_hresult(hr);
    SetFocus(hWndXamlIsland);

    const auto newHeight = InitialHeight;
    const auto newWidth = InitialWidth;
    const auto margin = XamlIslandMargin;
    SetWindowPos(hWndXamlIsland, 0, margin, margin, newHeight - margin, newWidth - margin, SWP_SHOWWINDOW);

    winrt::MyApp::MainUserControl mainUserControl;
    mainUserControl.UpdateLayout();
    desktopSource.Content(mainUserControl);

    ...
    
    while (GetMessage(&msg, nullptr, 0, 0))
    {
       BOOL xamlSourceProcessedMessage = FALSE;
       auto xamlSourceNative2 = desktopSource.as<IDesktopWindowXamlSourceNative2>();
       hr = xamlSourceNative2->PreTranslateMessage(&msg, &xamlSourceProcessedMessage);
       winrt::check_hresult(hr);
       if (!xamlSourceProcessedMessage && !TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
       {
           TranslateMessage(&msg);
           DispatchMessage(&msg);
       }
   }
   desktopSource.Close();
   app.Close();
   return 0;
}
```
