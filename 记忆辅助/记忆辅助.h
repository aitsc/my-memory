
// ���丨��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Gongju.h"


// C���丨��App: 
// �йش����ʵ�֣������ ���丨��.cpp
//

class C���丨��App : public CWinApp
{
public:
	C���丨��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C���丨��App theApp;
extern CGongju gongju;