
// GetDj97Music.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGetDj97MusicApp: 
// �йش����ʵ�֣������ GetDj97Music.cpp
//

class CGetDj97MusicApp : public CWinApp
{
public:
	CGetDj97MusicApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGetDj97MusicApp theApp;