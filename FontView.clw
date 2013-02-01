; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFontViewDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FontView.h"

ClassCount=5
Class1=CFontViewApp
Class2=CFontViewDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_FONTVIEW_DIALOG
Resource4=IDD_FONTVIEW_DIALOG (Neutral)
Class4=CStatLink
Class5=CStaticLink
Resource5=IDD_ABOUTBOX (English (U.K.))

[CLS:CFontViewApp]
Type=0
HeaderFile=FontView.h
ImplementationFile=FontView.cpp
Filter=N

[CLS:CFontViewDlg]
Type=0
HeaderFile=FontViewDlg.h
ImplementationFile=FontViewDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_SELECTFILE

[CLS:CAboutDlg]
Type=0
HeaderFile=FontViewDlg.h
ImplementationFile=FontViewDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_FONTVIEW_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CFontViewDlg

[CLS:CStatLink]
Type=0
HeaderFile=..\projects\statlink\statlink.h
ImplementationFile=..\projects\statlink\statlink.cpp
BaseClass=CDialog
Filter=D
LastObject=CStatLink

[CLS:CStaticLink]
Type=0
HeaderFile=StaticLink.h
ImplementationFile=StaticLink.cpp
BaseClass=CStatic
Filter=W

[DLG:IDD_FONTVIEW_DIALOG (Neutral)]
Type=1
Class=CFontViewDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SAMPLE,edit,1352732804
Control6=IDC_STATIC,button,1342177287
Control7=IDC_SYMBOL,button,1342242819
Control8=IDC_NONENGLISH,button,1342242819
Control9=IDC_RASTER,button,1342242819
Control10=IDC_PATH,edit,1350631552
Control11=IDC_SELECTFILE,button,1342242816
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.K.))]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_URL,static,1342308352
Control7=IDC_EMAIL,static,1342308352
Control8=IDC_STATIC,static,1342308352

