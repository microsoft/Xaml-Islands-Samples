#include "pch.h"
#include "TreeViewHostUserControl.h"
#if __has_include("TreeViewHostUserControl.g.cpp")
#include "TreeViewHostUserControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::UI::Popups;

namespace winrt::MyApp::implementation
{
	TreeViewHostUserControl::TreeViewHostUserControl()
	{
		InitializeComponent();
		_nodes = winrt::single_threaded_observable_vector<MyApp::TreeViewNodeViewModel>();
	}

	event_token TreeViewHostUserControl::TreeViewNodeSelected(EventHandler<MyApp::TreeViewNodeViewModel> const& handler)
	{
		return _treeViewNodeSelected.add(handler);
	}

	void TreeViewHostUserControl::TreeViewNodeSelected(event_token const& token)
	{
		_treeViewNodeSelected.remove(token);
	}

	void TreeViewHostUserControl::TreeView_ItemInvoked(muxc::TreeView const& /* sender */, muxc::TreeViewItemInvokedEventArgs const& args)
	{
		auto node = args.InvokedItem().as<MyApp::TreeViewNodeViewModel>();
		_treeViewNodeSelected(*this, node);
	}

	IObservableVector<MyApp::TreeViewNodeViewModel> TreeViewHostUserControl::Nodes()
	{
		return _nodes;
	}
}
