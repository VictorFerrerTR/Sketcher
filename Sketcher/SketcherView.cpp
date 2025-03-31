
// SketcherView.cpp : implementation of the CSketcherView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#endif

#include "SketcherDoc.h"
#include "SketcherView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketcherView

IMPLEMENT_DYNCREATE(CSketcherView, CView)

BEGIN_MESSAGE_MAP(CSketcherView, CView)
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
    ON_WM_CREATE()
END_MESSAGE_MAP()

// CSketcherView construction/destruction

CSketcherView::CSketcherView() noexcept
{
    // TODO: add construction code here

}

CSketcherView::~CSketcherView()
{
}

BOOL CSketcherView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

// CSketcherView drawing

int CSketcherView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    //m_simpleButton.Create(_T(""), WS_CHILD | WS_VISIBLE | BS_BITMAP/*BS_PUSHBUTTON*/, CRect(300, 100, 400, 150), this, IDC_BUTTON1);

    //// Load the bitmap
    //HBITMAP hBitmap = (HBITMAP)::LoadImage(
    //    AfxGetInstanceHandle(),
    //    MAKEINTRESOURCE(IDB_BITMAP2), // Replace with your bitmap resource ID
    //    IMAGE_BITMAP,
    //    0, 0,
    //    LR_CREATEDIBSECTION | LR_DEFAULTCOLOR // Ensure it's device-independent
    //);

    //// Attach the bitmap to the CMFCButton
    //if (hBitmap != nullptr)
    //{
    //    m_simpleButton.SetImage(hBitmap, TRUE, hBitmap, TRUE,hBitmap);
    //    m_simpleButton.SizeToContent();
    //    m_simpleButton.Invalidate();
    //}
    //else
    //{
    //    AfxMessageBox(_T("Failed to load bitmap resource!"));
    //}

    //HICON hBitmap = (HICON)::LoadImage(
    //    AfxGetInstanceHandle(),
    //    MAKEINTRESOURCE(IDR_MAINFRAME), // Icon resource ID
    //    IMAGE_ICON,
    //    32, 32, // Desired size of the icon
    //    LR_DEFAULTCOLOR
    //);

    //if (hBitmap != nullptr)
    //{
    //    //m_simpleButton.ModifyStyle(0, BS_BITMAP);
    //    m_simpleButton.SetImage(hBitmap); // TRUE indicates Auto Destroy for cleanup
    //    m_simpleButton.SizeToContent(); // Adjust button size to match the bitmap dimensions
    //    m_simpleButton.Invalidate();
    //}
    //else
    //{
    //    AfxMessageBox(_T("Failed to load bitmap!"));
    //}

    return 0;
}

void CSketcherView::OnDraw(CDC* /*pDC*/)
{
    CSketcherDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: add draw code for native data here
}


// CSketcherView printing

BOOL CSketcherView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CSketcherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CSketcherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

void CSketcherView::DoDataExchange(CDataExchange* pDX)
{
    CView::DoDataExchange(pDX);

    // Bind the button control to the variable
    DDX_Control(pDX, IDC_BUTTON1, m_simpleButton);
}


// CSketcherView diagnostics

#ifdef _DEBUG
void CSketcherView::AssertValid() const
{
    CView::AssertValid();
}

void CSketcherView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CSketcherDoc* CSketcherView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketcherDoc)));
    return (CSketcherDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketcherView message handlers
