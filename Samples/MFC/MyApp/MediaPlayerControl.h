#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "MediaPlayerControl.g.h"

namespace winrt::MyApp::implementation
{
    struct MediaPlayerControl : MediaPlayerControlT<MediaPlayerControl>
    {
        MediaPlayerControl();
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct MediaPlayerControl : MediaPlayerControlT<MediaPlayerControl, implementation::MediaPlayerControl>
    {
    };
}
