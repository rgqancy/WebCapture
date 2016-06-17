#if !defined(AFX_SELECTRECT_H__165CD626_3241_40E8_ABD4_14DD1B333690__INCLUDED_)
#define AFX_SELECTRECT_H__165CD626_3241_40E8_ABD4_14DD1B333690__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectRect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectRect dialog

#include "DIBLIB\\DIBLib.h"

#define ULONG_PTR ULONG
#include "GdiPlus\\gdiplus.h"
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

class CSelectRect : public CDialog
{
// Construction
public:
	void JustSelectRect();
	CSelectRect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectRect)
	enum { IDD = IDD_SELECTRECT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	//ȫ����λͼ�����ѡ���λͼ���
	HDIB hDibFull;
	HDIB hDibSelect;
	//ѡ��ľ���
	CRect rectSelect;

	BOOL bMove;
	int MoveType;
	CPoint MoveStart;
	CRect TempRect;
	BOOL Finished;

	CString data;

	//
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectRect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//��͸� ��Ҫ�ù̶���С�����ץͼ
	int iWidth;
	int iHeight;

	//��һ�����Ƿ�ѡ��
	int Step;
	//��¼��һ����
	CPoint ptFirst;

	// Generated message map functions
	//{{AFX_MSG(CSelectRect)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTRECT_H__165CD626_3241_40E8_ABD4_14DD1B333690__INCLUDED_)
