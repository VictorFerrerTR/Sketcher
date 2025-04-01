
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

    // Creation of the toolbar
    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_TOOLTIPS | CBRS_FLYBY) ||
        !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    // Creation of homepage button
    if (!m_HomePageBtn.Create(_T(""), WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, CRect(10, 10, 34, 30), this, IDC_OPEN_HOMEPAGE))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    // Load the bitmap for homepage button
    HBITMAP hBitmap = (HBITMAP)::LoadImage(
        AfxGetInstanceHandle(),
        MAKEINTRESOURCE(IDB_BITMAP2), // Replace with your bitmap resource ID
        IMAGE_BITMAP,
        0, 0,
        LR_CREATEDIBSECTION | LR_DEFAULTCOLOR // Ensure it's device-independent
    );

    // Attach the bitmap to the homepage button
    if (hBitmap != nullptr)
    {
        m_HomePageBtn.SetImage(hBitmap, TRUE, hBitmap, TRUE, hBitmap);
        //m_HomePageBtn.SizeToContent();
        m_HomePageBtn.Invalidate();
    }
    else
    {
        AfxMessageBox(_T("Failed to load bitmap resource!"));
    }

    // Create Fake client button
    if (!m_clientButton.Create(_T("Client 1"), WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, CRect(10, 10, 104, 30), this, IDC_OPEN_CLIENT1))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    // Create fake client button
    if (!m_clientButton2.Create(_T("Client 2"), WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, CRect(10, 10, 104, 30), this, IDC_OPEN_CLIENT1))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    // Add all the bars
    if (!m_wndReBar.Create(this, CBRS_HIDE_INPLACE, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP, AFX_IDW_REBAR))
        return false;

    m_wndReBar.AddBar(&m_wndToolBar, nullptr, nullptr, RBBS_GRIPPERALWAYS | RBBS_USECHEVRON );
    m_wndReBar.AddBar(&m_clientButton, nullptr, nullptr, RBBS_NOGRIPPER);
    m_wndReBar.AddBar(&m_clientButton2, nullptr, nullptr, RBBS_NOGRIPPER);
    m_wndReBar.AddBar(&m_HomePageBtn, nullptr, nullptr, RBBS_NOGRIPPER | RBBS_FIXEDSIZE);

    CReBarCtrl& reBarCtrl = m_wndReBar.GetReBarCtrl();
    int bandIndex2 = 1;
    REBARBANDINFO bandInfo;
    ZeroMemory(&bandInfo, sizeof(REBARBANDINFO));
    bandInfo.cbSize = sizeof(REBARBANDINFO);
    bandInfo.fMask = RBBIM_SIZE | RBBIM_IDEALSIZE | RBBIM_CHILD | RBBIM_CHILDSIZE ;
    bool result = reBarCtrl.GetBandInfo(bandIndex2, &bandInfo);

    if (!m_wndStatusBar.Create(this))
    {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }
    m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));


    //To fill the spaces betwen bands without gripper
    SetWindowTheme(m_wndReBar.GetSafeHwnd(), L" ", L" ");

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

