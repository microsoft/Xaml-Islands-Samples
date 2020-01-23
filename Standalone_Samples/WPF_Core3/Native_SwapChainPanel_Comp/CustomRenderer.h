#pragma once

#include "pch.h"
#include "Direct2DPanel.h"
namespace Native_SwapChainPanel_Comp {

	//[Windows::Foundation::Metadata::WebHostHidden] //Identifies the type as one whose functionality is not projected into the specified target language.
	public ref class CustomRenderer sealed :
		public Native_SwapChainPanel_Comp::Direct2DPanel
	{
	public:
		CustomRenderer();

	private protected:
		virtual void Render() override;
		virtual void CreateDeviceResources() override;

		virtual void OnDeviceLost() override;
		virtual void OnSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e) override;
		virtual void OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel^ sender, Platform::Object^ args) override;
		virtual void OnResuming(Platform::Object^ sender, Platform::Object^ args) override;

		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>                        m_strokeBrush;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>                        m_fillBrush;
	};
}
