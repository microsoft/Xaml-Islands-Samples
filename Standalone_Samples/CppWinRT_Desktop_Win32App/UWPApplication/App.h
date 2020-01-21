#pragma once
#include "App.g.h"
#include "App.base.h"
namespace winrt::UWPApplication::implementation
{
    class App : public AppT2<App>
    {
    public:
        App();
        ~App();
    };
}
namespace winrt::UWPApplication::factory_implementation
{
    class App : public AppT<App, implementation::App>
    {
    };
}

