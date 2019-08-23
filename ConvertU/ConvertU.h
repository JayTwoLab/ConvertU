
// ConvertU.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CConvertUApp:
// See ConvertU.cpp for the implementation of this class
//

class CConvertUApp : public CWinApp
{
public:
	CConvertUApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

	void GenVersion();
	CString m_strVersion;

};

extern CConvertUApp theApp;
