#include "pch.h"
#include "ImagePreviewerUserControl.h"
#if __has_include("ImagePreviewerUserControl.g.cpp")
#include "ImagePreviewerUserControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::MyApp::implementation
{
	ImagePreviewerUserControl::ImagePreviewerUserControl()
    {
        InitializeComponent();
    }

	MyApp::TreeViewNodeViewModel ImagePreviewerUserControl::ViewModel()
	{
		return _viewModel;
	}
	void ImagePreviewerUserControl::ViewModel(MyApp::TreeViewNodeViewModel const& value)
	{
		_viewModel = value;
	}
}
