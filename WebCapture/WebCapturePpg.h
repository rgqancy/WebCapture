#if !defined(AFX_WEBCAPTUREPPG_H__D1253031_C7E8_42CA_A17A_D55AC331A666__INCLUDED_)
#define AFX_WEBCAPTUREPPG_H__D1253031_C7E8_42CA_A17A_D55AC331A666__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// WebCapturePpg.h : Declaration of the CWebCapturePropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CWebCapturePropPage : See WebCapturePpg.cpp.cpp for implementation.

class CWebCapturePropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CWebCapturePropPage)
	DECLARE_OLECREATE_EX(CWebCapturePropPage)

// Constructor
public:
	CWebCapturePropPage();

// Dialog Data
	//{{AFX_DATA(CWebCapturePropPage)
	enum { IDD = IDD_PROPPAGE_WEBCAPTURE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CWebCapturePropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBCAPTUREPPG_H__D1253031_C7E8_42CA_A17A_D55AC331A666__INCLUDED)
