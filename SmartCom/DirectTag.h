#pragma once
#include "directcontrol.h"
#include "GlobalFunction.h"

class CDirectTag :
	public CDirectControl
{
public:
	CDirectTag(void);
public:
	~CDirectTag(void);
	CArray <_TagItem,_TagItem&> m_ItemArray;
public:
	int m_nCount;
	int nOverIndex;
	int nSelIndx;
	int ItemWidth;
	void AddItem(CString strName, HICON hIco=0, HWND hWndWeb=NULL);
	void UpdateSize();
public:
	void Move(int nX, int nY, int nW, int nH);
public:
	void Draw(HDC hDC);
	void DrawItem(HDC hDC, _TagItem item);
	void DrawEx();
	BOOL MouseEvent(UINT msg, int nX,int nY);
	void OnClick(void);
};
