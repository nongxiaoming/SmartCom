// CometBrowser.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCometBrowserApp:
// �йش����ʵ�֣������ CometBrowser.cpp
//

class CSmartComApp : public CWinApp
{
public:
	CSmartComApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSmartComApp theApp;