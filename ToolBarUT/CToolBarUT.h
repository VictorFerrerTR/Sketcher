#pragma once
#include <afxext.h>
#include<vector>
#include<memory>

/***
* This class implements a ToolBar that fits the UT requirements, where the distribution is:
*
* [Prev] [All toolbar original buttons] [Dynamic Space, ESgi, Clt-1, Clt-2, Home, Next]
*
* Where SP means Space between buttons.
*
* The buttons Prev and Next are there to show/hide the Toolbar button in case the width of 
* the windows is lesser than the active space of the toolbar.
*
*/

class CMFCButton;
class CButton;
class CComboBox;

class CToolBarUT : public CToolBar
{
    struct UT_TB_BUTTON
    {
        int nIndex{ -1 };
        int DefWidth{ 0 };              // To calcuate the minimal space required and Max size of the button
        int CurWidth{ 0 };
        int MinWidth{ 0 };               // Minimum SIze of the Button in case that it should be resized
        UCHAR StyleEx{ 'B' };           // B = Standar Button; S = Standar Separator; U = UT Button; W = Dynamic Separator
        BOOL bOnActiveSpace{ false };
        BOOL bVisible{ false };
        UINT nID{ 0 };
        UINT Style{ 0 };
        INT ilImage{0};
        std::unique_ptr<CButton> button{};
    };
    
    struct UT_ToolBar
    {
        bool bChevronL{ false };
        bool bChevronR{ false };
        int avlb_width{ -1 };       // The available spacet that the TB has to show it's buttons
        int tb_min_space{ -1 };     // The minimal space that TB needs to have without spaces, Previous and Next Button.
        int tb_optimal_space{ -1 }; // The minimal space that TB needs to have with but without Dynamic Spaces, Previous and Next Button.
        int tb_width{-1};           // The Current width of the toolbar.
        int lftOffset{ -1 };
        int rgtOffset{ -1 };
        std::vector<UT_TB_BUTTON> m_buttons{0};
        int idWideSpace{ -1 };
    };
    UT_ToolBar m_ut_TBLyt{};

    HWND m_hTool;
 
    void initTBLayout();
    void GetCurrentLayoutStatus(); // Calculate the Current Space and the Visible elements of the TB
    void calcOptimalDistribution();
    void calcMinimalDistribution();
    void calcShrinkDistribution();
    
    void setButtonOnTB(UT_TB_BUTTON & tbBtn);

    BOOL CreateSeparator(UINT nIndex, UINT nID, int nWidth);
    BOOL CreateButton(class CButton& button, UINT nIndex, UINT nID, int nWidth, UINT idBMP);

public:
    

    BOOL CreateToolBar(CWnd* pParentWnd, ULONG ID_MEN);

    void OnPrevious();
    void OnNext();
    void OnHome();

    void OnPaint();

};

