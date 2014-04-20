#if !defined(GlobalFunction_H__283745__INCLUDED)
#define GlobalFunction_H__283745__INCLUDED
#include "stdafx.h"
typedef struct _TagItem{
	HWND hWnd;
	int w;
	int h;
	int x;
	int y;
	CString strName;
	HWND hWndWeb;
	HICON hIcon;
	BOOL bSelect;
	BOOL bOver;
}_TagItem;
// 全局变量
extern HDC g_SkinDC;
extern HFONT g_hFont;
extern HFONT g_hFont2;
extern HICON g_hPageIcon;
//全局函数
extern BOOL Comet_RegClass(CString strClassName,HBRUSH hbrBackground);
extern LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
extern void DrawChildBack(HWND hParent,HWND hChild,HDC hDC);
extern CString _ToStr(long inParame);
extern CString _ToStr(int inParame);
extern CString _ToStr(HWND inParame);
#endif 
