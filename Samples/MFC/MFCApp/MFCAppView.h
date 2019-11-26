
// MFCAppView.h : interface of the CMFCAppView class
//

#pragma once

class CMFCAppView : public CView
{
protected: // create from serialization only
	CMFCAppView() noexcept;
	DECLARE_DYNCREATE(CMFCAppView)

// Attributes
public:
	CMFCAppDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource _desktopWindowXamlSource{ nullptr };
	winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource inkDesktopSource{ nullptr };
	winrt::MyApp::Display3DUserControl _display3DUserControl{ nullptr };
	winrt::MyApp::MediaPlayerControl _mediaPlayerControl{ nullptr };
	winrt::MyApp::ImagePreviewerUserControl _imagePreviewerUserControl{ nullptr };

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void AdjustLayout();
};

#ifndef _DEBUG  // debug version in MFCAppView.cpp
inline CMFCAppDoc* CMFCAppView::GetDocument() const
   { return reinterpret_cast<CMFCAppDoc*>(m_pDocument); }
#endif

