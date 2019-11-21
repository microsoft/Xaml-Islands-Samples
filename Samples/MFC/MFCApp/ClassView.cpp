
#include "pch.h"
#include "framework.h"
#include "MainFrm.h"
#include "ClassView.h"
#include "Resource.h"
#include "MFCApp.h"
#include "MFCAppDoc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml::Hosting;
using namespace MyApp;

CClassView::CClassView() noexcept
{
}

CClassView::~CClassView()
{
}

BEGIN_MESSAGE_MAP(CClassView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView message handlers

int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	auto createNodes = [](TreeViewHostUserControl control)
	{
		WCHAR path[MAX_PATH + 1];
		::GetModuleFileName(NULL, path, MAX_PATH);
		WCHAR drive[MAX_PATH + 1];
		WCHAR dir[MAX_PATH + 1];
		WCHAR fileName[MAX_PATH + 1];
		WCHAR extension[MAX_PATH + 1];
		_tsplitpath_s(path, drive, dir, fileName, extension);

		hstring basePath = hstring(drive) + dir;
		
		TreeViewNodeViewModel root{ L"Hubble Space Telescope", Uri{ nullptr }, L"ms-appx:///Assets/Telescope.gltf" };
		root.Children().Append({ L"Inking Telescope", Uri{ L"ms-appx:///Images/imageicon.png" }, basePath + L"Assets\\Hubble.png" });

		TreeViewNodeViewModel images{ L"Photos", Uri{ L"ms-appx:///Images/photosicon.png" }, L"" };
		images.Children().Append({ L"Veil Nebula Supernova Remnant", Uri{ L"ms-appx:///Images/imageicon.png" }, basePath + L"Assets\\1.jpg" });
		images.Children().Append({ L"Hubble Sets Sights on a Galaxy with a Bright Heart", Uri{ L"ms-appx:///Images/imageicon.png" }, basePath + L"Assets\\2.jpg" });
		images.Children().Append({ L"Hubble Captures Tangled Remnants of a Supernova", Uri{ L"ms-appx:///Images/imageicon.png" }, basePath + L"Assets\\3.jpg" });
		images.Children().Append({ L"Hubble Celebrates 29th Anniversary with a Colorful Look at the Southern Crab Nebula", Uri{ L"ms-appx:///Images/imageicon.png" }, basePath + L"Assets\\4.png" });
		images.Children().Append({ L"Hubble Spots Flock of Cosmic Ducks", Uri{ L"ms-appx:///Images/imageicon.png" }, basePath + L"Assets\\5.jpg" });
		images.Children().Append({ L"Hubble Shows Star ClusterÅfs True Identity", Uri{ L"ms-appx:///Images/imageicon.png" }, basePath + L"Assets\\6.jpg" });
		images.Children().Append({ L"Triangulum Galaxy Shows Stunning Face in Detailed Hubble Portrait", Uri{ L"ms-appx:///Images/imageicon.png" }, basePath + L"Assets\\7.png" });
		images.Children().Append({ L"Hubble Captures Tangled Remnants of a Supernova", Uri{ L"ms-appx:///Images/imageicon.png" },basePath + L"Assets\\8.jpg" });

		root.Children().Append(images);

		TreeViewNodeViewModel media{ L"Video", Uri { L"ms-appx:///Images/videoicon.png" }, L"ms-appx:///Assets/world.mp4" };
		root.Children().Append(media);

		TreeViewNodeViewModel journals{ L"Journals", Uri { L"ms-appx:///Images/journalsicon.png" }, L"" };
		TreeViewNodeViewModel forty{ L"40\'s", Uri { nullptr }, L"" };
		forty.Children().Append({ L"1946 First paper about space telescopes published", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		TreeViewNodeViewModel fifty{ L"50\'s", Uri { nullptr }, L"" };
		fifty.Children().Append({ L"1957 Sputnik launched", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		fifty.Children().Append({ L"1958 NASA created", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		TreeViewNodeViewModel sixty{ L"60\'s", Uri { nullptr }, L"" };
		sixty.Children().Append({ L"1969 Project gained support", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		TreeViewNodeViewModel seventy{ L"70\'s", Uri { nullptr }, L"" };
		seventy.Children().Append({ L"1974 First working group held", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		seventy.Children().Append({ L"1977 Congress approved funding and project began", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		seventy.Children().Append({ L"1978 Grinding of primary mirror began", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		seventy.Children().Append({ L"1979 Astronauts began training for servicing missions", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		TreeViewNodeViewModel eighty{ L"80\'s", Uri { nullptr }, L"" };
		eighty.Children().Append({ L"1983 Large space telescope named after Edwin Hubble", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		eighty.Children().Append({ L"1986 Space shuttle Challenger lost", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		TreeViewNodeViewModel ninety{ L"90\'s", Uri { nullptr }, L"" };
		ninety.Children().Append({ L"1990 Hubble launched", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		ninety.Children().Append({ L"1990 Hubble deployed", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		ninety.Children().Append({ L"1990 First image taken", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		ninety.Children().Append({ L"1990 Spherical aberration discovered in mirror", Uri { L"ms-appx:///Images/journalicon.png"}, L"" });
		journals.Children().Append(forty);
		journals.Children().Append(fifty);
		journals.Children().Append(sixty);
		journals.Children().Append(seventy);
		journals.Children().Append(eighty);
		journals.Children().Append(ninety);
		root.Children().Append(journals);


		control.Nodes().Append(root);
	};

	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	_desktopWindowXamlSource = DesktopWindowXamlSource{};
	auto interop = _desktopWindowXamlSource.as<IDesktopWindowXamlSourceNative>();
	check_hresult(interop->AttachToWindow(GetSafeHwnd()));

	HWND xamlHostHwnd = NULL;
	check_hresult(interop->get_WindowHandle(&xamlHostHwnd));

	_treeView = TreeViewHostUserControl{};
	createNodes(_treeView);
	_treeView.TreeViewNodeSelected({ this, &CClassView::TreeViewodeSelectedHandler });
	_desktopWindowXamlSource.Content(_treeView);

	AdjustLayout();
	return 0;
}

void CClassView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CClassView::AdjustLayout()
{
	auto interop = _desktopWindowXamlSource.as<IDesktopWindowXamlSourceNative>();
	HWND xamlHostHwnd = NULL;
	check_hresult(interop->get_WindowHandle(&xamlHostHwnd));

	RECT windowRect;
	GetWindowRect(&windowRect);
	::SetWindowPos(xamlHostHwnd, NULL, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_SHOWWINDOW);
}

BOOL CClassView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CClassView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}


void CClassView::OnClose()
{
	_treeView = nullptr;
	_desktopWindowXamlSource.Close();
	_desktopWindowXamlSource = nullptr;

	CDockablePane::OnClose();
}

void CClassView::TreeViewodeSelectedHandler(IInspectable const& /* sender */, winrt::MyApp::TreeViewNodeViewModel const& args)
{
	auto findDocumentFromDocumentTemplate = [](CDocTemplate const* docTemplate, hstring const& fraberName)
	{
		auto docPos = docTemplate->GetFirstDocPosition();
		while (docPos)
		{
			auto doc = dynamic_cast<CMFCAppDoc*>(docTemplate->GetNextDoc(docPos));
			if (doc->SelectedNode().Label() == fraberName)
			{
				return doc;
			}
		}

		return static_cast<CMFCAppDoc*>(NULL);
	};

	if (args.ImagePath().empty())
	{
		return;
	}

	auto pos = theApp.m_pDocManager->GetFirstDocTemplatePosition();
	auto docTemplate = theApp.m_pDocManager->GetNextDocTemplate(pos);
	ASSERT(docTemplate);

	// find doc
	auto doc = findDocumentFromDocumentTemplate(docTemplate, args.Label());
	if (doc)
	{
		auto viewPos = doc->GetFirstViewPosition();
		auto view = doc->GetNextView(viewPos);
		view->GetParentFrame()->ActivateFrame(SW_RESTORE);
	}
	else
	{
		auto doc = dynamic_cast<CMFCAppDoc*>(docTemplate->OpenDocumentFile(NULL));
		doc->SelectedNode(args);
	}
}

