//#pragma once
#include "pch.h"
#include <concrt.h> // Concurrency Runtime Task Scheduler
#include "DirectXHelper.h"
namespace Native_SwapChainPanel_Comp {

	public ref class Direct2DPanel : public Windows::UI::Xaml::Controls::SwapChainPanel
	{
		void BeginDraw();
		//void DrawSmiley();
		void EndDraw();

	protected private:

		Direct2DPanel();
		// Resource Creation
		void CreateDeviceIndependentResources();
		virtual void CreateDeviceResources();
		void CreateSizeDependentResources();

		void CreateD2DFactory();

		//void UpdateRenderTargetSize();
		//void SetSwapChain();

		// Event Handlers
		virtual void OnDeviceLost();
		virtual void OnSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e);
		virtual void OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel ^sender, Platform::Object ^args);
		virtual void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
		virtual void OnResuming(Platform::Object^ sender, Platform::Object^ args) { };

		// Output
		virtual void Render() { };
		virtual void Present();

		// DirectX Ressources
		Microsoft::WRL::ComPtr<ID3D11Device3>								m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext3>						m_d3dContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain3>                             m_swapChain;
		//Microsoft::WRL::ComPtr<IDXGIDevice> m_dxgiDevice;

		// Direct2D objects
		Microsoft::WRL::ComPtr<ID2D1Factory3>						    	m_d2dFactory;
		Microsoft::WRL::ComPtr<ID2D1Device>								    m_d2dDevice;
		Microsoft::WRL::ComPtr<ID2D1DeviceContext>						    m_d2dContext;
		Microsoft::WRL::ComPtr<ID2D1Bitmap1>								m_d2dTargetBitmap;

		// Parallel Execution helpers
		bool                                                                m_loadingComplete;
		Concurrency::critical_section                                       m_criticalSection;

		// Graphical Properties
		D2D1_COLOR_F                                                        m_backgroundColor;
		DXGI_ALPHA_MODE                                                     m_alphaMode;

		float                                                               m_renderTargetHeight;
		float                                                               m_renderTargetWidth;

		float                                                               m_compositionScaleX;
		float                                                               m_compositionScaleY;

		float                                                               m_height;
		float                                                               m_width;
	};
}
