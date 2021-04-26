; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CScriptoriumApp
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Scriptorium.h"

ClassCount=4
Class1=CScriptoriumApp
Class2=CScriptoriumDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CCustomStatic
Resource3=IDD_SCRIPTORIUM_DIALOG

[CLS:CScriptoriumApp]
Type=0
HeaderFile=Scriptorium.h
ImplementationFile=Scriptorium.cpp
Filter=N
LastObject=CScriptoriumApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CScriptoriumDlg]
Type=0
HeaderFile=ScriptoriumDlg.h
ImplementationFile=ScriptoriumDlg.cpp
Filter=D
LastObject=CScriptoriumDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ScriptoriumDlg.h
ImplementationFile=ScriptoriumDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SCRIPTORIUM_DIALOG]
Type=1
Class=CScriptoriumDlg
ControlCount=27
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC_SF,static,1342308864
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO_SF,combobox,1342242818
Control5=IDC_BUTTON_REFSC,button,1342242816
Control6=IDC_STATIC_GRSF,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_IN,static,1342308864
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_IN,edit,1350631552
Control11=IDC_BUTTON_REFIN,button,1342242816
Control12=IDC_STATIC_GRIN,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC_OUT,static,1342308864
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_OUT,edit,1350631552
Control17=IDC_BUTTON_REFOUT,button,1342242816
Control18=IDC_STATIC_GROUT,button,1342177287
Control19=IDC_BUTTON_RUN,button,1342242817
Control20=IDOK,button,1342242816
Control21=IDC_BUTTON_OPTION,button,1342242816
Control22=IDC_CHECK1,button,1342242819
Control23=IDC_CHECK2,button,1342242819
Control24=IDC_CHECK3,button,1342242819
Control25=IDC_STATIC,static,1342177792
Control26=IDC_EDIT_SUFFIX,edit,1350762624
Control27=IDC_STATIC,button,1342177287

[CLS:CCustomStatic]
Type=0
HeaderFile=CustomControl.h
ImplementationFile=CustomControl.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=IDC_STATIC_GROUT

