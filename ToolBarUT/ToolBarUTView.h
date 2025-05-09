
// ToolBarUTView.h : interface of the CToolBarUTView class
//

#pragma once


class CToolBarUTView : public CView
{
protected: // create from serialization only
	CToolBarUTView() noexcept;
	DECLARE_DYNCREATE(CToolBarUTView)

// Attributes
public:
	CToolBarUTDoc* GetDocument() const;

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
	virtual ~CToolBarUTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ToolBarUTView.cpp
inline CToolBarUTDoc* CToolBarUTView::GetDocument() const
   { return reinterpret_cast<CToolBarUTDoc*>(m_pDocument); }
#endif

