#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "TreeViewHostUserControl.g.h"
#include "TreeViewNodeViewModel.h"

namespace winrt::MyApp::implementation
{
	using namespace winrt;
	using namespace Windows::Foundation;
	using namespace Windows::Foundation::Collections;
	namespace muxc = Microsoft::UI::Xaml::Controls;
	
	struct TreeViewHostUserControl : TreeViewHostUserControlT<TreeViewHostUserControl>
    {
		TreeViewHostUserControl();
		event_token TreeViewNodeSelected(EventHandler<MyApp::TreeViewNodeViewModel> const& handler);
		void TreeViewNodeSelected(event_token const& token);
		void TreeView_ItemInvoked(muxc::TreeView const& sender, muxc::TreeViewItemInvokedEventArgs const& args);
		IObservableVector<MyApp::TreeViewNodeViewModel> Nodes();
	private:
		IObservableVector<MyApp::TreeViewNodeViewModel> _nodes;
		event<EventHandler<MyApp::TreeViewNodeViewModel>> _treeViewNodeSelected;
    };
}

namespace winrt::MyApp::factory_implementation
{
    struct TreeViewHostUserControl : TreeViewHostUserControlT<TreeViewHostUserControl, implementation::TreeViewHostUserControl>
    {
    };
}
