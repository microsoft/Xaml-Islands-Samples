#include "pch.h"
#include "MainUserControl.h"
#include <TreeViewNodeViewModel.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::MyApp::implementation
{
    MainUserControl::MainUserControl()
    {  

        InitializeComponent();
        for (int i = 0; i < 800; i++) {
            auto child = winrt::make<MyApp::implementation::TreeViewNodeViewModel>(L"Label", winrt::Windows::Foundation::Uri{ nullptr }, L"");

            treeView().Nodes().Append(child);
        }
    }

    winrt::hstring MainUserControl::MyProperty()
    {
        return hstring{};
        // return userControl().MyProperty();
    }

    void MainUserControl::MyProperty(winrt::hstring value)
    {
        // userControl().MyProperty(value);
    }
}
