
// MFCAppDoc.cpp : implementation of the CMFCAppDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApp.h"
#endif

#include "MFCAppDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCAppDoc

IMPLEMENT_DYNCREATE(CMFCAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCAppDoc, CDocument)
END_MESSAGE_MAP()


// CMFCAppDoc construction/destruction

CMFCAppDoc::CMFCAppDoc() noexcept
{
	// TODO: add one-time construction code here

}

winrt::MyApp::TreeViewNodeViewModel CMFCAppDoc::SelectedNode() const
{
	return _selectedNode;
}

void CMFCAppDoc::SelectedNode(winrt::MyApp::TreeViewNodeViewModel const& selectedNode)
{
	_selectedNode = selectedNode;
	SetTitle(_selectedNode.Label().c_str());
}

CMFCAppDoc::~CMFCAppDoc()
{
}

BOOL CMFCAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCAppDoc serialization

void CMFCAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCAppDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCAppDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCAppDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCAppDoc diagnostics

#ifdef _DEBUG
void CMFCAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCAppDoc commands


BOOL CMFCAppDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	return TRUE;
}

