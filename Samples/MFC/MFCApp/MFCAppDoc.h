
// MFCAppDoc.h : interface of the CMFCAppDoc class
//


#pragma once


class CMFCAppDoc : public CDocument
{
protected: // create from serialization only
	CMFCAppDoc() noexcept;
	DECLARE_DYNCREATE(CMFCAppDoc)

// Attributes
public:
	winrt::MyApp::TreeViewNodeViewModel SelectedNode() const;
	void SelectedNode(winrt::MyApp::TreeViewNodeViewModel const& selectedNode);
private:
	winrt::MyApp::TreeViewNodeViewModel _selectedNode{ nullptr };
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFCAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
