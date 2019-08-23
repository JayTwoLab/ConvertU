
// ConvertUDlg.h : header file
//

#pragma once


// CConvertUDlg dialog
class CConvertUDlg : public CDialogEx
{
// Construction
public:
	CConvertUDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONVERTU_DIALOG };
#endif

public:
	CString m_strVersion;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditOrigin();
	afx_msg void OnEnChangeEditEncode();
	afx_msg void OnEnUpdateEditEncode();
	afx_msg void OnEnUpdateEditOrigin();
};
