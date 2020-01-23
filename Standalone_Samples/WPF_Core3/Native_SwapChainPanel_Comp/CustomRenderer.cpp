#include "pch.h"
#include "CustomRenderer.h"

using namespace D2D1;
using namespace Native_SwapChainPanel_Comp;

CustomRenderer::CustomRenderer() {
	CreateDeviceIndependentResources();
	CreateDeviceResources();
	CreateSizeDependentResources();
}

void CustomRenderer::Render() {

	if (!m_loadingComplete) {
		return;
	}

	auto center = D2D1::Point2F(m_renderTargetWidth / 2, m_renderTargetHeight / 2);

	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(m_backgroundColor);
	// draw circle
	ID2D1SolidColorBrush* outlineBrush;
	ID2D1SolidColorBrush* circleBrush;
	m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &outlineBrush);
	m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SeaGreen), &circleBrush);
	D2D1_ELLIPSE circle = D2D1::Ellipse(center, 100, 100);
	m_d2dContext->FillEllipse(circle, circleBrush);
	m_d2dContext->DrawEllipse(circle, outlineBrush);

	m_d2dContext->EndDraw();

	Present();

}

void CustomRenderer::CreateDeviceResources()
{
	Direct2DPanel::CreateDeviceResources();

	m_d2dContext->CreateSolidColorBrush(ColorF(ColorF::Black), &m_strokeBrush);

	// Set D2D's unit mode to pixels so that drawing operation units are interpreted in pixels rather than DIPS.
	m_d2dContext->SetUnitMode(D2D1_UNIT_MODE::D2D1_UNIT_MODE_PIXELS);

	m_loadingComplete = true;
}

void CustomRenderer::OnDeviceLost()
{
	// Handle device lost, then re-render.
	Direct2DPanel::OnDeviceLost();
	Render();
}

void CustomRenderer::OnSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ e)
{
	// Process SizeChanged event, then re-render at the new size.
	Direct2DPanel::OnSizeChanged(sender, e);
	Render();
}

void CustomRenderer::OnCompositionScaleChanged(Windows::UI::Xaml::Controls::SwapChainPanel^ sender, Platform::Object^ args)
{
	// Process CompositionScaleChanged event, then re-render at the new scale.
	Direct2DPanel::OnCompositionScaleChanged(sender, args);
	Render();
}

void CustomRenderer::OnResuming(Platform::Object^ sender, Platform::Object^ args)
{
	// Ensure content is rendered when the app is resumed.
	Render();
}
