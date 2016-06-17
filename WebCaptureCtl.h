#if !defined(AFX_WEBCAPTURECTL_H__577C8F58_A5AA_4BD0_894B_F4484937FF4E__INCLUDED_)
#define AFX_WEBCAPTURECTL_H__577C8F58_A5AA_4BD0_894B_F4484937FF4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// WebCaptureCtl.h : Declaration of the CWebCaptureCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CWebCaptureCtrl : See WebCaptureCtl.cpp for implementation.

#include "SelectRect.h"

class CWebCaptureCtrl : public COleControl
{
	DECLARE_DYNCREATE(CWebCaptureCtrl)

// Constructor
public:
	CWebCaptureCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebCaptureCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CWebCaptureCtrl();

	DECLARE_OLECREATE_EX(CWebCaptureCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CWebCaptureCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CWebCaptureCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CWebCaptureCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CWebCaptureCtrl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CWebCaptureCtrl)
	afx_msg void OnCapture();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CWebCaptureCtrl)
	void FireOnCaptureData(LPCTSTR data)
		{FireEvent(eventidOnCaptureData,EVENT_PARAM(VTS_BSTR), data);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CWebCaptureCtrl)
	dispidOnCapture = 1L,
	eventidOnCaptureData = 1L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBCAPTURECTL_H__577C8F58_A5AA_4BD0_894B_F4484937FF4E__INCLUDED)
