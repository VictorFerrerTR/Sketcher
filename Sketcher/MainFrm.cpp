
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "Sketcher.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
    ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
    // TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

    if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    //if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
    //	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
    //{
    //	TRACE0("Failed to create toolbar\n");
    //	return -1;      // fail to create
    //}

    //if (!m_geometryToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
    //	!m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
    //{
    //	TRACE0("Failed to create toolbar\n");
    //	return -1;      // fail to create
    //}

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_FLYBY) ||
        !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    if (!m_HomePageBtn.Create(_T(""), WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, CRect(10, 10, 34, 34), this, IDC_OPEN_HOMEPAGE))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    // Load the bitmap
    HBITMAP hBitmap = (HBITMAP)::LoadImage(
        AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDB_BITMAP2), // Replace with your bitmap resource ID
        IMAGE_BITMAP,
        0, 0,
        LR_CREATEDIBSECTION | LR_DEFAULTCOLOR // Ensure it's device-independent
    );

    // Attach the bitmap to the CMFCButton
    if (hBitmap != nullptr)
    {
        m_HomePageBtn.SetImage(hBitmap, TRUE, hBitmap, TRUE, hBitmap);
        m_HomePageBtn.SizeToContent();
        m_HomePageBtn.Invalidate();
    }
    else
    {
        AfxMessageBox(_T("Failed to load bitmap resource!"));
    }

    if (!m_clientButton.Create(_T("Client 1"), WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, CRect(10, 10, 104, 34), this, IDC_OPEN_CLIENT1))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    //if (!m_wndGeomToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_FLYBY) ||
    //	!m_wndGeomToolBar.LoadToolBar(IDR_TOOLBAR1))
    //{
    //	TRACE0("Failed to create toolbar\n");
    //	return -1;      // fail to create
    //}

    //if (!m_wndColorToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_FLYBY) ||
    //	!m_wndColorToolBar.LoadToolBar(IDR_TOOLBAR2))
    //{
    //	TRACE0("Failed to create toolbar\n");
    //	return -1;      // fail to create
    //}



    // Add all the bars
    if (!m_wndReBar.Create(this, CBRS_HIDE_INPLACE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP, AFX_IDW_REBAR))
        return false;

    m_wndReBar.AddBar(&m_wndToolBar, nullptr, nullptr, RBBS_GRIPPERALWAYS | RBBS_USECHEVRON );
    m_wndReBar.AddBar(&m_clientButton, nullptr, nullptr, RBBS_NOGRIPPER | RBBS_HIDDEN);
    m_wndReBar.AddBar(&m_HomePageBtn, nullptr, nullptr, RBBS_NOGRIPPER);
    //m_wndReBar.AddBar(&m_wndColorToolBar, nullptr, nullptr, RBBS_GRIPPERALWAYS);
    //RecalcLayout();

    //DockControlBar(&m_wndToolBar);
    //m_wndToolBar.EnableDocking(0);
    //m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

    CReBarCtrl& reBarCtrl = m_wndReBar.GetReBarCtrl();
    int bandIndex2 = 1;
    REBARBANDINFO bandInfo;
    ZeroMemory(&bandInfo, sizeof(REBARBANDINFO));
    bandInfo.cbSize = sizeof(REBARBANDINFO);
    bandInfo.fMask = RBBIM_SIZE | RBBIM_IDEALSIZE | RBBIM_CHILD | RBBIM_CHILDSIZE ;
    bool result = reBarCtrl.GetBandInfo(bandIndex2, &bandInfo);
    //bandInfo.cxIdeal = 0;
    //bandInfo.cxMinChild = m_wndGeomToolBar.CalcFixedLayout(false, m_wndGeomToolBar.m_dwStyle & CBRS_ORIENT_HORZ).cx;
    //result = (BOOL)::DefWindowProc(m_wndReBar.m_hWnd, RB_SETBANDINFO, bandIndex2, (LPARAM)&bandInfo);//reBarCtrl.SetBandInfo(bandIndex2, &bandInfo);
    //result = reBarCtrl.GetBandInfo(bandIndex2, &bandInfo);

    if (!m_wndStatusBar.Create(this))
    {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }
    m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));


    //To fill the spaces betwen bands without gripper
    SetWindowTheme(m_wndReBar.GetSafeHwnd(), L" ", L" ");

    //int bandIndex1 = m_wndReBar.GetReBarCtrl().IDToIndex(m_wndToolBar.GetDlgCtrlID());
    //int bandIndex2 = m_wndReBar.GetReBarCtrl().IDToIndex(m_wndGeomToolBar.GetDlgCtrlID());

    //auto bandCount = m_wndReBar.GetReBarCtrl().GetBandCount();
    //m_wndReBar.GetReBarCtrl().MaximizeBand(0);

    //// TODO: Delete these three lines if you don't want the toolbar to be dockable
    //m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    //EnableDocking(CBRS_ALIGN_ANY);
    //DockControlBar(&m_wndToolBar);


    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CMDIFrameWnd::PreCreateWindow(cs))
        return FALSE;
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

