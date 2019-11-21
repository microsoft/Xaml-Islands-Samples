
// MFCAppView.cpp : implementation of the CMFCAppView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApp.h"
#endif

#include "MFCAppDoc.h"
#include "MFCAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml::Hosting;
using namespace MyApp;
// CMFCAppView

IMPLEMENT_DYNCREATE(CMFCAppView, CView)

BEGIN_MESSAGE_MAP(CMFCAppView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCAppView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMFCAppView construction/destruction

CMFCAppView::CMFCAppView() noexcept
{
	// TODO: add construction code here

}

CMFCAppView::~CMFCAppView()
{
}

BOOL CMFCAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCAppView drawing

void CMFCAppView::OnDraw(CDC* pDC)
{
	CMFCAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->SelectedNode() != nullptr)
	{
		LPCTSTR imagePath = pDoc->SelectedNode().ImagePath().c_str();

		PWSTR result = StrStr(imagePath, _T("gltf"));
		PWSTR mediaResult = StrStr(imagePath, _T("mp4"));

		//handle 2D nodes
		if (result == nullptr && mediaResult == nullptr)
		{
			result = StrStr(imagePath, _T("Hubble.png"));

			//Handle Inking Image node
			if (result != nullptr && inkDesktopSource == nullptr)
			{
				//XAML Island section
				HWND hWndXamlIsland;

				// This inkDesktopSource is the object that enables a non-UWP desktop application 
				// to host UWP controls in any UI element that is associated with a window handle (HWND).
				inkDesktopSource = winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource{ };

				// Get handle to corewindow
				auto interop = inkDesktopSource.as<IDesktopWindowXamlSourceNative>();
				// Parent the DesktopWindowXamlSource object to current window
				check_hresult(interop->AttachToWindow(this->GetSafeHwnd()));

				// This Hwnd will be the window handler for the Xaml Island: A child window that contains Xaml.  
				hWndXamlIsland = nullptr;
				// Get the new child window's hwnd 
				interop->get_WindowHandle(&hWndXamlIsland);

				RECT size;
				GetWindowRect(&size);
				auto viewWidth = size.right - size.left;
				auto viewHeight = size.bottom - size.top;	

				// Update the xaml island window size becuase initially is 0,0
				::SetWindowPos(hWndXamlIsland, NULL, 0, 0, viewWidth, viewHeight, SWP_SHOWWINDOW);

				//Creating the Xaml content
				Windows::UI::Xaml::Controls::RelativePanel xamlContainer;

				xamlContainer.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Stretch);
				xamlContainer.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Stretch);

				Windows::UI::Xaml::Controls::TextBlock tb;
				tb.Text(pDoc->SelectedNode().Label().c_str());
				tb.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
				tb.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
				tb.FontSize(48);


				Windows::UI::Xaml::Controls::Image image;
				Windows::Foundation::Uri uri(pDoc->SelectedNode().ImagePath().c_str());
				Windows::UI::Xaml::Media::Imaging::BitmapImage bitmapImage(uri);
				image.Source(bitmapImage);
				

				xamlContainer.Children().Append(image);
				xamlContainer.SetAlignLeftWithPanel(image, true);
				xamlContainer.SetAlignRightWithPanel(image, true);
				xamlContainer.SetAlignHorizontalCenterWithPanel(image, true);

				Windows::UI::Xaml::Controls::InkCanvas ic;


				ic.InkPresenter().InputDeviceTypes(winrt::Windows::UI::Core::CoreInputDeviceTypes::Touch | winrt::Windows::UI::Core::CoreInputDeviceTypes::Mouse);

				Windows::UI::Xaml::Controls::InkToolbar it;
				it.TargetInkCanvas(ic);
				it.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Left);
				it.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Top);


				xamlContainer.Children().Append(ic);
				xamlContainer.Children().Append(it);

				xamlContainer.SetAlignLeftWithPanel(ic, true);
				xamlContainer.SetAlignTopWithPanel(ic, true);
				xamlContainer.SetAlignBottomWithPanel(ic, true);
				xamlContainer.SetAlignRightWithPanel(ic, true);

				xamlContainer.SetAlignLeftWithPanel(it, true);
				xamlContainer.SetAlignTopWithPanel(it, true);
				
				xamlContainer.UpdateLayout();
				inkDesktopSource.Content(xamlContainer);
				AdjustLayout();
			}
			//Handling general MFC Image nodes
			else if (result == nullptr)
			{
				if (_desktopWindowXamlSource == nullptr)
				{
					_desktopWindowXamlSource = DesktopWindowXamlSource{};
					auto interop = _desktopWindowXamlSource.as<IDesktopWindowXamlSourceNative>();
					check_hresult(interop->AttachToWindow(GetSafeHwnd()));
					_imagePreviewerUserControl = winrt::MyApp::ImagePreviewerUserControl();
					_imagePreviewerUserControl.ViewModel(pDoc->SelectedNode());
					_desktopWindowXamlSource.Content(_imagePreviewerUserControl);
					AdjustLayout();
				}
				//RECT size;
				//GetWindowRect(&size);
				//CImage image;
				//if (SUCCEEDED(image.Load(pDoc->SelectedNode().ImagePath().c_str())))
				//{
				//	auto viewWidth = size.right - size.left;
				//	auto viewHeight = size.bottom - size.top;
				//	auto width = image.GetWidth();
				//	auto height = image.GetHeight();
				//	image.Draw(*pDC, viewWidth / 2 - width / 2, viewHeight / 2 - height / 2, width, height);
				//}

				//CFont font;
				//font.CreatePointFont(200, L"Calibri"); // 20pt Calibri
				//auto oldFont = pDC->SelectObject(font);
				//RECT windowRect;
				//GetWindowRect(&windowRect);
				//RECT drawTextRect{ 0, 10, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top };
				//pDC->DrawText(pDoc->SelectedNode().Label().c_str(), &drawTextRect, DT_CENTER | DT_WORDBREAK);
				//pDC->SelectObject(oldFont);
			}

		}
		else if (result == nullptr && mediaResult != nullptr)
		{
			if (_desktopWindowXamlSource == nullptr)
			{

				LPCTSTR imagePath = pDoc->SelectedNode().ImagePath().c_str();
				PWSTR result = StrStr(imagePath, _T("mp4"));
				if (result != nullptr)
				{
					_desktopWindowXamlSource = DesktopWindowXamlSource{};
					auto interop = _desktopWindowXamlSource.as<IDesktopWindowXamlSourceNative>();
					check_hresult(interop->AttachToWindow(GetSafeHwnd()));

					HWND xamlHostHwnd = NULL;
					check_hresult(interop->get_WindowHandle(&xamlHostHwnd));

					_mediaPlayerControl = winrt::MyApp::MediaPlayerControl();					
					_desktopWindowXamlSource.Content(_mediaPlayerControl);

					AdjustLayout();
				}
			}
		}
		//handle 3D node
		else
		{
			if (_desktopWindowXamlSource == nullptr)
			{

				LPCTSTR imagePath = pDoc->SelectedNode().ImagePath().c_str();
				PWSTR result = StrStr(imagePath, _T("gltf"));
				if (result != nullptr)
				{
					_desktopWindowXamlSource = DesktopWindowXamlSource{};
					auto interop = _desktopWindowXamlSource.as<IDesktopWindowXamlSourceNative>();
					check_hresult(interop->AttachToWindow(GetSafeHwnd()));

					HWND xamlHostHwnd = NULL;
					check_hresult(interop->get_WindowHandle(&xamlHostHwnd));

					_display3DUserControl = winrt::MyApp::Display3DUserControl();
					_display3DUserControl.ModelPath(imagePath);
					_desktopWindowXamlSource.Content(_display3DUserControl);

					AdjustLayout();
				}
			}
		}

	}



}


// CMFCAppView printing


void CMFCAppView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCAppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCAppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCAppView diagnostics

#ifdef _DEBUG
void CMFCAppView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCAppDoc* CMFCAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCAppDoc)));
	return (CMFCAppDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCAppView message handlers


int CMFCAppView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

void CMFCAppView::OnClose()
{
	CView::OnClose();
}

void CMFCAppView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CMFCAppView::AdjustLayout()
{
	if (_desktopWindowXamlSource != nullptr)
	{
		auto interop = _desktopWindowXamlSource.as<IDesktopWindowXamlSourceNative>();
		HWND xamlHostHwnd = NULL;
		check_hresult(interop->get_WindowHandle(&xamlHostHwnd));

		RECT windowRect;
		GetWindowRect(&windowRect);
		::SetWindowPos(xamlHostHwnd, NULL, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_SHOWWINDOW);
	}
	if (inkDesktopSource != nullptr)
	{
		auto interop = inkDesktopSource.as<IDesktopWindowXamlSourceNative>();
		HWND xamlHostHwnd = NULL;
		check_hresult(interop->get_WindowHandle(&xamlHostHwnd));

		RECT windowRect;
		GetWindowRect(&windowRect);
		::SetWindowPos(xamlHostHwnd, NULL, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_SHOWWINDOW);

	}
}
