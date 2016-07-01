; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSelectRect
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WebCapture.h"
CDK=Y

ClassCount=3
Class1=CWebCaptureCtrl
Class2=CWebCapturePropPage

ResourceCount=3
Resource1=IDD_ABOUTBOX_WEBCAPTURE
LastPage=0
Resource2=IDD_PROPPAGE_WEBCAPTURE
Class3=CSelectRect
Resource3=IDD_SELECTRECT

[CLS:CWebCaptureCtrl]
Type=0
HeaderFile=WebCaptureCtl.h
ImplementationFile=WebCaptureCtl.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC
LastObject=CWebCaptureCtrl

[CLS:CWebCapturePropPage]
Type=0
HeaderFile=WebCapturePpg.h
ImplementationFile=WebCapturePpg.cpp
Filter=D
LastObject=CWebCapturePropPage

[DLG:IDD_ABOUTBOX_WEBCAPTURE]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPPAGE_WEBCAPTURE]
Type=1
Class=CWebCapturePropPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_SELECTRECT]
Type=1
Class=CSelectRect
ControlCount=0

[CLS:CSelectRect]
Type=0
HeaderFile=SelectRect.h
ImplementationFile=SelectRect.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSelectRect

