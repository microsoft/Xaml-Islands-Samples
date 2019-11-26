#pragma once

#pragma push_macro("TRY")
#undef TRY
#include <unknwn.h> // To enable support for non-WinRT interfaces, unknwn.h must be included before any C++/WinRT headers.
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#pragma pop_macro("TRY")

class CWindowsDesktopHost : public CBasePane
{
    DECLARE_DYNAMIC(CWindowsDesktopHost)

public:
    CWindowsDesktopHost();
    virtual ~CWindowsDesktopHost();

    BOOL Create(CWnd* pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP);

    winrt::Windows::UI::Xaml::UIElement Content();
    void Content(winrt::Windows::UI::Xaml::UIElement content);

protected:
    DECLARE_MESSAGE_MAP()

    BOOL PreTranslateMessage(MSG* pMsg) override;

private:
    winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource m_xamlIsland;
};
