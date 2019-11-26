// WindowsDesktopHost.cpp : implementation file
//

#include "pch.h"
#include "ChromeTester.h"
#include "WindowsDesktopHost.h"

IMPLEMENT_DYNAMIC(CWindowsDesktopHost, CBasePane)

CWindowsDesktopHost::CWindowsDesktopHost()
{
}

CWindowsDesktopHost::~CWindowsDesktopHost()
{
}

BEGIN_MESSAGE_MAP(CWindowsDesktopHost, CBasePane)
END_MESSAGE_MAP()

BOOL CWindowsDesktopHost::Create(CWnd* pParentWnd, DWORD dwStyle)
{
    auto parentWnd = pParentWnd->GetSafeHwnd();
    auto native = m_xamlIsland.as<IDesktopWindowXamlSourceNative2>();
    winrt::check_hresult(native->AttachToWindow(parentWnd));
    HWND islandWnd = nullptr;
    winrt::check_hresult(native->get_WindowHandle(&islandWnd));
    return Attach(islandWnd);
}

BOOL CWindowsDesktopHost::PreTranslateMessage(MSG* pMsg)
{
    auto native = m_xamlIsland.as<IDesktopWindowXamlSourceNative2>();
    BOOL result = false;
    winrt::check_hresult(native->PreTranslateMessage(pMsg, &result));
    return result;
}

winrt::Windows::UI::Xaml::UIElement CWindowsDesktopHost::Content()
{
    return m_xamlIsland.Content();
}

void CWindowsDesktopHost::Content(winrt::Windows::UI::Xaml::UIElement content)
{
    m_xamlIsland.Content(content);
}

