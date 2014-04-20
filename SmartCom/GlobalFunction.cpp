#include "stdafx.h"
#include "GlobalFunction.h"
#include "resource.h"		// 主符号
//----------------------------------
HDC g_SkinDC;
HFONT g_hFont;
HFONT g_hFont2;
HICON g_hPageIcon;
//----------------------------------
BOOL Comet_RegClass(CString strClassName,HBRUSH hbrBackground)//注册窗口类
{
	HINSTANCE hInstance=AfxGetInstanceHandle();
	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof(WNDCLASSEX);	
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= MainWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= ::LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));;
	wcex.hCursor		= ::LoadCursor (0, IDC_ARROW);;
	if(hbrBackground){
	wcex.hbrBackground	= hbrBackground;
	}else{
	wcex.hbrBackground	= (HBRUSH)(COLOR_BTNFACE+1);
	}
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_CUSTOMERSERVICEASSISTANT);
	wcex.lpszClassName	= strClassName;
	wcex.hIconSm		= 0;
	return RegisterClassEx(&wcex);
}
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}
void DrawChildBack(HWND hParent,HWND hChild,HDC hDC)//从父窗口复制背景到子窗口
{
	HDC hCacheDC=(HDC)::GetProp(hParent,_T("Comet_CacheDC"));
	if(hCacheDC){
		POINT pt;pt.x=0;pt.y=0;
		RECT rc;
		::MapWindowPoints(hChild,hParent,&pt,1);
		::GetClientRect(hChild,&rc);
		::BitBlt(hDC,0,0,rc.right,rc.bottom,hCacheDC,pt.x,pt.y,SRCCOPY);
	}
}
CString _ToStr(long inParame){
	CString str;
	str.Format(_T("%d"),inParame);
	return str;
}
CString _ToStr(int inParame){
	CString str;
	str.Format(_T("%d"),inParame);
	return str;
}
CString _ToStr(HWND inParame){
	CString str;
	str.Format(_T("%d"),inParame);
	return str;
}
