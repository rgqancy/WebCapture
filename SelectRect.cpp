// SelectRect.cpp : implementation file
//

#include "stdafx.h"
#include "WebCapture.h"
#include "SelectRect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectRect dialog


CSelectRect::CSelectRect(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectRect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectRect)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//选择的区域的大小
	rectSelect.SetRect(0, 0, 0, 0);

	//步骤 默认选择阶段
	Step = 0;

	//记录第一个
	ptFirst = CPoint(0,0);

	//全屏位图指针和选定区域的位图指针
	hDibFull = NULL;
	hDibSelect = NULL;

	bMove = FALSE;
	MoveType = 0;
	MoveStart = CPoint(0, 0);
	TempRect = CRect(0, 0, 0, 0);

	Finished = FALSE;
}


void CSelectRect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectRect)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectRect, CDialog)
	//{{AFX_MSG_MAP(CSelectRect)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectRect message handlers

BOOL CSelectRect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//移动窗口到全屏
	CRect rectFull;
	rectFull.left = 0;
	rectFull.top = 0;
	rectFull.right = GetSystemMetrics(SM_CXSCREEN);
	rectFull.bottom = GetSystemMetrics(SM_CYSCREEN);

	MoveWindow(rectFull,TRUE);

	//设置全端显示
	//::SetWindowPos(m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE | SWP_NOMOVE);

	//拷贝全屏位图
	hDibFull = CopyScreenToDIB(&rectFull);

	return TRUE;  // return TRUE unless you set the focus to a control
	  // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelectRect::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	//绘制全屏的抓图,供用户选择
	RECT rectFull;
	rectFull.left = 0;
	rectFull.top = 0;
	rectFull.right = GetSystemMetrics(SM_CXSCREEN);
	rectFull.bottom = GetSystemMetrics(SM_CYSCREEN);
	PaintDIB(dc.m_hDC, &rectFull,hDibFull,&rectFull,NULL);

	if( Finished )
		return;

	//绘制提示框
	CBrush brMenu;
	brMenu.CreateSolidBrush(RGB(192, 240, 255));
	dc.SelectObject(&brMenu);
	CPen penMenu;
	penMenu.CreatePen(PS_SOLID, 1, RGB(192, 240, 255));
	dc.SelectObject(&penMenu);
	CRect menu;
	CPoint ptCur;
	GetCursorPos(&ptCur);
	if( rectFull.right-ptCur.x<120 )
	{
		//右下
		if( rectFull.bottom-ptCur.y<120 )
		{
			menu.left = ptCur.x - 110;
			menu.top = ptCur.y - 110;
			menu.right = ptCur.x - 10;
			menu.bottom = ptCur.y - 10;
		}
		//右上
		else
		{
			menu.left = ptCur.x - 110;
			menu.top = ptCur.y + 10;
			menu.right = ptCur.x - 10;
			menu.bottom = ptCur.y + 110;
		}
	}
	else if( ptCur.x<120 )
	{
		//左下
		if( rectFull.bottom-ptCur.y<120 )
		{
			menu.left = ptCur.x + 10;
			menu.top = ptCur.y - 110;
			menu.right = ptCur.x + 110;
			menu.bottom = ptCur.y - 10;
		}
		//左上
		else
		{
			menu.left = ptCur.x + 10;
			menu.top = ptCur.y + 10;
			menu.right = ptCur.x + 110;
			menu.bottom = ptCur.y + 110;
		}
	}
	else
	{
		//中下
		if( rectFull.bottom-ptCur.y<120 )
		{
			menu.left = ptCur.x + 10;
			menu.top = ptCur.y - 110;
			menu.right = ptCur.x + 110;
			menu.bottom = ptCur.y - 10;
		}
		//中上
		else
		{
			menu.left = ptCur.x + 10;
			menu.top = ptCur.y + 10;
			menu.right = ptCur.x + 110;
			menu.bottom = ptCur.y + 110;
		}
	}
	dc.Rectangle(menu);
	brMenu.DeleteObject();
	penMenu.DeleteObject();
	
	dc.SetBkMode(TRANSPARENT);
	CString Msg1 = "选择区域后";
	CString Msg2 = "双击确认";
	CString Msg3;
	Msg3.Format("宽度:%d px", rectSelect.Width());
	CString Msg4;
	Msg4.Format("高度:%d px", rectSelect.Height());
	dc.TextOut(menu.left+5, menu.top+5, Msg1.GetBuffer(0), Msg1.GetLength());
	dc.TextOut(menu.left+5, menu.top+25, Msg2.GetBuffer(0), Msg2.GetLength());
	dc.TextOut(menu.left+5, menu.top+45, Msg3.GetBuffer(0), Msg3.GetLength());
	dc.TextOut(menu.left+5, menu.top+65, Msg4.GetBuffer(0), Msg4.GetLength());

	if( Step > 0 )
	{
		//绘制选定的区域的红色边框
		CPen pnRed;
		pnRed.CreatePen(PS_SOLID,1,RGB(255,0,0));
		dc.SelectObject(&pnRed);
		CRect rect = rectSelect;
		dc.MoveTo(rect.left, rect.top);
		dc.LineTo(rect.left, rect.bottom);
		dc.LineTo(rect.right, rect.bottom);
		dc.LineTo(rect.right, rect.top);
		dc.LineTo(rect.left, rect.top);
		pnRed.DeleteObject();

		if( Step == 2 || Step == 3 || Step == 4 )
		{
			CBrush brJust;
			brJust.CreateSolidBrush(RGB(255, 0, 0));
			dc.SelectObject(&brJust);

			CRect rect1 = CRect(rect.left-2, rect.top-2, rect.left+2, rect.top+2);
			CRect rect2 = CRect(rect.left+rect.Width()/2-2, rect.top-2, rect.left+rect.Width()/2+2, rect.top+2);
			CRect rect3 = CRect(rect.right-2, rect.top-2, rect.right+2, rect.top+2);
			CRect rect4 = CRect(rect.right-2, rect.top+rect.Height()/2-2, rect.right+2, rect.top+rect.Height()/2+2);
			CRect rect5 = CRect(rect.right-2, rect.bottom-2, rect.right+2, rect.bottom+2);
			CRect rect6 = CRect(rect.left+rect.Width()/2-2, rect.bottom-2, rect.left+rect.Width()/2+2, rect.bottom+2);
			CRect rect7 = CRect(rect.left-2, rect.bottom-2, rect.left+2, rect.bottom+2);
			CRect rect8 = CRect(rect.left-2, rect.top+rect.Height()/2-2, rect.left+2, rect.top+rect.Height()/2+2);
			dc.Rectangle(rect1);
			dc.Rectangle(rect2);
			dc.Rectangle(rect3);
			dc.Rectangle(rect4);
			dc.Rectangle(rect5);
			dc.Rectangle(rect6);
			dc.Rectangle(rect7);
			dc.Rectangle(rect8);
			brJust.DeleteObject();
		}
	}

	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CSelectRect::OnEraseBkgnd()
{
	return TRUE;
}

void CSelectRect::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int maxw = GetSystemMetrics(SM_CXSCREEN);
	int maxh = GetSystemMetrics(SM_CYSCREEN);

	int dx, dy;
	dx = point.x - MoveStart.x;
	dy = point.y - MoveStart.y;

	//设置鼠标
	CRect rect = rectSelect;
	CRect rect1 = CRect(rect.left-2, rect.top-2, rect.left+2, rect.top+2);
	CRect rect2 = CRect(rect.left+rect.Width()/2-2, rect.top-2, rect.left+rect.Width()/2+2, rect.top+2);
	CRect rect3 = CRect(rect.right-2, rect.top-2, rect.right+2, rect.top+2);
	CRect rect4 = CRect(rect.right-2, rect.top+rect.Height()/2-2, rect.right+2, rect.top+rect.Height()/2+2);
	CRect rect5 = CRect(rect.right-2, rect.bottom-2, rect.right+2, rect.bottom+2);
	CRect rect6 = CRect(rect.left+rect.Width()/2-2, rect.bottom-2, rect.left+rect.Width()/2+2, rect.bottom+2);
	CRect rect7 = CRect(rect.left-2, rect.bottom-2, rect.left+2, rect.bottom+2);
	CRect rect8 = CRect(rect.left-2, rect.top+rect.Height()/2-2, rect.left+2, rect.top+rect.Height()/2+2);


	switch(Step)
	{
	case 1:	//选择
		rectSelect.left = ptFirst.x;
		rectSelect.top = ptFirst.y;
		rectSelect.right = point.x;
		rectSelect.bottom = point.y;
		JustSelectRect();
		break;
	case 2://调整
		if( rect1.PtInRect(point) || rect5.PtInRect(point) )
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		else if( rect2.PtInRect(point) || rect6.PtInRect(point) )
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
		else if( rect3.PtInRect(point) || rect7.PtInRect(point) )
			SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		else if( rect4.PtInRect(point) || rect8.PtInRect(point) )
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		else if( rect.PtInRect(point) )
			SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		break;
	case 3: 
		switch(MoveType)
		{
		case 1:
			rectSelect = TempRect;
			rectSelect.left += dx;
			rectSelect.top += dy;
			JustSelectRect();
			break;
		case 2:
			rectSelect = TempRect;
			rectSelect.top += dy;
			JustSelectRect();
			break;
		case 3:
			rectSelect = TempRect;
			rectSelect.right += dx;
			rectSelect.top += dy;
			JustSelectRect();
			break;
		case 4:
			rectSelect = TempRect;
			rectSelect.right += dx;
			JustSelectRect();
			break;
		case 5:
			rectSelect = TempRect;
			rectSelect.right += dx;
			rectSelect.bottom += dy;
			JustSelectRect();
			break;
		case 6:
			rectSelect = TempRect;
			rectSelect.bottom += dy;
			JustSelectRect();
			break;
		case 7:
			rectSelect = TempRect;
			rectSelect.left += dx;
			rectSelect.bottom += dy;
			JustSelectRect();
			break;
		case 8:
			rectSelect = TempRect;
			rectSelect.left += dx;
			JustSelectRect();
			break;
		case 9:
			rectSelect = TempRect;
			rectSelect.left += dx;			
			rectSelect.top += dy;			
			rectSelect.right += dx;			
			rectSelect.bottom += dy;

			if( rectSelect.left<0 )
			{
				rectSelect.left = 0;
				rectSelect.right = TempRect.Width();
			}
			if( rectSelect.right>maxw )
			{
				rectSelect.right = maxw;
				rectSelect.left = maxw - TempRect.Width();
			}
			if( rectSelect.top<0 )
			{
				rectSelect.top = 0;
				rectSelect.bottom = TempRect.Height();
			}
			if( rectSelect.bottom>maxh )
			{
				rectSelect.bottom = maxh;
				rectSelect.top = maxh - TempRect.Height();
			}

			JustSelectRect();
			break;
		}
	}
	
	Invalidate(TRUE);
	
	CDialog::OnMouseMove(nFlags, point);
}

void CSelectRect::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	switch(Step)
	{
	case 0:
		ptFirst = point;
		Step = 1;
		OnMouseMove(nFlags, point);
		break;
	case 2:
		//设置鼠标
		CRect rect = rectSelect;
		CRect rect1 = CRect(rect.left-2, rect.top-2, rect.left+2, rect.top+2);
		CRect rect2 = CRect(rect.left+rect.Width()/2-2, rect.top-2, rect.left+rect.Width()/2+2, rect.top+2);
		CRect rect3 = CRect(rect.right-2, rect.top-2, rect.right+2, rect.top+2);
		CRect rect4 = CRect(rect.right-2, rect.top+rect.Height()/2-2, rect.right+2, rect.top+rect.Height()/2+2);
		CRect rect5 = CRect(rect.right-2, rect.bottom-2, rect.right+2, rect.bottom+2);
		CRect rect6 = CRect(rect.left+rect.Width()/2-2, rect.bottom-2, rect.left+rect.Width()/2+2, rect.bottom+2);
		CRect rect7 = CRect(rect.left-2, rect.bottom-2, rect.left+2, rect.bottom+2);
		CRect rect8 = CRect(rect.left-2, rect.top+rect.Height()/2-2, rect.left+2, rect.top+rect.Height()/2+2);

		if( rect1.PtInRect(point) )
			MoveType = 1;
		else if( rect2.PtInRect(point) )
			MoveType = 2;
		else if( rect3.PtInRect(point) )
			MoveType = 3;
		else if( rect4.PtInRect(point) )
			MoveType = 4;
		else if( rect5.PtInRect(point) )
			MoveType = 5;
		else if( rect6.PtInRect(point) )
			MoveType = 6;
		else if( rect7.PtInRect(point) )
			MoveType = 7;
		else if( rect8.PtInRect(point) )
			MoveType = 8;
		else if( rect.PtInRect(point) )
			MoveType = 9;

		bMove = TRUE;
		MoveStart = point;
		TempRect = rectSelect;
		Step = 3;
		break;
	}	

	Invalidate(TRUE);
	CDialog::OnLButtonDown(nFlags, point);
}

void CSelectRect::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	switch(Step)
	{
	case 1:
		Step = 2;
		break;
	case 3:
		bMove = FALSE;
		MoveType = 0;
		MoveStart = CPoint(0, 0);
		TempRect = CRect(0, 0, 0, 0);
		Step = 2;
		break;
	}

	Invalidate(TRUE);
	CDialog::OnLButtonUp(nFlags, point) ;
}

void CSelectRect::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Step = 0;
	//选择的区域的大小
	rectSelect.SetRect(0, 0, 0, 0);

	//步骤 默认选择阶段
	Step = 0;

	//记录第一个
	ptFirst = CPoint(0,0);

	bMove = FALSE;
	MoveType = 0;
	MoveStart = CPoint(0, 0);
	TempRect = CRect(0, 0, 0, 0);

	CDialog::OnRButtonUp(nFlags, point);
}

void CSelectRect::JustSelectRect()
{
	//鼠标移动计算选择的区域的矩形
	int maxw = GetSystemMetrics(SM_CXSCREEN);
	int maxh = GetSystemMetrics(SM_CYSCREEN);
	rectSelect.NormalizeRect();
	if( rectSelect.Width() < 10 )
		if( rectSelect.right >= maxw-10 )
			rectSelect.left = rectSelect.left-10;
		else
			rectSelect.right = rectSelect.right + 10;
	if( rectSelect.Height() < 10 )
		if( rectSelect.bottom >= maxh-10 )
			rectSelect.top = rectSelect.top-10;
		else
			rectSelect.bottom = rectSelect.bottom + 10;
}

void CSelectRect::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if( (Step==2||Step==3) && rectSelect.PtInRect(point) )
	{
		Finished = TRUE;

		SetTimer(NULL, 100, NULL);
	}
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

int CSelectRect::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num = 0;  // number of image encoders
	UINT size = 0; // size of the image encoder array in bytes
	
	ImageCodecInfo* pImageCodecInfo = NULL;
	
	Gdiplus::GetImageEncodersSize(&num, &size);
	if(size == 0)
	return -1;  // Failure  
	
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure  
	
	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);
	
	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success  
		}
	}
	
	free(pImageCodecInfo);
	return -1;  // Failure  
}

void CSelectRect::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(nIDEvent);

	hDibSelect = CopyScreenToDIB(&rectSelect);
	HBITMAP hBitmap = DIBToBitmap(hDibSelect, NULL);

	Gdiplus::Bitmap image(hBitmap, NULL);  
	CLSID pngClsid;  
	GetEncoderClsid(L"image/png", &pngClsid);  

	CHAR Buffer[1024];
	GetTempPath(MAX_PATH, Buffer);
	CString TempFileName;
	TempFileName.Format("%scapture.png", Buffer);
	image.Save(TempFileName.AllocSysString(), &pngClsid, NULL);

	data = "";

	BYTE fBuffer[8*1024];
	BYTE hexBuffer[8*1024*2+1];
	FILE *fp = fopen(TempFileName.GetBuffer(0), "rb+");
	if( fp )
	{
		rewind(fp);
		while( !feof(fp) )
		{
			char list[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

			ZeroMemory(&hexBuffer[0], 8*1024*2+1);
			size_t len = fread(&fBuffer[0], 1, 8*1024, fp);
			for(DWORD x=0; x<len; x++)
			{
				hexBuffer[2*x] = list[fBuffer[x]/16];
				hexBuffer[2*x+1] = list[fBuffer[x]%16];
			}
			CString temp;
			temp.Format("%s", &hexBuffer[0]);
			data += temp;
		}
	}
	fclose(fp);

	OnOK();
	
	CDialog::OnTimer(nIDEvent);
}
