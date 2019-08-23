
// ConvertU.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "ConvertU.h"
#include "ConvertUDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConvertUApp

BEGIN_MESSAGE_MAP(CConvertUApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CConvertUApp construction

CConvertUApp::CConvertUApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CConvertUApp object

CConvertUApp theApp;


// CConvertUApp initialization

BOOL CConvertUApp::InitInstance()
{
	CWinApp::InitInstance();
	
	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("ConvertU Applications"));

	GenVersion();
	// TRACE(_T("VER : %s\n"), m_strVersion );

	CConvertUDlg dlg;
	m_pMainWnd = &dlg;
	dlg.m_strVersion = m_strVersion;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CConvertUApp::GenVersion()
{

	HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
	if (hRsrc != NULL)
	{
		HGLOBAL hGlobalMemory = LoadResource(NULL, hRsrc);
		if (hGlobalMemory != NULL)
		{
			CString rVersion;
			LPVOID pVersionResouece = LockResource(hGlobalMemory);
			LPVOID pVersion = NULL;
			DWORD uLength, langD;
			BOOL retVal;
			LPCTSTR lpSubBlock = _T("\\VarFileInfo\\Translation");

			retVal = VerQueryValue(pVersionResouece, lpSubBlock, (LPVOID*)& pVersion, (UINT*)& uLength);
			if (retVal && uLength == 4) {
				memcpy(&langD, pVersion, 4);
				//ProductVersion <-> FileVersion
				rVersion.Format(_T("\\StringFileInfo\\%02X%02X%02X%02X\\FileVersion"),
					(langD & 0xff00) >> 8, langD & 0xff, (langD & 0xff000000) >> 24,
					(langD & 0xff0000) >> 16);
			}
			else {
				//ProductVersion <-> FileVersion
				rVersion.Format(_T("\\StringFileInfo\\%04X04B0\\FileVersion"), GetUserDefaultLangID());
			}
			if (VerQueryValue(pVersionResouece, (LPCTSTR)rVersion, (LPVOID*)& pVersion, (UINT*)& uLength) != 0)
			{
				m_strVersion.Format(_T("%s"), (LPCTSTR)pVersion);
			}
		}

		FreeResource(hGlobalMemory);
	}


}



