#pragma once

#include "TreeViewNodeViewModel.g.h"

namespace winrt::MyApp::implementation
{
    struct TreeViewNodeViewModel : TreeViewNodeViewModelT<TreeViewNodeViewModel>
    {
        TreeViewNodeViewModel();
		TreeViewNodeViewModel(hstring const& label, Windows::Foundation::Uri const& icon, hstring const& imagePath);
		hstring Label();
		void Label(hstring const& value);
		Windows::Foundation::Uri Icon();
		void Icon(Windows::Foundation::Uri const& value);
		hstring Memo();
		void Memo(hstring const& value);
		hstring ImagePath();
		void ImagePath(hstring const& value);
		Windows::Foundation::Collections::IObservableVector<MyApp::TreeViewNodeViewModel> Children();
	private:
		hstring _label;
		hstring _memo;
		Windows::Foundation::Uri _icon;
		hstring _imagePath;
		Windows::Foundation::Collections::IObservableVector<MyApp::TreeViewNodeViewModel> _children;
	};
}

namespace winrt::MyApp::factory_implementation
{
    struct TreeViewNodeViewModel : TreeViewNodeViewModelT<TreeViewNodeViewModel, implementation::TreeViewNodeViewModel>
    {
    };
}
