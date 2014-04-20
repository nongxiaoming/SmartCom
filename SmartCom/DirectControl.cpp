#include "StdAfx.h"
#include "DirectControl.h"
#include "GlobalFunction.h"
// download by http://www.codefans.net
CDirectControl::CDirectControl(void)
: nWidth(0)
, nHeight(0)
, x(0)
, y(0)
, Type(0)
, ID(0)
, Over(false)
, Down(false)
, hWnd(NULL)
{

}

CDirectControl::~CDirectControl(void)
{
}

void CDirectControl::Create(HWND hWndParent,int nX,int nY,int nW, int nH,int nSkinX, int nSkinY,int nID)
{
	hWnd=hWndParent;
	SkinX=nSkinX;
	SkinY=nSkinY;
	nWidth=nW;
	nHeight=nH;
	x=nX;
	y=nY;
	ID=nID;
}

void CDirectControl::Draw(HDC hDC)
{
	int SrcX=SkinX;
	int SrcY=SkinY;

	if (ID==IDM_MAIN)
	{
		if (Over)SrcX=SkinX+nWidth*1;
		if (Down)SrcX=SkinX+nWidth*2;
	}else{
		if (Over)SrcY=SkinY+nHeight*1;
		if (Down)SrcY=SkinY+nHeight*2;
	}
	BitBlt(hDC,x,y,nWidth,nHeight,g_SkinDC,SrcX,SrcY,SRCCOPY);
	if (ID==IDM_MAIN){
		DrawIconEx(hDC,x+4,y+4,hIcon,nHeight-8,nHeight-8,0,0,3);
	}
}
void CDirectControl::DrawEx()
{
	HDC hCacheDC=(HDC)::GetProp(hWnd,_T("Comet_CacheDC"));
	Draw(hCacheDC);
	HDC hDC=GetDC(hWnd);
	BitBlt(hDC,x,y,nWidth,nHeight,hCacheDC,x,y,SRCCOPY);
	ReleaseDC(hWnd,hDC);
}
BOOL CDirectControl::MouseEvent(UINT msg, int nX,int nY)
{
	BOOL bRet=FALSE;
	if (msg==WM_MOUSELEAVE)
	{
		if (Down || Over)
		{
			Over=FALSE;
			Down=FALSE;
			DrawEx();			
		}
		return bRet;
	}
	if (nX>=x && nY>=y)
	{
		if (nX<=nHeight+x && nY<=nHeight+y)
		{
			bRet=TRUE;
			if(!Over && msg==WM_MOUSEMOVE){
				Over=TRUE;				
				DrawEx();				
			}else if(!Down && msg==WM_LBUTTONDOWN){
				Over=TRUE;
				Down=TRUE;
				DrawEx();
			}else if(Down && msg==WM_LBUTTONUP){
				Over=TRUE;
				Down=FALSE;
				DrawEx();
				OnClick();
			}
			return bRet;
		}
	}
	
	if(Down && msg==WM_LBUTTONUP){
		Over=FALSE;
		Down=FALSE;
		DrawEx();
		return bRet;
	}
	if(!Down && Over && msg==WM_MOUSEMOVE){
		Over=FALSE;
		DrawEx();
	}
	return bRet;
}
void CDirectControl::OnClick(void)
{
	::ReleaseCapture ();
	switch (ID)
	{
	case IDM_CLOSE:
		::PostMessage(hWnd,WM_SYSCOMMAND,SC_CLOSE,0);
		break;
	case IDM_MIN:
		::PostMessage(hWnd,WM_SYSCOMMAND,SC_MINIMIZE,0);
		break;
	case IDM_MAX:
		if(IsZoomed(hWnd)){
			::PostMessage(hWnd,WM_SYSCOMMAND,SC_RESTORE,0);
		}else{
			::PostMessage(hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);
		}
		break;
	default:
		::PostMessage(hWnd,WM_COMMAND,ID,0);
		break;
	}
}
