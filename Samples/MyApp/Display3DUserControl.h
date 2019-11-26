//
// Declaration of the MainUserControl class.
//

#pragma once
#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "Display3DUserControl.g.h"

using namespace winrt;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Xaml::Shapes;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::MyApp::implementation
{
	struct Display3DUserControl : Display3DUserControlT<Display3DUserControl>
	{
		
		Image _hubbleImage = Image{ nullptr };
		Compositor _compositor = Compositor{ nullptr };
		ContainerVisual _hostVisual = ContainerVisual{ nullptr };
		Scenes::SceneVisual _sceneVisual = Scenes::SceneVisual{ nullptr };
		hstring _modelPath;
		hstring ModelPath();
		void ModelPath(hstring value);

		Display3DUserControl();
		void Show3D_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
	};
}

namespace winrt::MyApp::factory_implementation
{
	struct Display3DUserControl : Display3DUserControlT<Display3DUserControl, implementation::Display3DUserControl>
	{
	};
}
