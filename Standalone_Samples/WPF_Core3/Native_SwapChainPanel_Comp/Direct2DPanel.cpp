#include "pch.h"
#include "Direct2DPanel.h"
using namespace Native_SwapChainPanel_Comp;
using namespace Microsoft::WRL;
using namespace D2D1;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Platform;
using namespace Concurrency;

static const float m_dipsPerInch = 96.0f;

Direct2DPanel::Direct2DPanel():
	m_loadingComplete(false),
	m_backgroundColor(D2D1::ColorF(D2D1::ColorF::AliceBlue)), // Default to white background.
	m_alphaMode(DXGI_ALPHA_MODE_UNSPECIFIED), // Default to ignore alpha, which can provide better performance if transparency is not required.
	m_compositionScaleX(1.0f),
	m_compositionScaleY(1.0f),
	m_height(1.0f),
	m_width(1.0f)
{
	// Register Event Listeners
	this->SizeChanged += ref new Windows::UI::Xaml::SizeChangedEventHandler(this, &Direct2DPanel::OnSizeChanged);
	this->CompositionScaleChanged += ref new Windows::Foundation::TypedEventHandler<SwapChainPanel^, Object^>(this, &Direct2DPanel::OnCompositionScaleChanged);
	Application::Current->Suspending += ref new SuspendingEventHandler(this, &Direct2DPanel::OnSuspending);
	Application::Current->Resuming += ref new EventHandler<Object^>(this, &Direct2DPanel::OnResuming);
}

void Direct2DPanel::CreateDeviceIndependentResources()
{
	CreateD2DFactory();
}

void Direct2DPanel::CreateDeviceResources()
{
	// This flag adds support for surfaces with a different color channel ordering
	// than the API default. It is required for compatibility with Direct2D.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
	// If the project is in a debug build, enable debugging via SDK Layers.
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// This array defines the set of DirectX hardware feature levels this app will support.
	// Note the ordering should be preserved.
	// Don't forget to declare your application's minimum required feature level in its
	// description.  All applications are assumed to support 9.1 unless otherwise stated.
	const D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	// Create the Direct3D 11 API device object.
	DX::ThrowIfFailed(
		D3D11CreateDevice(
			nullptr,                        // Specify nullptr to use the default adapter.
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			creationFlags,                  // Set debug and Direct2D compatibility flags.
			featureLevels,                  // List of feature levels this app can support.
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,              // Always set this to D3D11_SDK_VERSION for Windows Store apps.
			&device,                   // Returns the Direct3D device created.
			nullptr,
			&context
		)
	);
	// get the Direct3D11.3 device and context.
	DX::ThrowIfFailed(
		device.As(&m_d3dDevice)
	);

	DX::ThrowIfFailed(
		context.As(&m_d3dContext)
	);

	// create the Direct2D object and a corresponding context

	ComPtr<IDXGIDevice3> dxgiDevice;
	DX::ThrowIfFailed(
		m_d3dDevice.As(&dxgiDevice)
	);

	DX::ThrowIfFailed(
		m_d2dFactory->CreateDevice(dxgiDevice.Get(), &m_d2dDevice)
	);

	DX::ThrowIfFailed(
		m_d2dDevice->CreateDeviceContext(
			D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&m_d2dContext
		)
	);

	// Set D2D text anti-alias mode to Grayscale to ensure proper rendering of text on intermediate surfaces.
	m_d2dContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);


}

void Direct2DPanel::CreateSizeDependentResources()
{
	// Ensure dependent objects have been released.
	m_d2dContext->SetTarget(nullptr);
	m_d2dTargetBitmap = nullptr;
	m_d3dContext->OMSetRenderTargets(0, nullptr, nullptr);
	m_d3dContext->Flush1(D3D11_CONTEXT_TYPE_ALL, nullptr);

	// UpdateRenderTargetSize(); DX11 Template does dpi and scaling stuff here

	// Set render target size to the rendered size of the panel including the composition scale,
	// defaulting to the minimum of 1px if no size was specified.
	m_renderTargetWidth = m_width * m_compositionScaleX;
	m_renderTargetHeight = m_height * m_compositionScaleY;

	// If the swap chain already exists, then resize it.
	if (m_swapChain != nullptr)
	{
		HRESULT hr = m_swapChain->ResizeBuffers(
			2,
			static_cast<UINT>(m_renderTargetWidth),
			static_cast<UINT>(m_renderTargetHeight),
			DXGI_FORMAT_B8G8R8A8_UNORM,
			0
		);

		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			// If the device was removed for any reason, a new device and swap chain will need to be created.
			OnDeviceLost();
			return;

		}
		else
		{
			DX::ThrowIfFailed(hr);
		}
	}
	else // Otherwise, create a new one.
	{
		// Direct X Template considers HighRes / Scaling here
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		swapChainDesc.Width = static_cast<UINT>(m_renderTargetWidth);      // Match the size of the panel.
		swapChainDesc.Height = static_cast<UINT>(m_renderTargetHeight);
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;                  // This is the most common swap chain format.
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;                                 // Don't use multi-sampling.
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;                                      // Use double buffering to enable flip / minimize latency
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;        // All Windows Store apps must use this SwapEffect.
		swapChainDesc.Flags = 0;
		swapChainDesc.AlphaMode = m_alphaMode;

		// Get underlying DXGI Device from D3D Device.
		ComPtr<IDXGIDevice3> dxgiDevice;
		DX::ThrowIfFailed(
			m_d3dDevice.As(&dxgiDevice)
		);

		// Get adapter.
		ComPtr<IDXGIAdapter> dxgiAdapter;
		DX::ThrowIfFailed(
			dxgiDevice->GetAdapter(&dxgiAdapter)
		);

		// Get factory.
		ComPtr<IDXGIFactory4> dxgiFactory;
		DX::ThrowIfFailed(
			dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
		);

		ComPtr<IDXGISwapChain1> swapChain;
		// Create swap chain.
		DX::ThrowIfFailed(
			dxgiFactory->CreateSwapChainForComposition(
				m_d3dDevice.Get(),
				&swapChainDesc,
				nullptr,
				&swapChain
			)
		);
		swapChain.As(&m_swapChain);

		// Ensure that DXGI does not queue more than one frame at a time. This both reduces
		// latency and ensures that the application will only render after each VSync, minimizing
		// power consumption.
		DX::ThrowIfFailed(
			dxgiDevice->SetMaximumFrameLatency(1)
		);

		Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([=]()
		{
			//Get backing native interface for SwapChainPanel.
			ComPtr<ISwapChainPanelNative> panelNative;
			DX::ThrowIfFailed(
				reinterpret_cast<IUnknown*>(this)->QueryInterface(IID_PPV_ARGS(&panelNative))
			);

			// Associate swap chain with SwapChainPanel.  This must be done on the UI thread.
			DX::ThrowIfFailed(
				panelNative->SetSwapChain(m_swapChain.Get())
			);
		}, CallbackContext::Any));
	}

	// Direct X Template Handles Screen Rotation here

	// Direct X Template Creates RenderTargetView for the Backbuffer here

	// Direct X Template Creates DepthStencilView for use with 3D Rendering

	// Direct X Template sets the 3D rendering viewport


	// Ensure the physical pixel size of the swap chain takes into account both the XAML SwapChainPanel's logical layout size and
	// any cumulative composition scale applied due to zooming, render transforms, or the system's current scaling plateau.
	// For example, if a 100x100 SwapChainPanel has a cumulative 2x scale transform applied, we instead create a 200x200 swap chain
	// to avoid artifacts from scaling it up by 2x, then apply an inverse 1/2x transform to the swap chain to cancel out the 2x transform.
	DXGI_MATRIX_3X2_F inverseScale = { 0 };
	inverseScale._11 = 1.0f / m_compositionScaleX;
	inverseScale._22 = 1.0f / m_compositionScaleY;

	m_swapChain->SetMatrixTransform(&inverseScale);

	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
			m_dipsPerInch * m_compositionScaleX,
			m_dipsPerInch * m_compositionScaleY
		);

	// Direct2D needs the DXGI version of the backbuffer surface pointer.
	ComPtr<IDXGISurface2> dxgiBackBuffer;
	DX::ThrowIfFailed(
		m_swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer))
	);

	// Get a D2D surface from the DXGI back buffer to use as the D2D render target.
	DX::ThrowIfFailed(
		m_d2dContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer.Get(),
			&bitmapProperties,
			&m_d2dTargetBitmap
		)
	);

	m_d2dContext->SetDpi(m_dipsPerInch * m_compositionScaleX, m_dipsPerInch * m_compositionScaleY);
	m_d2dContext->SetTarget(m_d2dTargetBitmap.Get());
}

void Direct2DPanel::CreateD2DFactory()
{

	// Initialize Direct2D resources.
	D2D1_FACTORY_OPTIONS options;
	ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

#if defined(_DEBUG)
	// If the project is in a debug build, enable Direct2D debugging via SDK Layers.
	options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

	// Initialize the Direct2D Factory.
	DX::ThrowIfFailed(
		D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			__uuidof(ID2D1Factory3),
			&options,
			&m_d2dFactory
		)
	);
}

void Native_SwapChainPanel_Comp::Direct2DPanel::Present()
{
	//Direct X Template omits the parameters and discards d3d rendertarget and depthstencil views
	DXGI_PRESENT_PARAMETERS parameters = { 0 };
	parameters.DirtyRectsCount = 0;
	parameters.pDirtyRects = nullptr;
	parameters.pScrollRect = nullptr;
	parameters.pScrollOffset = nullptr;

	HRESULT hr = S_OK;

	hr = m_swapChain->Present1(1, 0, &parameters);

	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
	{
		OnDeviceLost();
	}
	else
	{
		DX::ThrowIfFailed(hr);
	}
}

void Native_SwapChainPanel_Comp::Direct2DPanel::OnSuspending(Platform::Object ^ sender, Windows::ApplicationModel::SuspendingEventArgs ^ e)
{
	critical_section::scoped_lock lock(m_criticalSection);
	ComPtr<IDXGIDevice3> dxgiDevice;
	m_d3dDevice.As(&dxgiDevice);

	// Hints to the driver that the app is entering an idle state and that its memory can be used temporarily for other apps.
	dxgiDevice->Trim();
}

void Native_SwapChainPanel_Comp::Direct2DPanel::OnDeviceLost()
{
	// DirectX Template omits loadingComplete flag. No concurrency?
	m_loadingComplete = false;

	m_swapChain = nullptr;


	// DirectX Template omits this step:
	// Make sure the rendering state has been released.
	m_d3dContext->OMSetRenderTargets(0, nullptr, nullptr);

	m_d2dContext->SetTarget(nullptr);
	m_d2dTargetBitmap = nullptr;

	m_d2dContext = nullptr;
	m_d2dDevice = nullptr;

	m_d3dContext->Flush();

	CreateDeviceResources();
	//DirectX Template: Set Dpi
	CreateSizeDependentResources();
}

void Native_SwapChainPanel_Comp::Direct2DPanel::OnSizeChanged(Platform::Object ^ sender, Windows::UI::Xaml::SizeChangedEventArgs ^ e)
{
	if (m_width != e->NewSize.Width || m_height != e->NewSize.Height)
	{
		critical_section::scoped_lock lock(m_criticalSection); // why is a CS necessary here?

		// Store values so they can be accessed from a background thread.
		m_width = max(e->NewSize.Width, 1.0f);
		m_height = max(e->NewSize.Height, 1.0f);

		// Recreate size-dependent resources when the panel's size changes.
		CreateSizeDependentResources();
	}
}

void Native_SwapChainPanel_Comp::Direct2DPanel::OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel ^ sender, Platform::Object ^ args)
{
	if (m_compositionScaleX != CompositionScaleX || m_compositionScaleY != CompositionScaleY)
	{
		critical_section::scoped_lock lock(m_criticalSection);

		// Store values so they can be accessed from a background thread.
		m_compositionScaleX = this->CompositionScaleX;
		m_compositionScaleY = this->CompositionScaleY;

		// Recreate size-dependent resources when the composition scale changes.
		CreateSizeDependentResources();
	}
}

