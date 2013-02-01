// FontViewDlg.h : header file
//

#if !defined(AFX_FONTVIEWDLG_H__F9E2C87F_0885_48A7_81B9_A3963440761C__INCLUDED_)
#define AFX_FONTVIEWDLG_H__F9E2C87F_0885_48A7_81B9_A3963440761C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFontViewDlg dialog

class CFontViewDlg : public CDialog
{
// Construction
public:
	CFontViewDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFontViewDlg)
	enum { IDD = IDD_FONTVIEW_DIALOG };
	CButton	m_Ok;
	CString	m_exampletext;
	BOOL	m_bNonEnglish;
	BOOL	m_bSymbol;
	BOOL	m_bRaster;
	CString	m_path;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFontViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnSelectfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTVIEWDLG_H__F9E2C87F_0885_48A7_81B9_A3963440761C__INCLUDED_)
