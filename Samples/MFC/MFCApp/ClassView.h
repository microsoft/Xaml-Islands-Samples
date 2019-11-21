
#pragma once

#include "ViewTree.h"

class CClassView : public CDockablePane
{
public:
	CClassView() noexcept;
	virtual ~CClassView();

	void AdjustLayout();
	void TreeViewodeSelectedHandler(winrt::Windows::Foundation::IInspectable const& sender, winrt::MyApp::TreeViewNodeViewModel const& args);

private:
	winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource _desktopWindowXamlSource{ nullptr };
	winrt::MyApp::TreeViewHostUserControl _treeView{ nullptr };
	
protected:

// Overrides
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};

