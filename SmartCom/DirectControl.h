#pragma once

class CDirectControl
{
public:
	CDirectControl(void);
public:
	~CDirectControl(void);
public:
	int nWidth;
	int nHeight;
	int x;
	int y;
	int Type;
	bool Over;
	bool Down;
	int SkinX;
	int SkinY;
	HWND hWnd;
	int ID;
	HICON hIcon;
public:
	void Create(HWND hWndParent,int nX,int nY,int nW, int nH,int nSkinX, int nSkinY,int nID=NULL);
public:
	void Draw(HDC hDC);
	void DrawEx();
	BOOL MouseEvent(UINT msg, int nX,int nY);
public:
	void OnClick(void);
};
