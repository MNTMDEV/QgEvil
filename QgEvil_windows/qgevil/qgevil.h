
// qgevil.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CqgevilApp:
// �йش����ʵ�֣������ qgevil.cpp
//

class CqgevilApp : public CWinApp
{
public:
	CqgevilApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CqgevilApp theApp;