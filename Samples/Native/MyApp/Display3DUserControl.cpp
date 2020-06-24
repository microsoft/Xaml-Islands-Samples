#include "pch.h"
#include "Display3DUserControl.h"
#include <winrt\Windows.UI.Xaml.Controls.h>

using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Xaml::Hosting;
#ifdef __SCENE_LOADER__
using namespace winrt::SceneLoaderComponent;
#endif
using namespace Windows::Foundation::Numerics;
using namespace winrt::Windows::UI::Composition::Scenes;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::MyApp::implementation
{

	IAsyncAction  LoadGltf(Compositor const& _compositor, SceneVisual const& _sceneVisual, ContainerVisual const& _hostVisual, Image const& mc, hstring const& modelPath)
	{
		
		Uri uri{ modelPath };
		auto buffer{ co_await FileIO::ReadBufferAsync(co_await StorageFile::GetFileFromApplicationUriAsync(uri)) };
#ifdef __SCENE_LOADER__
		auto loader = SceneLoader{};
		auto sceneNode = loader.Load(buffer, _compositor);
#endif

		_hostVisual.RelativeSizeAdjustment(Numerics::float2().one());

		ElementCompositionPreview::SetElementChildVisual(mc, _hostVisual);

		_sceneVisual.Scale(float3(2.5f, 2.5f, 1.0f));
		_sceneVisual.Root(SceneNode::Create(_compositor));
		_sceneVisual.Root().Children().Clear();
#ifdef __SCENE_LOADER__
		_sceneVisual.Root().Children().Append(sceneNode);
#endif // __SCENE_LOADER__

		auto rotationAnimation = _compositor.CreateScalarKeyFrameAnimation();
		rotationAnimation.InsertKeyFrame(1.0f, 360.0f, _compositor.CreateLinearEasingFunction());
		rotationAnimation.Duration(std::chrono::seconds{ 16 });
		rotationAnimation.IterationBehavior(AnimationIterationBehavior::Forever);
		_sceneVisual.Root().Transform().RotationAxis(float3(0.0f, 1.0f, 0.2f));

		_sceneVisual.Root().Transform().StartAnimation(L"RotationAngleInDegrees", rotationAnimation);

		_hostVisual.Children().InsertAtTop(_sceneVisual);

	}

	Display3DUserControl::Display3DUserControl()
	{
		InitializeComponent();


		_compositor = Window::Current().Compositor();
		_hostVisual = _compositor.CreateContainerVisual();
		_sceneVisual = SceneVisual::Create(_compositor);
		_sceneVisual.Offset(float3(800.0f, 300.0f, 0));

	}



	winrt::hstring Display3DUserControl::ModelPath()
	{
		return _modelPath;
	}

	void Display3DUserControl::ModelPath(winrt::hstring value)
	{
		_modelPath = value;
	}
}



void winrt::MyApp::implementation::Display3DUserControl::Show3D_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{
	_hubbleImage = HubbleImage();
	LoadGltf(_compositor, _sceneVisual, _hostVisual, _hubbleImage,_modelPath);
}
