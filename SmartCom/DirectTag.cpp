#include "StdAfx.h"
#include "DirectTag.h"

CDirectTag::CDirectTag(void)
: m_nCount(0)
,nOverIndex(-1)
,nSelIndx(-1)
,ItemWidth(0)
{
}

CDirectTag::~CDirectTag(void)
{
}

void CDirectTag::AddItem(CString strName, HICON hIco, HWND hWndWeb)
{
	_TagItem item;
	item.strName=strName;
	item.hWnd=hWndWeb;
	item.hIcon=hIcon;
	item.bSelect=false;
	item.bOver=FALSE;
	if (m_nCount)
	{
		_TagItem  PrevItem=m_ItemArray.GetAt(m_nCount-1);
		item.x=PrevItem.x+PrevItem.w+1;
	}else{
		item.x=0;
		item.bSelect=true;
		nSelIndx=0;
	}
	if(hIco!=0){
		item.hIcon=hIcon;
	}else{
		item.hIcon=g_hPageIcon;
	}
	item.w=ItemWidth;
	item.h=30;
	item.y=nHeight-item.h;
	m_ItemArray.Add(item);
	m_nCount=(int)m_ItemArray.GetCount();
	UpdateSize();

}
void CDirectTag::UpdateSize()
{
	if(!m_nCount)return;
	ItemWidth=nWidth/m_nCount;
	if(ItemWidth>80)ItemWidth=80;
	if(ItemWidth<20)ItemWidth=20;
	_TagItem  item;
	int itemX=0;
	for(int i=0;i<m_nCount;i++)
	{
		item=m_ItemArray.GetAt(i);
		item.w=ItemWidth;
		item.y=nHeight-item.h;
		item.x=itemX;
		itemX=itemX+item.w+1;
		m_ItemArray.SetAt(i,item);
	}
}
void CDirectTag::Move(int nX, int nY, int nW, int nH)
{
	nWidth=nW;
	nHeight=nH;
	x=nX;
	y=nY;
	UpdateSize();
}

void CDirectTag::Draw(HDC hDC)
{
	::SetTextColor(hDC,0x6D4100);
	_TagItem  item;
	for(int i=0;i<m_nCount;i++)
	{
		item=m_ItemArray.GetAt(i);
		DrawItem(hDC,item);
	}
}

void CDirectTag::DrawItem(HDC hDC, _TagItem item)
{
	if(ItemWidth==20 && item.x+item.w>nWidth)return;
	int SkinW=30;
	int SkinH=30;
	int SrcX=SkinX;
	int DestX=x+item.x;
	int DestY=y+item.y;
	if(item.bOver)SrcX=SkinX+SkinW*1;
	if(item.bSelect)SrcX=SkinX+SkinW*2;
	::TransparentBlt(hDC,DestX,DestY,5,item.h,g_SkinDC,SrcX,SkinY,5,SkinH,0xFF00FF);
	::TransparentBlt(hDC,DestX+5,DestY,item.w-10,item.h,g_SkinDC,SrcX+5,SkinY,5,SkinH,0xFF00FF);
	::TransparentBlt(hDC,DestX+item.w-5,DestY,5,item.h,g_SkinDC,SrcX+SkinW-5,SkinY,5,SkinH,0xFF00FF);
	RECT txtRC;
	HFONT hOldFont;
	int icoY=(item.h-16)/2;
	int icoX=2;
	if(item.bSelect){
		txtRC=CRect(icoX+DestX+18,DestY,DestX+item.w-2,DestY+item.h);
		hOldFont=(HFONT)::SelectObject(hDC,(HGDIOBJ)g_hFont2);
	}else{
		txtRC=CRect(icoX+DestX+18,DestY+3,DestX+item.w-2,DestY+item.h);
		hOldFont=(HFONT)::SelectObject(hDC,(HGDIOBJ)g_hFont);
		icoY=icoY+2;
	}
	::DrawIconEx(hDC,DestX+icoX,DestY+icoY,item.hIcon,16,16,0,NULL,3);
	::DrawText(hDC,item.strName,item.strName.GetLength(),&txtRC,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS|DT_HIDEPREFIX);
	::SelectObject(hDC,(HGDIOBJ)hOldFont);
}

void CDirectTag::DrawEx()
{
	HDC hCacheDC=(HDC)::GetProp(hWnd,_T("Comet_CacheDC"));
	::StretchBlt(hCacheDC,x,y,nWidth,nHeight,hCacheDC,x-1,y,1,nHeight,SRCCOPY);
	Draw(hCacheDC);
	HDC hDC=GetDC(hWnd);
	BitBlt(hDC,x,y,nWidth,nHeight,hCacheDC,x,y,SRCCOPY);
	ReleaseDC(hWnd,hDC);
}
BOOL CDirectTag::MouseEvent(UINT msg, int nX,int nY)
{
	CString str;
	BOOL bRet=FALSE;
	RECT rc=CRect(x,y,x+nWidth,y+nHeight);
	POINT pt=CPoint(nX,nY);
	if (msg!=WM_MOUSELEAVE && PtInRect(&rc,pt))
	{
			bRet=TRUE;
	}
	//-------------------------------------
	if(!bRet){
		if(nOverIndex>-1){
			nOverIndex=-1;
			DrawEx();
		}
		return bRet;
	}
	//-------------------------------------
	int nIndex=-1;
	_TagItem  item;
	for(int i=0;i<m_nCount;i++)
	{
		item=m_ItemArray.GetAt(i);
		if(nX>=(x+item.x) && nX<=(x+item.x+item.w)){
			if(nY>=(y+item.y) && nY<=(y+item.y+item.h)){
				nIndex=i;
				break;
			}
		}
	}
	if (nIndex==-1 || nIndex==nSelIndx)
	{
		return bRet;
	}
	if(nIndex!=nOverIndex && msg==WM_MOUSEMOVE){
		if (nOverIndex!=-1)
		{
			item=m_ItemArray.GetAt(nOverIndex);
			item.bOver=FALSE;
			m_ItemArray.SetAt(nOverIndex,item);
			nOverIndex=-1;
		}
		if(nIndex!=nSelIndx)
		{
			nOverIndex=nIndex;
			item=m_ItemArray.GetAt(nOverIndex);
			item.bOver=TRUE;
			m_ItemArray.SetAt(nOverIndex,item);			
		}
		DrawEx();
		return bRet;
	}
	if(nIndex!=nSelIndx && msg==WM_LBUTTONDOWN){
		if (nSelIndx!=-1)
		{
			item=m_ItemArray.GetAt(nSelIndx);
			item.bOver=FALSE;
			item.bSelect=FALSE;
			m_ItemArray.SetAt(nSelIndx,item);
		}
		nSelIndx=nIndex;
		item=m_ItemArray.GetAt(nSelIndx);
		item.bSelect=TRUE;
		item.bOver=FALSE;
		m_ItemArray.SetAt(nSelIndx,item);
		DrawEx();
		return bRet;
	}
	return bRet;
}
void CDirectTag::OnClick(void)
{
	::ReleaseCapture ();
}