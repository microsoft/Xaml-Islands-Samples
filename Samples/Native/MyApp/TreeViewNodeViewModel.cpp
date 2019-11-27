#include "pch.h"
#include "TreeViewNodeViewModel.h"
#if __has_include("TreeViewNodeViewModel.g.cpp")
#include "TreeViewNodeViewModel.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;

namespace winrt::MyApp::implementation
{
	TreeViewNodeViewModel::TreeViewNodeViewModel() : TreeViewNodeViewModel(L"", Uri{ nullptr }, L"")
	{
	}

	TreeViewNodeViewModel::TreeViewNodeViewModel(hstring const& label, Uri const& icon, hstring const& imagePath) :
		_label(label), _icon(icon), _imagePath(imagePath)
	{
		_children = winrt::single_threaded_observable_vector<MyApp::TreeViewNodeViewModel>();
	}

	hstring TreeViewNodeViewModel::Label()
	{
		return _label;
	}
	void TreeViewNodeViewModel::Label(hstring const& value)
	{
		_label = value;
	}
	Uri TreeViewNodeViewModel::Icon()
	{
		return _icon;
	}
	void TreeViewNodeViewModel::Icon(Uri const& value)
	{
		_icon = value;
	}
	hstring TreeViewNodeViewModel::Memo()
	{
		return _memo;
	}
	void TreeViewNodeViewModel::Memo(hstring const& value)
	{
		_memo = value;
	}
	hstring TreeViewNodeViewModel::ImagePath()
	{
		return _imagePath;
	}
	void TreeViewNodeViewModel::ImagePath(hstring const& value)
	{
		_imagePath = value;
	}
	Windows::Foundation::Collections::IObservableVector<MyApp::TreeViewNodeViewModel> TreeViewNodeViewModel::Children()
	{
		return _children;
	}
}
