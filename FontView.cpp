// FontView.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FontView.h"
#include "FontViewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Doesn't work when put in .h :-/
HRESULT (__stdcall *g_pfnSHGetFolderPath)( HWND, int, HANDLE, DWORD, LPTSTR );

/////////////////////////////////////////////////////////////////////////////
// CFontViewApp

BEGIN_MESSAGE_MAP(CFontViewApp, CWinApp)
	//{{AFX_MSG_MAP(CFontViewApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontViewApp construction

CFontViewApp::CFontViewApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFontViewApp object

CFontViewApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFontViewApp initialization

BOOL CFontViewApp::InitInstance()
{
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Create and prepare dialog box
	CFontViewDlg dlg;
	CString HtmlStr, HtmlStrFormat;
	m_pMainWnd = &dlg;
	dlg.m_bSymbol = true;
	dlg.m_bNonEnglish = false;
	dlg.m_bRaster = false;
	TCHAR lpszFilePath[MAX_PATH];
	int fontCount = 0;
	char last = '\0';

	// Bepaal de folder waar het HTML-bestand moet worden geschreven

	// SHGetSpecialFolderPath() only works when "Integrated Desktop" is installed
	// SHGetSpecialFolderPath( NULL, lpszFilePath, CSIDL_PERSONAL, true );

	// We have to dynamically load shfolder.dll
	HMODULE hModSHFolder = LoadLibrary("shfolder.dll");

	if ( hModSHFolder != NULL ) {
		(*(FARPROC*)&g_pfnSHGetFolderPath = GetProcAddress(hModSHFolder, "SHGetFolderPathA"));
		// To force creating folder, use: CSIDL_PERSONAL|CSIDL_FLAG_CREATE
		g_pfnSHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, NULL, lpszFilePath);
	} else
		lpszFilePath[0] = '\0';
	
	dlg.m_path = lpszFilePath;
	dlg.m_path += "\\" FILEOUTNAME;

	// Lees de sample text uit Sample.txt, als deze bestaat

	TRY {
		TCHAR lpszSampleText[SAMPLETEXTMAXLEN+2];
		lpszSampleText[0] = '\0';
		CStdioFile sampleFile( SAMPLETEXTFILENAME, CFile::modeRead );
		int nSampleTextOffset = 0;
		while ( nSampleTextOffset < SAMPLETEXTMAXLEN && sampleFile.ReadString( lpszSampleText+nSampleTextOffset, SAMPLETEXTMAXLEN-nSampleTextOffset ) ) {
			nSampleTextOffset = strlen( lpszSampleText );
			if ( lpszSampleText[nSampleTextOffset-1] == '\n' ) {
				lpszSampleText[nSampleTextOffset-1] = '\r';
				lpszSampleText[nSampleTextOffset] = '\n';
			}
			lpszSampleText[++nSampleTextOffset] = '\0';
		}
		dlg.m_exampletext = lpszSampleText;
	}
	CATCH( CFileException, e ) {
		dlg.m_exampletext.LoadString( IDS_SAMPLE );
	}
	END_CATCH

	// Verwerk de dialoogbox

	if ( dlg.DoModal() == IDOK )
	{
		int i;
		FontArray fontArray;
		CClientDC dc( m_pMainWnd );

		// Enumerate fonts with callback function EnumFontProc
		::EnumFontFamilies( (HDC) dc, NULL, (FONTENUMPROC) EnumFontProc, (LPARAM) &fontArray );
		int aantal = fontArray.GetSize();

		// Open file
		CStdioFile out( dlg.m_path, CFile::modeWrite | CFile::modeCreate );

		// Get FontList program path
		//char szPath[1024];
		//GetModuleFileName(AfxGetApp()->m_hInstance, szPath, sizeof(szPath));

		// Write header
		HRSRC hResInfo = FindResource( NULL, MAKEINTRESOURCE(HTMLHEADHTML), RT_HTML );
		HtmlStrFormat = (LPSTR) LoadResource( NULL, hResInfo );
		HtmlStr.Format( HtmlStrFormat, aantal );
		out.WriteString( HtmlStr );

		// Create list of pointers
		FONTINF** fontPtrs = new FONTINF*[aantal];
		for ( i = 0; i < aantal; i++ ) {
			fontPtrs[i] = &fontArray[i];
		}

		// Sort fonts alphabetically
	    qsort( (void *)fontPtrs, (size_t)aantal, sizeof( FONTINF* ), compare );

		// Write all fonts
		for ( i = 0; i < aantal; i++ ) {
			int tmCharSet = fontPtrs[i]->fontinfo.tmCharSet;
			// opt. exclude non-English fonts
			if ( (dlg.m_bNonEnglish || ( tmCharSet == ANSI_CHARSET || tmCharSet == OEM_CHARSET || tmCharSet == SYMBOL_CHARSET ) ) )
				// opt. exclude symbol fonts
				if ( (dlg.m_bSymbol || tmCharSet != SYMBOL_CHARSET ) )
					// opt. exclude raster fonts
					if ( (dlg.m_bRaster || !(fontPtrs[i]->FontType & RASTER_FONTTYPE) ) ) {
						char *fontName = (char *) fontPtrs[i]->fontname.elfFullName;
						if ( fontName[0] != '\0' && fontName[0] != '@' ) {
							char c = toupper( fontName[0] );
							if ( c != last ) {
								last = c;
							} else {
								c = NULL;
							}

							out.WriteString( FontHTML( fontPtrs[i], dlg.m_exampletext, fontCount++, c ) );
						}
					}
		}

		delete fontPtrs;

		// Write footer
		hResInfo = FindResource( NULL, MAKEINTRESOURCE(IDR_HTMLFOOTER), RT_HTML );
		HtmlStr = (LPSTR) LoadResource( NULL, hResInfo );
		out.WriteString( HtmlStr );
		out.Close();

		// Find default browser
		unsigned long buflen = BUFLENGTH;
		char buf[BUFLENGTH];
		char defaultBrowser[BUFLENGTH];

		strcpy(defaultBrowser, "iexplore.exe");
		HKEY hkey;
		long ret = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Clients\\StartMenuInternet", 0, KEY_READ, &hkey);
		if (ret == ERROR_SUCCESS) {
			ret = RegQueryValueEx(hkey,
		             "",
		             NULL,
		             NULL,
		             (unsigned char *) buf,
		             &buflen);
			RegCloseKey(hkey);
			if (ret == ERROR_SUCCESS)
				strcpy(defaultBrowser, buf);
		}

		// Open browser
		ShellExecute(NULL, "open", defaultBrowser, "\""+dlg.m_path+"\"", NULL, SW_SHOWNORMAL);
	}
	return FALSE;
}

// Callback function for EnumFontFamilies()
int CALLBACK CFontViewApp::EnumFontProc( ENUMLOGFONT *lpelf, NEWTEXTMETRIC *lpntm, int nFontType, LPARAM lParam ) {
	FontArray *pFontArray = (FontArray*) lParam;
	FONTINF fontinfo;
	fontinfo.FontType = nFontType;
	fontinfo.fontinfo = *lpntm;
	fontinfo.fontname = *lpelf;
	pFontArray->Add( fontinfo );
	return 1;
}

// Print information about a font
CString CFontViewApp::FontHTML( FONTINF *pFontInfo, CString strExampleText, int fontCount, int c ) {
	CString fontType = "";

	if ( pFontInfo->FontType & RASTER_FONTTYPE )
		fontType += " Raster"; 

	if ( pFontInfo->fontinfo.tmItalic )
		fontType += " Italic";
	if ( pFontInfo->fontinfo.tmUnderlined )
		fontType += " Underlined";
	if ( pFontInfo->fontinfo.tmStruckOut )
		fontType += " Struck out";

	switch ( pFontInfo->fontinfo.tmWeight ) {
		case 100:
			fontType += " Thin";
			break;
		case 200:
			fontType += " Ultralight";
			break;
		case 300:
			fontType += " Light";
			break;
		//case 400:
		//	fontType += " Normal";
		//	break;
		case 500:
			fontType += " Medium";
			break;
		case 600:
			fontType += " Demibold";
			break;
		case 700:
			fontType += " Bold";
			break;
		case 800:
			fontType += " Ultrabold";
			break;
		case 900:
			fontType += " Black";
			break;
	}

	switch ( pFontInfo->fontinfo.tmCharSet ) {
		case ANSI_CHARSET:
			fontType += " ANSI";
			break;
		case BALTIC_CHARSET:
			fontType += " Baltic";
			break;
		case CHINESEBIG5_CHARSET:
			fontType += " Chinese BIG5";
			break;
		case DEFAULT_CHARSET:
			fontType += " Default";
			break;
		case EASTEUROPE_CHARSET:
			fontType += " Eastern Europe";
			break;
		case GB2312_CHARSET:
			fontType += " GB 2312";
			break;
		case GREEK_CHARSET:
			fontType += " Greek";
			break;
		case HANGUL_CHARSET:
			fontType += " Hangul";
			break;
		case MAC_CHARSET:
			fontType += " Mac";
			break;
		case OEM_CHARSET:
			fontType += " OEM";
			break;
		case RUSSIAN_CHARSET:
			fontType += " Russian";
			break;
		case SHIFTJIS_CHARSET:
			fontType += " Shift-JIS";
			break;
		case SYMBOL_CHARSET:
			fontType += " Symbol";
			break;
		case TURKISH_CHARSET:
			fontType += " Turkish";
			break;
		case JOHAB_CHARSET:
			fontType += " Johab";
			break;
		case HEBREW_CHARSET:
			fontType += " Hebrew";
			break;
		case ARABIC_CHARSET:
			fontType += " Arabic";
			break;
		case THAI_CHARSET:
			fontType += " Thai";
			break;
	}

	HRSRC hResInfo = FindResource( NULL, MAKEINTRESOURCE(IDR_HTMLFONT), RT_HTML );
	CString fontHTML = (LPSTR) LoadResource( NULL, hResInfo );

	CString fontNameEscaped;
	fontNameEscaped = escape( pFontInfo->fontname.elfFullName );
	CString id;
	if ( c && c != '"' )
		id.Format( " id=\"char%c\"", c );
	else
		id = "";
	CString outText;
	outText.Format( fontHTML,
		id,
		fontCount,
		fontCount,
		fontCount,
		fontCount,
		(LPCTSTR) pFontInfo->fontname.elfFullName,
		fontType,
		fontCount,
		fontNameEscaped,
		strExampleText
	);

	return outText;
}

// Compare function for qsort
int compare( const void *arg1, const void *arg2 )
{
	/* Compare all of both strings: */
	LPCTSTR name1 = (LPCTSTR) (*( FONTINF** ) arg1)->fontname.elfFullName;
	LPCTSTR name2 = (LPCTSTR) (*( FONTINF** ) arg2)->fontname.elfFullName;
	
	return _stricmp( name1, name2 );
}

CString CFontViewApp::escape(CString fontName)
{
	fontName.Replace( "'", "\\'" );
	fontName.Replace( "\"", "&quot;" );
	return fontName;

}
