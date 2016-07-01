// WebCaptureCtl.cpp : Implementation of the CWebCaptureCtrl ActiveX Control class.

#include "stdafx.h"
#include "WebCapture.h"
#include "WebCaptureCtl.h"
#include "WebCapturePpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CWebCaptureCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CWebCaptureCtrl, COleControl)
	//{{AFX_MSG_MAP(CWebCaptureCtrl)
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CWebCaptureCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CWebCaptureCtrl)
	DISP_FUNCTION(CWebCaptureCtrl, "OnCapture", OnCapture, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CWebCaptureCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CWebCaptureCtrl, COleControl)
	//{{AFX_EVENT_MAP(CWebCaptureCtrl)
	EVENT_CUSTOM("OnCaptureData", FireOnCaptureData, VTS_BSTR)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CWebCaptureCtrl, 1)
	PROPPAGEID(CWebCapturePropPage::guid)
END_PROPPAGEIDS(CWebCaptureCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWebCaptureCtrl, "WEBCAPTURE.WebCaptureCtrl.1",
	0x104c0f32, 0x19fd, 0x41ac, 0x89, 0xe9, 0xf3, 0x87, 0x4, 0xe0, 0xba, 0xa9)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CWebCaptureCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DWebCapture =
		{ 0x971990b5, 0xf442, 0x4ad8, { 0x8d, 0x5d, 0x79, 0x77, 0x1, 0x6c, 0x48, 0x6f } };
const IID BASED_CODE IID_DWebCaptureEvents =
		{ 0x1b4266d0, 0x8f95, 0x4f5c, { 0xb9, 0x32, 0x1a, 0xc5, 0x81, 0x4b, 0x8f, 0xe } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwWebCaptureOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CWebCaptureCtrl, IDS_WEBCAPTURE, _dwWebCaptureOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CWebCaptureCtrl::CWebCaptureCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CWebCaptureCtrl

BOOL CWebCaptureCtrl::CWebCaptureCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_WEBCAPTURE,
			IDB_WEBCAPTURE,
			afxRegApartmentThreading,
			_dwWebCaptureOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CWebCaptureCtrl::CWebCaptureCtrl - Constructor

CWebCaptureCtrl::CWebCaptureCtrl()
{
	InitializeIIDs(&IID_DWebCapture, &IID_DWebCaptureEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CWebCaptureCtrl::~CWebCaptureCtrl - Destructor

CWebCaptureCtrl::~CWebCaptureCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CWebCaptureCtrl::OnDraw - Drawing function

void CWebCaptureCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CWebCaptureCtrl::DoPropExchange - Persistence support

void CWebCaptureCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CWebCaptureCtrl::OnResetState - Reset control to default state

void CWebCaptureCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CWebCaptureCtrl::AboutBox - Display an "About" box to the user

void CWebCaptureCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_WEBCAPTURE);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CWebCaptureCtrl message handlers

void CWebCaptureCtrl::OnCapture() 
{
	// TODO: Add your dispatch handler code here
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken = NULL;

    if(Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL) != Ok)
    {  
		AfxMessageBox("加载GDIPLUS库失败");
    }

	//显示选择对话框
	CSelectRect m_SelectRect;	
	m_SelectRect.DoModal();

	FireOnCaptureData(m_SelectRect.data);

	if(gdiplusToken )
		Gdiplus::GdiplusShutdown(gdiplusToken);
}

BOOL CWebCaptureCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class 
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

BOOL CWebCaptureCtrl::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class 
	
	return COleControl::DestroyWindow();
}
