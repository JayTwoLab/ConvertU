
// ConvertUDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ConvertU.h"
#include "ConvertUDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	CString m_strVersion;
	
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strTitle;
	strTitle.Format(_T("ConvertU ver.%s"), m_strVersion );
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strTitle);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CConvertUDlg dialog

CConvertUDlg::CConvertUDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONVERTU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConvertUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConvertUDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_ORIGIN, &CConvertUDlg::OnEnChangeEditOrigin)
	ON_EN_CHANGE(IDC_EDIT_ENCODE, &CConvertUDlg::OnEnChangeEditEncode)
	ON_EN_UPDATE(IDC_EDIT_ENCODE, &CConvertUDlg::OnEnUpdateEditEncode)
	ON_EN_UPDATE(IDC_EDIT_ORIGIN, &CConvertUDlg::OnEnUpdateEditOrigin)
END_MESSAGE_MAP()


// CConvertUDlg message handlers

BOOL CConvertUDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConvertUDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.m_strVersion = m_strVersion;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CConvertUDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CConvertUDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConvertUDlg::OnEnChangeEditOrigin()
{
	if (this->GetFocus() != GetDlgItem(IDC_EDIT_ORIGIN))
	{
		// TRACE(_T(" current focus is not origin edit \n"));
		return;
	}

	CString strOrigin;
	GetDlgItem(IDC_EDIT_ORIGIN)->GetWindowText(strOrigin);

	if (strOrigin.GetLength() >= MAX_URL)
	{
		strOrigin = strOrigin.GetBuffer(MAX_URL);
	}

	// encode from 'orign' to 'encode'
	CString strResult = EncodeURL(strOrigin);
	GetDlgItem(IDC_EDIT_ENCODE)->SetWindowText(strResult);
}

void CConvertUDlg::OnEnChangeEditEncode()
{
	if (this->GetFocus() != GetDlgItem(IDC_EDIT_ENCODE))
	{
		// TRACE(_T(" current focus is not origin edit \n"));
		return;
	}

	CString strEncode;
	GetDlgItem(IDC_EDIT_ENCODE)->GetWindowText(strEncode);

	if (strEncode.GetLength() >= MAX_URL)
	{
		strEncode = strEncode.GetBuffer(MAX_URL);
	}

	// decode from 'encode' to 'origin'
	CString strResult = DecodeURL(strEncode); 
	GetDlgItem(IDC_EDIT_ORIGIN)->SetWindowText(strResult);
}


void CConvertUDlg::OnEnUpdateEditEncode()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}


void CConvertUDlg::OnEnUpdateEditOrigin()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}
