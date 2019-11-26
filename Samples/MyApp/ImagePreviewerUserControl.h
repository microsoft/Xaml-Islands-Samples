#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "ImagePreviewerUserControl.g.h"
#include "TreeViewNodeViewModel.h"

namespace winrt::MyApp::implementation
{
    struct ImagePreviewerUserControl : ImagePreviewerUserControlT<ImagePreviewerUserControl>
    {
        ImagePreviewerUserControl();
		MyApp::TreeViewNodeViewModel ViewModel();
		void ViewModel(MyApp::TreeViewNodeViewModel const& value);
	private:
		MyApp::TreeViewNodeViewModel _viewModel{ nullptr };
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct ImagePreviewerUserControl : ImagePreviewerUserControlT<ImagePreviewerUserControl, implementation::ImagePreviewerUserControl>
    {
    };
}
