// FontView.h : main header file for the FONTVIEW application
//

#if !defined(AFX_FONTVIEW_H__8257B3FC_4433_4472_92A4_409E6CA12D50__INCLUDED_)
#define AFX_FONTVIEW_H__8257B3FC_4433_4472_92A4_409E6CA12D50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <afxtempl.h>

#define VERSION _T("1.4beta")
#define APPNAME _T("FontList " VERSION)
#define FILEOUTNAME _T("Font List.html")
#define SAMPLETEXTMAXLEN 1000
#define SAMPLETEXTFILENAME "Sample.txt"
#define BUFLENGTH 1024

typedef struct tagFONTINF {
	int FontType;
	ENUMLOGFONT fontname;
	NEWTEXTMETRIC fontinfo;
} FONTINF;

typedef CArray<FONTINF, FONTINF&> FontArray;

int compare( const void *arg1, const void *arg2 );


/////////////////////////////////////////////////////////////////////////////
// CFontViewApp:
// See FontView.cpp for the implementation of this class
//

class CFontViewApp : public CWinApp
{
public:
	CFontViewApp();
	static int CALLBACK EnumFontProc( ENUMLOGFONT *lpelf, NEWTEXTMETRIC *lpntm, int nFontType, LPARAM lParam );
	CString CFontViewApp::FontHTML( FONTINF *pFontInfo, CString strExampleText, int fontCount, int c );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFontViewApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString escape( CString fontName );
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTVIEW_H__8257B3FC_4433_4472_92A4_409E6CA12D50__INCLUDED_)
