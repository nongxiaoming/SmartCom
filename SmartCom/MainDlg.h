#pragma once

#include "DirectControl.h"
#include "DirectTag.h"
#include "addredit.h"
// CMainDlg

class CMainDlg : public CWnd
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg();
	virtual ~CMainDlg();

protected:
	DECLARE_MESSAGE_MAP()
private:
	CString m_strClassName;
	int m_nWidth;
	int m_nHeight;
	CRect m_TitleRc;
	CRect m_ClientRc;
	CRect m_TagRect;
	CRect m_BarRect;
	CRect m_StatuRect;
	int m_BarTop;
	CRect m_WebRect;
	HCURSOR m_hCursor_Arrow;
	HCURSOR m_hCursor_SizeWE;
	HCURSOR m_hCursor_SizeNWSE;
	HBRUSH m_hbrBack;
	HICON m_MaxIcon;
	HICON m_MinIcon;
	HDC m_hCacheDC;
	HBITMAP m_hCacheBitmap;
	HBITMAP m_hOldCacheBitmap;
	CDirectControl m_MinBtn;
	CDirectControl m_MaxBtn;
	CDirectControl m_CloseBtn;
	CDirectControl m_MenuBtn;
	CDirectControl m_HelpBtn;
	CDirectControl m_MainBtn;
	//CDirectControl m_RetreatBtn;
	//CDirectControl m_ForwardBtn;
	//CDirectControl m_HistoryBtn1;
	//CDirectControl m_HistoryBtn2;
	//CDirectControl m_HomeBtn;
	//CDirectControl m_RefreshBtn;
	//CDirectControl m_FavoritesBtn;
	//CDirectTag m_Tag;
	BOOL m_bTracking;
public:	
	BOOL CreateDlg(void);
	void Show(void);
	void UpdateCache();
	void SetWndCursor(HCURSOR hCursor);
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnPaint();
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	BOOL DirectMouseEvent(UINT msg, int x, int y);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);	
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};


