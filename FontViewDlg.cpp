// FontViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FontView.h"
#include "FontViewDlg.h"
#include "StaticLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStaticLink m_url;
	CStaticLink m_email;
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BOOL CAboutDlg::OnInitDialog() 
{
	m_url.SubclassDlgItem(IDC_URL, this);
	m_email.SubclassDlgItem(IDC_EMAIL, this);
	m_email.m_link = _T("mailto:edwin@bitstorm.org");

	return CDialog::OnInitDialog();;
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontViewDlg dialog

CFontViewDlg::CFontViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFontViewDlg)
	m_exampletext = _T("");
	m_bNonEnglish = FALSE;
	m_bSymbol = FALSE;
	m_bRaster = FALSE;
	m_path = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontViewDlg)
	DDX_Control(pDX, IDOK, m_Ok);
	DDX_Text(pDX, IDC_SAMPLE, m_exampletext);
	DDX_Check(pDX, IDC_NONENGLISH, m_bNonEnglish);
	DDX_Check(pDX, IDC_SYMBOL, m_bSymbol);
	DDX_Check(pDX, IDC_RASTER, m_bRaster);
	DDX_Text(pDX, IDC_PATH, m_path);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFontViewDlg, CDialog)
	//{{AFX_MSG_MAP(CFontViewDlg)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_SELECTFILE, OnSelectfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontViewDlg message handlers

BOOL CFontViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

void CFontViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CFontViewDlg::OnSelectfile()
{
	TCHAR lpszFilePath[MAX_PATH];
	GetDlgItemText( IDC_PATH, lpszFilePath, MAX_PATH );
	CFileDialog fileDlg( FALSE, _T("html"), lpszFilePath, OFN_HIDEREADONLY, _T("HTML files (*.html)|*.htm;*.html|All files (*.*)|*.*||") );
	if ( fileDlg.DoModal() == IDOK ) {
		SetDlgItemText( IDC_PATH, fileDlg.GetPathName() );
		m_Ok.SetFocus();
	}
}

