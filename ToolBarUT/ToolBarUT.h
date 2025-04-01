
// ToolBarUT.h : main header file for the ToolBarUT application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CToolBarUTApp:
// See ToolBarUT.cpp for the implementation of this class
//

class CToolBarUTApp : public CWinApp
{
public:
	CToolBarUTApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CToolBarUTApp theApp;
