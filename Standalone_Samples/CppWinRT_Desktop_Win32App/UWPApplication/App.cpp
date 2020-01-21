#include "pch.h"
#include "App.h"
using namespace winrt;
using namespace Windows::UI::Xaml;
namespace winrt::UWPApplication::implementation
{
    App::App()
    {
        Initialize();
        AddRef();// This is workaround
        m_inner.as<::IUnknown>()->Release();
    }
    App::~App()
    {
        Close();
    }
}