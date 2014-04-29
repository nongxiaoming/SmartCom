// MainDlg.cpp : 实现文件


#include "stdafx.h"
#include "SmartCom.h"
#include "MainDlg.h"
#include "GlobalFunction.h"

// CMainDlg

IMPLEMENT_DYNAMIC(CMainDlg, CWnd)

CMainDlg::CMainDlg()
:m_bTracking(FALSE)
{
	
}

CMainDlg::~CMainDlg()
{
}


BEGIN_MESSAGE_MAP(CMainDlg, CWnd)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()



// CMainDlg 消息处理程序



BOOL CMainDlg::CreateDlg(void)
{

	CString strClassName=_T("SmartCom");
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_hCursor_Arrow = LoadCursor (0, IDC_ARROW);
	m_hCursor_SizeWE = LoadCursor (0, IDC_SIZEWE);
	m_hCursor_SizeNWSE = LoadCursor (0, IDC_SIZENWSE);
	m_hbrBack=CreateSolidBrush(0xB98B49);
	HDC hSrcDC=::GetDC(0);
	g_SkinDC=::CreateCompatibleDC(hSrcDC);
	m_hCacheDC=::CreateCompatibleDC(hSrcDC);
	::ReleaseDC(0,hSrcDC);
	::SetBkMode(m_hCacheDC,TRANSPARENT);
	HBITMAP hBitmap=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_SKIN1));
	::SelectObject(g_SkinDC,hBitmap);
	m_MaxIcon=(HICON)::LoadImage(hInstance,MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR); 
	m_MinIcon=(HICON)::LoadImage(hInstance,MAKEINTRESOURCE(IDR_MAINFRAME), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	g_hPageIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_PAGE));
	g_hFont=CreateFont(12, 0, 0, 0, 400, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, _T("宋体"));
	g_hFont2=CreateFont(12, 0, 0, 0, 700, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, _T("宋体"));
	//----------------------
	BOOL bRet=Comet_RegClass(strClassName,m_hbrBack);
	if(!bRet)return FALSE;
	CRect rc(100,100,850,600);
	bRet=CWnd::CreateEx(0,strClassName,_T("SmartCom"),WS_POPUP|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,rc,NULL,0);
	if(!bRet)return FALSE;
	//----------------------
	m_MainBtn.Create(m_hWnd,0,1,37,22,128,122,IDM_MAIN);
	m_CloseBtn.Create(m_hWnd,0,1,37,22,128,122,IDM_CLOSE);
	m_MaxBtn.Create(m_hWnd,0,1,25,22,78,122,IDM_MAX);
	m_MinBtn.Create(m_hWnd,0,1,25,22,53,122,IDM_MIN);
	m_MenuBtn.Create(m_hWnd,0,1,27,22,26,122,IDM_MENU);
	m_HelpBtn.Create(m_hWnd,0,1,26,22,0,122,IDM_HELP);

	//----------------------
	//m_AddrEdit.CreateEx(0,_T("Edit"),_T(""),WS_CHILD|WS_VISIBLE,rc,this,0);
	////----------------------
	//m_Tag.AddItem(_T("标签1"));
	//m_Tag.AddItem(_T("标签2"));
	//m_Tag.AddItem(_T("标签3"));
	//----------------------
	UpdateCache();
	return ::IsWindow(m_hWnd);
}
void CMainDlg::Show(void)
{
	CWnd::ShowWindow(SW_SHOW);
}
void CMainDlg::UpdateCache()
{
	//if(!IsWindow(m_AddrEdit.m_hWnd))return;
	GetClientRect(&m_ClientRc);
	m_nWidth=m_ClientRc.Width();
	m_nHeight=m_ClientRc.Height();
	int y=0;
	if (IsZoomed()){
		m_MainBtn.Create(m_hWnd,5,3,39,28,141,53,IDM_MAIN);
		m_MainBtn.hIcon=m_MinIcon;
		m_TitleRc=CRect(65,-50,m_nWidth-150,-5);
		y=35;
	}else{
		m_MainBtn.Create(m_hWnd,3,3,61,48,62,1,IDM_MAIN);
		m_MainBtn.hIcon=m_MaxIcon;
		m_TitleRc=CRect(65,0,m_nWidth-150,25);		
		y=53;
	}
	int x=m_nWidth-1;
	x=x-m_CloseBtn.nWidth;
	m_CloseBtn.x=x;
	x=x-m_MaxBtn.nWidth;
	m_MaxBtn.x=x;	
	x=x-m_MinBtn.nWidth;
	m_MinBtn.x=x;
	x=x-m_MenuBtn.nWidth;
	m_MenuBtn.x=x;
	x=x-m_HelpBtn.nWidth;
	m_HelpBtn.x=x;
	m_BarTop=y;
	x=m_MainBtn.x+m_MainBtn.nWidth+2;
	m_TagRect=CRect(m_MainBtn.x+m_MainBtn.nWidth+2,y-30,m_HelpBtn.x-2,y);
	m_BarRect=CRect(3,y,m_nWidth-3,y+38);
	y+=38;
	m_StatuRect=CRect(3,m_nHeight-28,m_nWidth-3,m_nHeight-3);
	m_WebRect=CRect(3,y,m_nWidth-3,m_StatuRect.top-1);
	//----------------------------
	HRGN hRgn1=::CreateRectRgn (0, 0, 0, 0);
	HRGN hRgn2=::CreateRoundRectRgn (0, 0, m_nWidth + 1, m_nHeight+ 1,4,4);
	HRGN hRgn3=::CreateRectRgn(0,20,m_nWidth+1,m_nHeight);
	::CombineRgn (hRgn1,hRgn2,hRgn3,2);
	::SetWindowRgn (m_hWnd,hRgn1,1);
	::DeleteObject(hRgn1);
	::DeleteObject(hRgn2);
	::DeleteObject(hRgn3);
}

void CMainDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CWnd::OnGetMinMaxInfo(lpMMI);	
	lpMMI->ptMinTrackSize.x=500;
	lpMMI->ptMinTrackSize.y=400;

	
}

void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	UpdateCache();
	CWnd::OnSize(nType, cx, cy);
}

void CMainDlg::OnPaint()
{
	CPaintDC dc(this); 
	CDC memDC;CBitmap memBitmap;
	memDC.CreateCompatibleDC(&dc);
	memBitmap.CreateCompatibleBitmap(&dc,m_nWidth,m_nHeight);
	memDC.SelectObject(&memBitmap);
	memDC.SetBkMode(TRANSPARENT);
	HDC hDC=memDC.m_hDC;
	//-------------------------
	if(::GetProp(m_hWnd,_T("Comet_CacheDC"))){
		::SelectObject(m_hCacheDC,m_hOldCacheBitmap);
		::DeleteObject((HGDIOBJ)m_hCacheBitmap);
	}else{
		::SetProp(m_hWnd,_T("Comet_CacheDC"),(HANDLE)m_hCacheDC);
	}
	m_hCacheBitmap=CreateCompatibleBitmap(dc.m_hDC,m_nWidth,m_nWidth);
	m_hOldCacheBitmap=(HBITMAP)::SelectObject(m_hCacheDC,m_hCacheBitmap);
	//--------------------------------------
	::FillRect(hDC,m_ClientRc,m_hbrBack);
	::StretchBlt(hDC,0,0,3,m_nHeight,g_SkinDC,0,47,3,1,SRCCOPY);
	::StretchBlt(hDC,m_nWidth-3,0,3,m_nHeight,g_SkinDC,57,47,3,1,SRCCOPY);
	::BitBlt(hDC,0,0,5,48,g_SkinDC,0,0,SRCCOPY);
	::StretchBlt(hDC,5,0,m_nWidth-10,48,g_SkinDC,5,0,10,48,SRCCOPY);
	::BitBlt(hDC,m_nWidth-5,0,5,48,g_SkinDC,55,0,SRCCOPY);
	::BitBlt(hDC,0,m_nHeight-3,3,3,g_SkinDC,0,47,SRCCOPY);
	::StretchBlt(hDC,3,m_nHeight-3,m_nWidth-6,3,g_SkinDC,5,47,10,3,SRCCOPY);
	::BitBlt(hDC,m_nWidth-3,m_nHeight-3,3,3,g_SkinDC,57,47,SRCCOPY);
	//--------------------------------------
	::StretchBlt(hDC,m_BarRect.left,m_BarRect.top-4,m_BarRect.Width(),m_BarRect.Height()+4,g_SkinDC,0,79,4,41,SRCCOPY);
	//--------------------------------------
	::StretchBlt(hDC,m_StatuRect.left,m_StatuRect.top,m_StatuRect.Width(),m_StatuRect.Height(),g_SkinDC,170,102,20,25,SRCCOPY);
	::BitBlt(hDC,m_StatuRect.right-9,m_StatuRect.bottom-9,7,8,g_SkinDC,241,118,SRCCOPY);
	//--------------------------------------
	//::StretchBlt(hDC,m_FavoritesBtn.x+m_FavoritesBtn.nWidth,m_FavoritesBtn.y,m_GoUrlBtn.x-m_FavoritesBtn.x-//m_FavoritesBtn.nWidth,m_ForwardBtn.nHeight,g_SkinDC,167,160,10,m_ForwardBtn.nHeight,SRCCOPY);//地址栏
	//--------------------------------------
	CBrush brush(RGB(255,255,255));
	memDC.FillRect(m_WebRect,&brush);
	//--------------------------------------
	m_MainBtn.Draw(hDC);
	m_MinBtn.Draw(hDC);
	m_MaxBtn.Draw(hDC);
	m_CloseBtn.Draw(hDC);
	m_MenuBtn.Draw(hDC);
	m_HelpBtn.Draw(hDC);
//	m_GoUrlBtn.Draw(hDC);
	//--------------------------------------
	CString str;
	GetWindowText(str);
	memDC.DrawText(str,m_TitleRc,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_HIDEPREFIX);
	//--------------------------------------
	::BitBlt(m_hCacheDC,0,0,m_nWidth,m_nHeight,hDC,0,0,SRCCOPY);
	dc.BitBlt(0,0,m_nWidth,m_nHeight,&memDC,0,0,SRCCOPY);
}

void CMainDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(DirectMouseEvent(WM_LBUTTONDOWN,point.x,point.y)){ 
		CWnd::OnLButtonDown(nFlags, point);
		return;
	}else if(point.x>m_TitleRc.left && point.x<m_TitleRc.right && point.y<m_TitleRc.bottom){ 
		ReleaseCapture ();
		SendMessage (WM_NCLBUTTONDOWN, HTCAPTION, 0);
		return;
	}else if(m_nHeight - point.y < 15 && m_nWidth - point.x < 5){ // 右下角
		SendMessage ( WM_SYSCOMMAND, 61448, 0);  //' 右下角调大小
		return;
	}else if(point.y>20 && m_nWidth - point.x < 5){ // 右边
		SendMessage ( WM_SYSCOMMAND, 61442, 0);  //' 右边调大小
		return;
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CMainDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = 1;
		m_bTracking = (bool)_TrackMouseEvent(&tme);
	}
	if(DirectMouseEvent(WM_MOUSEMOVE,point.x,point.y)){ 
		CWnd::OnLButtonDown(nFlags, point);
		return;
	}else if(m_nHeight - point.y < 15 && m_nWidth - point.x < 5){ // 右下角
		SetWndCursor (m_hCursor_SizeNWSE);
		return;
	}else if(point.y>20 && m_nWidth - point.x < 5){ // 右边
		SetWndCursor (m_hCursor_SizeWE);
		return;
	}else{
		SetWndCursor (m_hCursor_Arrow);
		return;
	}

	CWnd::OnMouseMove(nFlags, point);
}
void CMainDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	DirectMouseEvent(WM_LBUTTONUP,point.x,point.y);
	CWnd::OnLButtonUp(nFlags, point);
}
LRESULT CMainDlg::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	DirectMouseEvent(WM_MOUSELEAVE,LOWORD(lParam),HIWORD(lParam));
	m_bTracking = FALSE;
	return 0;
}
//设置鼠标指针
void CMainDlg::SetWndCursor(HCURSOR hCursor){
	if (GetClassLong (m_hWnd,GCL_HCURSOR) != (DWORD)hCursor){
		SetClassLong (m_hWnd,GCL_HCURSOR, (LONG)hCursor);
	}

}
BOOL CMainDlg::OnEraseBkgnd(CDC* pDC)
{
	try
	{
		::BitBlt(pDC->m_hDC,0,0,m_nWidth,m_nHeight,m_hCacheDC,0,0,SRCCOPY);
		return true;
	}
	catch (...)
	{
		return CWnd::OnEraseBkgnd(pDC);
	}
}

BOOL CMainDlg::DirectMouseEvent(UINT msg, int x, int y)
{
	m_MinBtn.MouseEvent(msg,x,y);
	m_MaxBtn.MouseEvent(msg,x,y);
	m_CloseBtn.MouseEvent(msg,x,y);
	m_MenuBtn.MouseEvent(msg,x,y);
	m_HelpBtn.MouseEvent(msg,x,y);
	m_MainBtn.MouseEvent(msg,x,y);
	return FALSE;
}



void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	RECT rc;
	switch (nID)
	{
		case SC_MAXIMIZE:
			CWnd::OnSysCommand(nID, lParam);
			m_MaxBtn.SkinX=103;
			SystemParametersInfo(SPI_GETWORKAREA,NULL,&rc,0);
			MoveWindow(rc.left-2,rc.top-2,rc.right-rc.left+4,rc.bottom-rc.top+2,1);
			return;
			break;
		case SC_RESTORE:
			m_MaxBtn.SkinX=78;
			break;

	}

	CWnd::OnSysCommand(nID, lParam);
}


//void CMainDlg::CreateWeb(CString strUrl)
//{
//	CCometWebBrowser *pWeb=new CCometWebBrowser();
//	pWeb->Create(NULL,_T(""),WS_VISIBLE,m_WebRect,this,0);
//	pWeb->Navigate(strUrl);
//}

BOOL CMainDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch(wParam){
		case IDM_GOURL:
			//OnGoUrl(NULL);
			break;

	}

	return CWnd::OnCommand(wParam, lParam);
}

