
// SketcherDoc.h : interface of the CSketcherDoc class
//


#pragma once
#include "ElementType.h"
#include "ElementColor.h"

class CSketcherDoc : public CDocument
{
protected: // create from serialization only
    CSketcherDoc() noexcept;
    DECLARE_DYNCREATE(CSketcherDoc)

    // Attributes
public:

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
    virtual ~CSketcherDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    ElementType GetElementType() const { return m_Element; }
    ElementColor GetElementColor() const { return m_Color; }

protected:

    // Generated message map functions
protected:
    DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
    // Helper function that sets search content for a Search Handler
    void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
    afx_msg void OnColorBlack();
    afx_msg void OnColorRed();
    afx_msg void OnColorGreen();
    afx_msg void OnColorBlue();
    afx_msg void OnElementLine();
    afx_msg void OnElementRectangle();
    afx_msg void OnElementCircle();
    afx_msg void OnElementCurve();
    afx_msg void OnUpdateColorBlack(CCmdUI* pCmdUI);
    afx_msg void OnUpdateColorRed(CCmdUI* pCmdUI);
    afx_msg void OnUpdateColorGreen(CCmdUI* pCmdUI);
    afx_msg void OnUpdateColorBlue(CCmdUI* pCmdUI);
    afx_msg void OnUpdateElementLine(CCmdUI* pCmdUI);
    afx_msg void OnUpdateElementRectangle(CCmdUI* pCmdUI);
    afx_msg void OnUpdateElementCircle(CCmdUI* pCmdUI);
    afx_msg void OnUpdateElementCurve(CCmdUI* pCmdUI);
protected:
    ElementType m_Element{ ElementType::LINE };         // Current element type
    ElementColor m_Color{ ElementColor::BLACK };        // Current drawing color
};
