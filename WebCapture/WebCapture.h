#if !defined(AFX_WEBCAPTURE_H__0B9A35BA_A8FE_4D6E_AAF1_0E69E0704F60__INCLUDED_)
#define AFX_WEBCAPTURE_H__0B9A35BA_A8FE_4D6E_AAF1_0E69E0704F60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// WebCapture.h : main header file for WEBCAPTURE.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWebCaptureApp : See WebCapture.cpp for implementation.

class CWebCaptureApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBCAPTURE_H__0B9A35BA_A8FE_4D6E_AAF1_0E69E0704F60__INCLUDED)
