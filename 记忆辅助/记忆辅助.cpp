
// ���丨��.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "���丨��.h"
#include "���丨��Dlg.h"
#include "Cdenglu.h"
#include "Gongju.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C���丨��App

BEGIN_MESSAGE_MAP(C���丨��App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// C���丨��App ����

C���丨��App::C���丨��App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� C���丨��App ����

C���丨��App theApp;
CGongju gongju;

// C���丨��App ��ʼ��

BOOL C���丨��App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	AfxEnableControlContainer();
	HANDLE h;
	h = CreateMutex(NULL, false, L"7a431d32f3t");
	if (h)//��ֻ֤��һ����������
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			AfxMessageBox(L"��һ���������������У�");
			return FALSE;
		}
	}

	CCommandLineInfo cmdInfo;//�ļ�������ص���
	ParseCommandLine(cmdInfo);

	Cdenglu denglu;
	denglu.lujing = cmdInfo.m_strFileName;//��ȡ�ļ������򿪷�ʽ���ļ�·��
	if (denglu.DoModal() == 10)
	{
		return FALSE;//�˳�����
	}

	gongju.fp = denglu.fp; //�ļ����ݵݽ�
	gongju.lujing = denglu.lujing;
	gongju.chushihua();
	if (0 > gongju.yc)
	{
		if (gongju.yc == -1) AfxMessageBox(L"ϵͳʱ�����");
		else if (gongju.yc == -2) AfxMessageBox(L"ϵͳʱ�������");
		else if (gongju.yc == -3) AfxMessageBox(L"ʱ�䲻ƥ�䣡");
		else if (gongju.yc == -4) AfxMessageBox(L"�������");
		return FALSE;//�˳�����
	}

	C���丨��Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}
	gongju.��������();
	fclose(gongju.fp);
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

