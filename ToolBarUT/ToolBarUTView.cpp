
// ToolBarUTView.cpp : implementation of the CToolBarUTView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ToolBarUT.h"
#endif

#include "ToolBarUTDoc.h"
#include "ToolBarUTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolBarUTView

IMPLEMENT_DYNCREATE(CToolBarUTView, CView)

BEGIN_MESSAGE_MAP(CToolBarUTView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CToolBarUTView construction/destruction

CToolBarUTView::CToolBarUTView() noexcept
{
	// TODO: add construction code here

}

CToolBarUTView::~CToolBarUTView()
{
}

BOOL CToolBarUTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CToolBarUTView drawing

void CToolBarUTView::OnDraw(CDC* /*pDC*/)
{
	CToolBarUTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CToolBarUTView printing

BOOL CToolBarUTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CToolBarUTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CToolBarUTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CToolBarUTView diagnostics

#ifdef _DEBUG
void CToolBarUTView::AssertValid() const
{
	CView::AssertValid();
}

void CToolBarUTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolBarUTDoc* CToolBarUTView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolBarUTDoc)));
	return (CToolBarUTDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolBarUTView message handlers
