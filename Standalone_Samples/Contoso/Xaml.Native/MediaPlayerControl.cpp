#include "pch.h"
#include "MediaPlayerControl.h"
#if __has_include("MediaPlayerControl.g.cpp")
#include "MediaPlayerControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::MyApp::implementation
{
    MediaPlayerControl::MediaPlayerControl()
    {
        InitializeComponent();
    }
}
