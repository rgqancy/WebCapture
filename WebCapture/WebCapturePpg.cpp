// WebCapturePpg.cpp : Implementation of the CWebCapturePropPage property page class.

#include "stdafx.h"
#include "WebCapture.h"
#include "WebCapturePpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CWebCapturePropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CWebCapturePropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CWebCapturePropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CWebCapturePropPage, "WEBCAPTURE.WebCapturePropPage.1",
	0xcf5f6831, 0xb411, 0x4957, 0xb2, 0x27, 0xd7, 0x5, 0x1f, 0xbd, 0x5b, 0x4)


/////////////////////////////////////////////////////////////////////////////
// CWebCapturePropPage::CWebCapturePropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CWebCapturePropPage

BOOL CWebCapturePropPage::CWebCapturePropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_WEBCAPTURE_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CWebCapturePropPage::CWebCapturePropPage - Constructor

CWebCapturePropPage::CWebCapturePropPage() :
	COlePropertyPage(IDD, IDS_WEBCAPTURE_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CWebCapturePropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CWebCapturePropPage::DoDataExchange - Moves data between page and properties

void CWebCapturePropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CWebCapturePropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CWebCapturePropPage message handlers
