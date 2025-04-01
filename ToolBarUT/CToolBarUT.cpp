#include "pch.h"
#include "CToolBarUT.h"
#include "resource.h"

#include <afx.h>

void CToolBarUT::initTBLayout()
{
    auto& ctb = GetToolBarCtrl();
    int iCount = ctb.GetButtonCount();

    if (iCount != m_ut_TBLyt.m_buttons.size())
        m_ut_TBLyt.m_buttons.resize(iCount);

    m_ut_TBLyt.tb_width = 0;
    for (int i{ 0 }; i < iCount; i++)
    {
        CRect rec;
        bool bIncMin{ true };
        bool bIncOpt{ true };
        UT_TB_BUTTON& btn = m_ut_TBLyt.m_buttons[i];
        
        btn.nIndex = i;
        GetItemRect(i, rec);
        btn.bVisible = true;
        btn.bVisible = true;
        
        GetButtonInfo(i, btn.nID, btn.Style, btn.ilImage);
        btn.DefWidth = rec.Width();
        btn.MinWidth = rec.Width();

        if (btn.nID == WM_TB_CMD_PREV || btn.nID == WM_TB_CMD_NEXT) // Previous or Next
        {
            btn.CurWidth = 0;   // These buttons are not visible at the begin
            btn.bVisible = false;
            btn.DefWidth = 8;
            btn.MinWidth = btn.DefWidth;
            btn.ilImage = btn.nID == WM_TB_CMD_PREV ? IDB_PREV : IDB_NEXT;
            m_ut_TBLyt.lftOffset = btn.nID == WM_TB_CMD_PREV ? i : m_ut_TBLyt.lftOffset;
            m_ut_TBLyt.rgtOffset = btn.nID == WM_TB_CMD_NEXT ? i : m_ut_TBLyt.rgtOffset;
            bIncMin = false;
            bIncOpt = false;
            btn.StyleEx = 'U';
        }
        else if (btn.nID == WM_TB_CMD_ESIG || btn.nID == WM_TB_CMD_CLT1 || btn.nID == WM_TB_CMD_CLT2)   // The button is a UltraTax Custom Button
        {
            btn.DefWidth = 100;
            btn.MinWidth = 65;
            btn.ilImage = IDB_BTN;
            btn.StyleEx = 'U';
        }
        else if (btn.nID == WM_TB_CMD_HOME) // The button is a UltraTax Home Button
        {
            btn.DefWidth = 24;
            btn.MinWidth = btn.DefWidth;
            btn.ilImage = IDB_BTN;
            btn.StyleEx = 'U';
        }
        else if (btn.nID == WM_TB_SP_3) // The Slot is a Dynamic Separator
        {
            btn.DefWidth = 6;
            btn.MinWidth = 1;
            m_ut_TBLyt.idWideSpace = i;
            bIncMin = false;
            bIncOpt = false;
            btn.StyleEx = 'W';
        }
        else
        {
            if (btn.Style == 0) // Button
                btn.StyleEx = 'B';
            else                // Space
            {
                btn.StyleEx = 'S';
                btn.MinWidth = 1;
                bIncMin = false;
            };
        }

        btn.CurWidth = btn.DefWidth;

        if (btn.bVisible)    m_ut_TBLyt.tb_width += btn.CurWidth;
        if (bIncMin)         m_ut_TBLyt.tb_min_space += btn.MinWidth;       
        if (bIncOpt)         m_ut_TBLyt.tb_optimal_space += btn.DefWidth;

    }


}

void CToolBarUT::GetCurrentLayoutStatus()
{
    CRect tbRect;
    int hP, vP;
    auto& ctb = GetToolBarCtrl();

    ctb.GetPadding(hP, vP);
    GetWindowRect(&tbRect); // Get the Current ToolBar size in the WinForm

    m_ut_TBLyt.avlb_width = tbRect.Width() - (hP*2);

    // For Optimal case, Resize the Dynamic Space
    if (m_ut_TBLyt.avlb_width > m_ut_TBLyt.tb_optimal_space)
        calcOptimalDistribution();
    // For Minimal case, Show the Remove all the spaces and Chevron Buttons and all the spaces, just use the Dynamic Space to adjust
    else if (m_ut_TBLyt.avlb_width > m_ut_TBLyt.tb_min_space)
        calcMinimalDistribution();
    // For Shrink case, Show the Chevron Buttons
    else
        calcShrinkDistribution();
}

/** 
* In an Optimal Distribution, there is no necessity of Chevron Buttons and
* the distribution depends of the Dynamical Space.
*/
void CToolBarUT::calcOptimalDistribution()
{
    int idDS{ -1 };
    m_ut_TBLyt.tb_width = { 0 }; 
    m_ut_TBLyt.lftOffset = -1;
    m_ut_TBLyt.rgtOffset = -1;

    for (int i{ 0 }; i < m_ut_TBLyt.m_buttons.size(); i++)
    {
        UT_TB_BUTTON& tbBtn = m_ut_TBLyt.m_buttons[i];

        tbBtn.bVisible = true;

        if (tbBtn.nID == WM_TB_CMD_PREV || tbBtn.nID == WM_TB_CMD_NEXT)
            tbBtn.bVisible = false;
        else if (tbBtn.StyleEx == 'W') // The 
            idDS = i;
        else
            m_ut_TBLyt.tb_width += tbBtn.DefWidth;
        tbBtn.CurWidth = tbBtn.DefWidth;
    }

    if (idDS != -1)
    {
        int wDS = m_ut_TBLyt.avlb_width - m_ut_TBLyt.tb_width;
        m_ut_TBLyt.m_buttons[idDS].CurWidth = wDS;
        m_ut_TBLyt.tb_width += wDS;
    }
    
}

/**
* In an Optimal Distribution, there is no necessity of Chevron Buttons and
* all of the Standard Spaces are removed to take advantage of the available
* space and the minimal available space is set on the Dynamical Space.
*/
void CToolBarUT::calcMinimalDistribution()
{
    int idDS{ -1 };
    m_ut_TBLyt.tb_width = 0;
    m_ut_TBLyt.lftOffset = -1;
    m_ut_TBLyt.rgtOffset = -1;

    for (int i{ 0 }; i < m_ut_TBLyt.m_buttons.size(); i++)
    {
        UT_TB_BUTTON& tbBtn = m_ut_TBLyt.m_buttons[i];

        tbBtn.bVisible = true;

        if (tbBtn.nID == WM_TB_CMD_PREV || tbBtn.nID == WM_TB_CMD_NEXT || tbBtn.StyleEx == 'S')
            tbBtn.bVisible = false;
        else if (tbBtn.StyleEx == 'W') // The Dynamic Separator
            idDS = i;
        else
            m_ut_TBLyt.tb_width += tbBtn.MinWidth;
        tbBtn.CurWidth = tbBtn.MinWidth;
    }

    if (idDS != -1)
    {
        int wDS = m_ut_TBLyt.avlb_width - m_ut_TBLyt.tb_width;
        wDS = wDS <= m_ut_TBLyt.m_buttons[idDS].CurWidth ? m_ut_TBLyt.m_buttons[idDS].MinWidth : wDS;

        m_ut_TBLyt.m_buttons[idDS].CurWidth = wDS;
        m_ut_TBLyt.tb_width += wDS;
        m_ut_TBLyt.m_buttons[idDS].bVisible = wDS > 1;
    }
}

/**
* No Spaces and it depends of the Chevron Buttons to show the available buttons.
* It will use the MinSize for all the Custom Buttons and keeps the original size
* for standard buttons.
*/
void CToolBarUT::calcShrinkDistribution()
{
    int idDS{ -1 };
    int restantW{ m_ut_TBLyt.avlb_width };
    int nSize = m_ut_TBLyt.m_buttons.size();
    m_ut_TBLyt.tb_width = 0;

    auto fnProccChevron = [&restantW](UT_TB_BUTTON& btn, UINT l_nID, int &tbWidth)-> void
        {
            if (btn.nID == l_nID)
            {
                restantW -= btn.MinWidth;
                tbWidth += btn.MinWidth;
                btn.bVisible = true;
            }
        };

    // Rest the BAR and it's elements
    for (int i{ 0 }; i < m_ut_TBLyt.m_buttons.size(); i++)
    {
        m_ut_TBLyt.m_buttons[i].bVisible = false;
        m_ut_TBLyt.m_buttons[i].CurWidth = m_ut_TBLyt.m_buttons[i].MinWidth;
        if (m_ut_TBLyt.m_buttons[i].StyleEx == 'W') // The Dynamic Separator to be adjusted at the end of the routine.
            idDS = i;
    }

    auto& cvrLBtn = m_ut_TBLyt.m_buttons[0];
    auto& cvrRBtn = m_ut_TBLyt.m_buttons[nSize - 1];

    // Case 1. The Left Offset is on the first Button, so the Left Chevron is not needed but the Right do.
    if (m_ut_TBLyt.lftOffset <= 1)
    {
        m_ut_TBLyt.lftOffset = 1;
        fnProccChevron(cvrRBtn, WM_TB_CMD_NEXT, m_ut_TBLyt.tb_width);
    }
    // Case 2. The Right Offset is on the last Button, so the Right Chevron is not needed but the Right do.
    else if (m_ut_TBLyt.rgtOffset >= nSize - 1)
    {
        m_ut_TBLyt.rgtOffset = nSize - 1;
        fnProccChevron(cvrLBtn, WM_TB_CMD_PREV, m_ut_TBLyt.tb_width);
    }
    // Case 3. Both Chevrons are needed.
    else
    {
        m_ut_TBLyt.rgtOffset = m_ut_TBLyt.lftOffset;
        fnProccChevron(cvrLBtn, WM_TB_CMD_PREV, m_ut_TBLyt.tb_width);
        fnProccChevron(cvrRBtn, WM_TB_CMD_NEXT, m_ut_TBLyt.tb_width);
    }


    
    // Reset the Offsets
    m_ut_TBLyt.rgtOffset = m_ut_TBLyt.lftOffset;
    bool bKeepDoing{ true };
    // Show the buttons and update the Left and Right Offsets
    for (int i{ m_ut_TBLyt.lftOffset }; bKeepDoing && i < m_ut_TBLyt.m_buttons.size(); i++)
    {
        auto& tbBtn = m_ut_TBLyt.m_buttons[i];

        // Only the Standard Buttons or Custom Buttons are  candidate to be shown.
        // The Next and Previous Chevron Buttons MUST BE processed previously  this FOR.
        if ((tbBtn.nID != WM_TB_CMD_PREV && tbBtn.nID != WM_TB_CMD_NEXT) && (tbBtn.StyleEx == 'B' || tbBtn.StyleEx == 'U'))
        {
            // if there is room to fit the Button, Update the Right Offset, 
            // set Visible the button, and calculate the reminded space
            if (restantW >= tbBtn.MinWidth)
            {
                m_ut_TBLyt.rgtOffset = i;
                fnProccChevron(tbBtn, tbBtn.nID, m_ut_TBLyt.tb_width);
            }
            else
                bKeepDoing = false;

        }
    }

    m_ut_TBLyt.tb_width += restantW;
    if (restantW > 1) // There is a reminded space to fill with the Dynamic Separator
    {
        m_ut_TBLyt.m_buttons[idDS].CurWidth = restantW;
        m_ut_TBLyt.m_buttons[idDS].bVisible = true;
    }
}

void CToolBarUT::OnPaint()
{

    if (!GetToolBarCtrl().IsWindowVisible()) return;

    GetCurrentLayoutStatus();


    int idSp = m_ut_TBLyt.idWideSpace;

    for (int i{ 0 }; i < m_ut_TBLyt.m_buttons.size(); i++)
        setButtonOnTB(m_ut_TBLyt.m_buttons[i]);
}

void CToolBarUT::setButtonOnTB(UT_TB_BUTTON& tbBtn)
{
    CRect rect{};
    CButton* btn = tbBtn.button.get();

    UINT nID = GetItemID(tbBtn.nIndex);
    if (!tbBtn.bVisible) // Show/Hide the ToolBar Buttons and Spaces, needed by Custom Buttons and Dynamic Space
    {
        // To Hide buttons or spaces, it's necessary to change the type of sloto to 
        // TBBS_SEPARATOR and set the width to 1.
        SetButtonInfo(tbBtn.nIndex, nID, TBBS_SEPARATOR, 1);
        GetToolBarCtrl().HideButton(nID, true);
    }
    else
    {
        if (tbBtn.StyleEx == 'B')
            SetButtonInfo(tbBtn.nIndex, nID, TBBS_BUTTON, tbBtn.ilImage);
        else
            SetButtonInfo(tbBtn.nIndex, nID, TBBS_SEPARATOR, tbBtn.CurWidth);
    }

    if (btn) // Show/Hide the CButtons
    {
        if (tbBtn.bVisible)
        {
            GetItemRect(tbBtn.nIndex, &rect);
            btn->MoveWindow(rect);
            btn->ShowWindow(SW_SHOW);
        }
        else
            btn->ShowWindow(SW_HIDE);
    }
}



#pragma region Constructors

BOOL CToolBarUT::CreateToolBar(CWnd* pParentWnd, ULONG ID_MEN)
{
    const UINT ID_COMBO = 6661;

    BOOL ret{ true };
    WORD dwCtrlStyle = TBSTYLE_FLAT;
    //DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;


    if (!CToolBar::CreateEx(pParentWnd, dwCtrlStyle, dwStyle) || !LoadToolBar(ID_MEN))
    {
        TRACE("Failed to create ToolBar\n");
        ret = false;
    }

    if (ret)
    {
        initTBLayout();

        RECT wsSz{};
        CControlBarInfo cbi;

        std::unique_ptr<SIZE> mxSz(new SIZE);
        GetToolBarCtrl().GetMaxSize(mxSz.get());
        GetClientRect(&wsSz);
        GetBarInfo(&cbi);

        GetWindowRect(&wsSz);
        GetParentFrame()->GetWindowRect(&wsSz);


        for (auto& btn : m_ut_TBLyt.m_buttons)
        {
            if (btn.StyleEx == 'U')
            {
                btn.button = std::unique_ptr<CButton>(new CButton());
                ret = CreateButton(*btn.button, btn.nIndex, btn.nID, btn.CurWidth, btn.ilImage);
            }
            else if (btn.StyleEx == 'S' || btn.StyleEx == 'W')
            {
                ret = CreateSeparator(btn.nIndex, btn.nID, btn.CurWidth);
            }

            if (!ret) break;
        }
    }

    return ret;
}

BOOL CToolBarUT::CreateSeparator(UINT nIndex, UINT nID, int nWidth)
{
    CRect rect;
    auto& ctb = GetToolBarCtrl();
    int bcount = ctb.GetButtonCount();

    SetButtonInfo(nIndex, nID, TBBS_SEPARATOR, nWidth);
    GetItemRect(nIndex, &rect);
    return TRUE;
}

BOOL CToolBarUT::CreateButton(class CButton& button, UINT nIndex, UINT nID, int nWidth, UINT idBMP)
{
    CRect rect;
    auto& ctb = GetToolBarCtrl();
    int bcount = ctb.GetButtonCount();

    SetButtonInfo(nIndex, nID, TBBS_SEPARATOR, nWidth);
    GetItemRect(nIndex, &rect);

    LPCTSTR pCaption = L"";
    if (!button.Create(pCaption, WS_VISIBLE | BS_PUSHBUTTON | WS_CHILD, rect, this, nID))
    {
        TRACE("Failed to create Button\n");
        return FALSE;
    }

    nWidth = nWidth > 20 ? 20 : nWidth;
    HBITMAP m_myBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(idBMP), IMAGE_BITMAP, nWidth, rect.Height() - 2, LR_LOADMAP3DCOLORS);
    button.ModifyStyle(0, BS_BITMAP);
    button.SetBitmap(m_myBitmap);
    auto we = button.IsWindowEnabled();
    return TRUE;
}

#pragma endregion


#pragma region Button Handlers

void CToolBarUT::OnPrevious()
{
    m_ut_TBLyt.lftOffset--;
    const char stlX = m_ut_TBLyt.m_buttons[m_ut_TBLyt.lftOffset].StyleEx;
    if (stlX == 'S' || stlX == 'W')
        m_ut_TBLyt.lftOffset--;
    OnPaint();
}

void CToolBarUT::OnNext()
{
    
    m_ut_TBLyt.lftOffset++;
    const char stlX = m_ut_TBLyt.m_buttons[m_ut_TBLyt.lftOffset].StyleEx;
    if (stlX == 'S' || stlX == 'W')
        m_ut_TBLyt.lftOffset++;
    OnPaint();
}

void CToolBarUT::OnHome()
{
    static bool sbHide{ false };
    sbHide = !sbHide;

    for (int i = 0; i < 10; i++)
    {
        auto& btn = m_ut_TBLyt.m_buttons[i];
        if (sbHide)
        {
            UINT nID = GetItemID(i);
            SetButtonInfo(i, nID, TBBS_SEPARATOR, 1);
            GetToolBarCtrl().HideButton(nID, sbHide);
        }
        else
        {
            UINT nID = GetItemID(i);
            int curW = btn.CurWidth;
            if(m_ut_TBLyt.m_buttons[i].StyleEx == 'B')
                SetButtonInfo(i, nID, TBBS_BUTTON, btn.ilImage);
            else
                SetButtonInfo(i, nID, TBBS_SEPARATOR, btn.CurWidth);

            GetToolBarCtrl().HideButton(nID, sbHide);
        }
    }
    
}

#pragma endregion
