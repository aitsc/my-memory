
// 记忆辅助.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "记忆辅助Dlg.h"
#include "Cdenglu.h"
#include "Gongju.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C记忆辅助App

BEGIN_MESSAGE_MAP(C记忆辅助App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// C记忆辅助App 构造

C记忆辅助App::C记忆辅助App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 C记忆辅助App 对象

C记忆辅助App theApp;
CGongju gongju;

// C记忆辅助App 初始化

BOOL C记忆辅助App::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	AfxEnableControlContainer();
	HANDLE h;
	h = CreateMutex(NULL, false, L"7a431d32f3t");
	if (h)//保证只有一个程序运行
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			AfxMessageBox(L"有一个程序正在运行中！");
			return FALSE;
		}
	}

	CCommandLineInfo cmdInfo;//文件关联相关的类
	ParseCommandLine(cmdInfo);

	Cdenglu denglu;
	denglu.lujing = cmdInfo.m_strFileName;//获取文件关联打开方式的文件路径
	if (denglu.DoModal() == 10)
	{
		return FALSE;//退出程序
	}

	gongju.fp = denglu.fp; //文件数据递交
	gongju.lujing = denglu.lujing;
	gongju.chushihua();
	if (0 > gongju.yc)
	{
		if (gongju.yc == -1) AfxMessageBox(L"系统时间错误！");
		else if (gongju.yc == -2) AfxMessageBox(L"系统时间溢出！");
		else if (gongju.yc == -3) AfxMessageBox(L"时间不匹配！");
		else if (gongju.yc == -4) AfxMessageBox(L"意外错误！");
		return FALSE;//退出程序
	}

	C记忆辅助Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}
	gongju.重新整理();
	fclose(gongju.fp);
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

