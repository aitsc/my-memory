
// 记忆辅助Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "记忆辅助Dlg.h"
#include "afxdialogex.h"
#include "Cxiugaimingzi.h"
#include "Cxiugaimima.h"
#include "Cbianji.h"
#include "C分类情况.h"
#include "C关于说明.h"
#include "C卡片式.h"
#include "C选择分类.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// C记忆辅助Dlg 对话框

static int ScreenX = GetSystemMetrics(SM_CXSCREEN);//屏幕宽度
static int ScreenY = GetSystemMetrics(SM_CYSCREEN);//屏幕高度
enum
{
	DOCK_NONE,           //不停靠
	DOCK_TOP,           //停靠上边
	DOCK_LEFT,           //停靠左边
	DOCK_RIGHT           //停靠右边
};

C记忆辅助Dlg::C记忆辅助Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C记忆辅助Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DockMode = DOCK_NONE; //初始不需要收起
	m_bHide = false; //假代表未收起
}

void C记忆辅助Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C记忆辅助Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_MOVING()
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_USERtishi, Ontishi)
	ON_COMMAND(ID_32771, &C记忆辅助Dlg::Onxiugaimingzi)
	ON_COMMAND(ID_32772, &C记忆辅助Dlg::Onxiugaimima)
	ON_COMMAND(ID_32773, &C记忆辅助Dlg::Onchakanbianji)
	ON_COMMAND(ID_32775, &C记忆辅助Dlg::Onguanyu)
	ON_BN_CLICKED(IDC_BUTTON2, &C记忆辅助Dlg::OnBnClicked_Qiandao)
	ON_BN_CLICKED(IDOK, &C记忆辅助Dlg::OnBnClicked_Xuexi)
	ON_BN_CLICKED(IDCANCEL, &C记忆辅助Dlg::OnBnClicked_Fuxi)
	ON_BN_CLICKED(IDC_BUTTON1, &C记忆辅助Dlg::OnBnClicked_Fanxiang)
	ON_COMMAND(ID_32774, &C记忆辅助Dlg::Onfenleiqingkuang)
	ON_COMMAND(ID_32786, &C记忆辅助Dlg::Ondaochu)
	ON_WM_CREATE()
	ON_COMMAND(ID_32787, &C记忆辅助Dlg::On新建用户)
	ON_STN_CLICKED(IDC_STATIC3, &C记忆辅助Dlg::OnStnClicked_深入复习)
	ON_WM_NCLBUTTONDBLCLK()
END_MESSAGE_MAP()


// C记忆辅助Dlg 消息处理程序

BOOL C记忆辅助Dlg::OnInitDialog()
{	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	menu.LoadMenu(IDR_ZHUYAO);
	SetMenu(&menu);
	// TODO:  在此添加额外的初始化代码
	//GetMenu()->GetSubMenu(0)->DeleteMenu(ID_32786, MF_BYCOMMAND);
	shuaxin();
	gongju.BEI_FEN();//备份数据

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C记忆辅助Dlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	EndDialog(10); //关闭程序
	//CDialogEx::OnClose();
}

//刷新主界面
void C记忆辅助Dlg::shuaxin()
{
	//用户名刷新
	CString yhm = gongju.yhm;
	GetMenu()->DeleteMenu(1, MF_BYPOSITION);
	GetMenu()->AppendMenu(MF_ENABLED, ID_32776, yhm);
	DrawMenuBar();
	//标签天数刷新
	CString s;
	s.Format(L"今日已背项目：%d", gongju.fxjz[3]);
	GetDlgItem(IDC_STATIC6)->SetWindowText(s);
	s.Format(L"总记忆项目：%d", gongju.zjyxm);
	GetDlgItem(IDC_STATIC1)->SetWindowText(s);
	s.Format(L"已学习项目：%d", gongju.zjyxm - gongju.dxxxm);
	GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	s.Format(L"待复习项目：%d", gongju.dfxxm);
	GetDlgItem(IDC_STATIC3)->SetWindowText(s);
	s.Format(L"已掌握项目：%d", gongju.yzwxm);
	GetDlgItem(IDC_STATIC4)->SetWindowText(s);
	//签到情况刷新
	if (0 == gongju.lsj)
	{
		s.Format(L"请签到开始记忆之旅！");
		GetDlgItem(IDC_STATIC5)->SetWindowText(s);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	}
	else if (gongju.xtsj > gongju.lsj + 1)
	{
		s.Format(L"你已断签%d天！", gongju.xtsj - gongju.lsj - 1);
		GetDlgItem(IDC_STATIC5)->SetWindowText(s);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	}
	else
	{
		s.Format(L"您成功签到%d天！", gongju.lsj - gongju.fsj + 1);
		GetDlgItem(IDC_STATIC5)->SetWindowText(s);
		if (gongju.xtsj == gongju.lsj) GetDlgItem(IDC_BUTTON2)->EnableWindow(false);//当天已签到
		else GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	}
	//其他按钮刷新
	if (gongju.zjyxm < 15)//至少15个项目才能学习
	{
		s.Format(L"请在查看编辑内添加项目！");
		GetDlgItem(IDC_STATIC5)->SetWindowText(s);
		GetDlgItem(IDOK)->EnableWindow(false);
		GetDlgItem(IDCANCEL)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
		if (gongju.lsj>0 && gongju.xtsj > gongju.lsj) GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		else GetDlgItem(IDC_BUTTON2)->EnableWindow(false);//签过到的
	}
	else if (gongju.zjyxm == gongju.yzwxm)//全部掌握
	{
		s.Format(L"恭喜您全部学完！");
		GetDlgItem(IDC_STATIC5)->SetWindowText(s);
		GetDlgItem(IDOK)->EnableWindow(false);
		GetDlgItem(IDCANCEL)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	}
	else if (gongju.xtsj != gongju.lsj)//还未签到时
	{
		GetDlgItem(IDOK)->EnableWindow(false);
		GetDlgItem(IDCANCEL)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	}
	else //一般情况
	{
		if (0 == gongju.dxxxm) GetDlgItem(IDOK)->EnableWindow(false); //学完了
		else GetDlgItem(IDOK)->EnableWindow(true);
		if (0 == gongju.dfxxm) GetDlgItem(IDCANCEL)->EnableWindow(false);//复习完了
		else GetDlgItem(IDCANCEL)->EnableWindow(true);
		if (0 == gongju.dwfl[0][64]) GetDlgItem(IDC_BUTTON1)->EnableWindow(false);//无反向
		else GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	}
	PostMessage(WM_USERtishi, 0, 0);
}

LRESULT  C记忆辅助Dlg::Ontishi(WPARAM wParam, LPARAM lParam)
{
	Sleep(50);
	if (1 == gongju.yc)
	{
		MessageBox(L"你好久没签到了，注意坚持哦！");
		gongju.yc = 0;
	}
	else if (20 <= gongju.yc)
	{
		CString s;
		s.Format(L"数据可能存在损坏:%d", gongju.yc);
		MessageBox(s);
	}
	else if (0 != gongju.yc)
	{
		CString s;
		s.Format(L"数据存在异常:%d", gongju.yc);
		MessageBox(s);
		gongju.BEI_FEN();//运行中产生的异常
	}
	return 1;
}


void C记忆辅助Dlg::Onxiugaimingzi()
{
	// TODO:  在此添加命令处理程序代码
	Cxiugaimingzi xiugai;
	xiugai.yuanmz = gongju.yhm;
	if(11==xiugai.DoModal()) shuaxin();//修改完成 刷新
}


void C记忆辅助Dlg::Onxiugaimima()
{
	// TODO:  在此添加命令处理程序代码
	Cxiugaimima xiugai;
	xiugai.DoModal();
}


void C记忆辅助Dlg::Onchakanbianji()
{
	// TODO:  在此添加命令处理程序代码
	Cbianji xiugai;
	xiugai.DoModal();
	shuaxin();//刷新
}


void C记忆辅助Dlg::Onguanyu()
{
	// TODO:  在此添加命令处理程序代码
	C关于说明 dlg;
	dlg.DoModal();
}


void C记忆辅助Dlg::OnBnClicked_Qiandao()
{
	// TODO:  在此添加控件通知处理程序代码
	gongju.Qiandao();
	shuaxin();
}


void C记忆辅助Dlg::OnBnClicked_Xuexi()
{
	// TODO:  在此添加控件通知处理程序代码
	if (0 < gongju.dfxxm&&MessageBox(TEXT("复习还未完成，是否先去复习？"), TEXT("建议先复习"), MB_YESNO) == IDYES)
	{
		OnBnClicked_Fuxi();
		return;
	}
	gongju.buchongJydl();
	C卡片式 xuexi;
	ShowWindow(false);
	xuexi.卡片类型 = 0;
	xuexi.DoModal();
	ShowWindow(true);
	shuaxin();
}


void C记忆辅助Dlg::OnBnClicked_Fuxi()
{
	// TODO:  在此添加控件通知处理程序代码
	C卡片式 fuxi;
	ShowWindow(false);
	fuxi.卡片类型 = 1;
	fuxi.DoModal();
	ShowWindow(true);
	shuaxin();
}


void C记忆辅助Dlg::OnBnClicked_Fanxiang()
{
	// TODO:  在此添加控件通知处理程序代码
	if (gongju.dwfl[0][64] <= 0)
	{
		MessageBox(L"无项目可以反向！");
		return;
	}
	C选择分类 xz;
	xz.是反向 = 1;
	if (11 != xz.DoModal()) return;//未选择分类时
	gongju.反向初始化(xz.fenlei);
	C卡片式 fanxiang;
	ShowWindow(false);
	fanxiang.卡片类型 = 2;
	fanxiang.DoModal();
	gongju.反向数组[32704] = 0;
	ShowWindow(true);
	shuaxin();
}


void C记忆辅助Dlg::Onfenleiqingkuang()
{
	// TODO:  在此添加命令处理程序代码
	C分类情况 fenlei;
	fenlei.DoModal();
	shuaxin();//刷新
}


void C记忆辅助Dlg::Ondaochu()
{
	// TODO:  在此添加命令处理程序代码
	if (gongju.zjyxm <= 0)
	{
		MessageBox(L"无项目可以导出！");
		return;
	}
	C选择分类 xz;
	if (11 != xz.DoModal()) return;
	CFileDialog filedlg(false);
	filedlg.m_ofn.lpstrTitle = L"请选择保存位置";
	filedlg.m_ofn.lpstrFilter = L"文本文件(*.txt)\0*.txt\0\0";
	if (IDOK != filedlg.DoModal())
	{
		ShowWindow(false);   //保证焦点可以从保存对话框回来
		ShowWindow(true);
		return;
	}
	ShowWindow(false);
	ShowWindow(true);
	CString s = filedlg.GetPathName();
	if (lstrcmpi(s.Right(4), L".txt") != 0) //使得后缀名自动添加而不重复
		s += ".txt";
	if (0 == gongju.daochu(s, xz.fenlei))
		MessageBox(L"导出失败！");
}


void C记忆辅助Dlg::On新建用户()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog filedlg(false);
	FILE *fp;
	filedlg.m_ofn.lpstrTitle = L"新建数据库";
	filedlg.m_ofn.lpstrFilter = L"数据文件(*.ysj)\0*.ysj\0\0";
	if (IDOK != filedlg.DoModal())
	{
		ShowWindow(false);   //保证焦点可以从保存对话框回来
		ShowWindow(true);
		return;
	}
	ShowWindow(false);
	ShowWindow(true);
	CString s = filedlg.GetPathName();
	if (lstrcmpi(s.Right(4), L".ysj") != 0) //使得后缀名自动添加而不重复
		s += ".ysj";
	if (0 != _wfopen_s(&fp, s, L"wb+"))
	{
		MessageBox(L"新建失败！");
		return;
	}
	char c = 0;
	fwrite(L"谭不忘初心", 2, 5, fp);//写入标识头和默认用户名
	for (int i = 0, c = 0; i < 86; i++)
		fwrite(&c, 1, 1, fp);
	for (int i = 0, c = 0; i < 523264; i++)
		fwrite(&c, 1, 1, fp);
	for (int i = 0, c = 0; i < 2066; i++)
		fwrite(&c, 1, 1, fp);
	int a = 525430;
	fwrite(&a, 4, 1, fp);
	MessageBox(L"新建成功！");
}


void C记忆辅助Dlg::OnStnClicked_深入复习()
{
	// TODO:  在此添加控件通知处理程序代码
	if (gongju.dfxxm != 0 || gongju.fxlbt->biaoshi <= 0) return;
	if (MessageBox(TEXT("您确定要深入复习？"), TEXT("深入复习加深记忆"), MB_YESNO) == IDNO)
	{
		return;
	}
	C卡片式 srfuxi;
	ShowWindow(false);
	srfuxi.卡片类型 = 3;
	srfuxi.DoModal();
	ShowWindow(true);
	shuaxin();
}


void C记忆辅助Dlg::AnimateShowHide(BOOL bHide)
{
	if (m_DockMode == DOCK_NONE)
		return;
	m_bHide = bHide;
	const int borderWidth = 1;//留下的边缘
	RECT rc;
	GetWindowRect(&rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	//下边判断窗体该如何移动,由停靠方式决定
	int timesY = 9; //平移对话框的次数,如果你觉得不够平滑,可以增大该值.
	int timesX = 6;//横向
	int times = 0;
	int xStep, yStep;
	int xEnd, yEnd;
	switch (m_DockMode)
	{
	case DOCK_TOP:
	{
		//向上移藏
		xStep = 0;
		xEnd = rc.left;
		if (bHide)
		{
			yStep = -rc.bottom / timesY;
			yEnd = -height + borderWidth;
		}
		else//弹出
		{
			yStep = -rc.top / timesY;
			yEnd = 0;
		}
		times = timesY;
		break;
	}
	case DOCK_LEFT:
	{
		//向左移藏
		yStep = 0;
		yEnd = rc.top;
		if (bHide)
		{
			xStep = -rc.right / timesX;
			xEnd = -width + borderWidth;
		}
		else//弹出
		{
			xStep = -rc.left / timesX;
			xEnd = 0;
		}
		times = timesX;
		break;
	}
	case DOCK_RIGHT:
	{
		//向右移藏
		yStep = 0;
		yEnd = rc.top;
		if (bHide)
		{
			xStep = (ScreenX - rc.left) / timesX;
			xEnd = ScreenX - borderWidth;
		}
		else//弹出
		{
			xStep = (ScreenX - rc.right) / timesX;
			xEnd = ScreenX - width;
		}
		times = timesX;
		break;
	}
	default:
		_ASSERTE(FALSE);
	}
	//动画滚动窗体.
	for (int i = 0; i < times - 1; ++i)
	{
		rc.left += xStep;
		rc.top += yStep;
		MoveWindow(rc.left, rc.top, width, height, false);
		//SetWindowPos(NULL, rc.left, rc.top, 0, 0, SWP_NOSIZE | SWP_NOSENDCHANGING);
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

		Sleep(5);
	}
	SetWindowPos(NULL, xEnd, yEnd, 0, 0, SWP_NOSIZE);
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE); //贴边则置顶
}


void C记忆辅助Dlg::OnMoving(UINT nSide, LPRECT pRect)
{
	int juli = 14; //有效距离
	//自动收起
	if (pRect->top <= juli) //在上边有效距离内，自动靠拢。
	{
		m_DockMode = DOCK_TOP;
	}
	else if (pRect->left <= juli) //在左边有效距离内，自动靠拢。
	{
		m_DockMode = DOCK_LEFT;
	}
	else if (ScreenX - pRect->right <= juli) //在右边有效距离内，自动靠拢。
	{
		m_DockMode = DOCK_RIGHT;
	}
	else
	{
		m_DockMode = DOCK_NONE;
	}
	if (ScreenY < pRect->bottom)//太低不靠拢
	{
		m_DockMode = DOCK_NONE;
	}
	//越界检测
	if (pRect->top <= 0) //不能超过最上边
	{
		pRect->bottom -= pRect->top;
		pRect->top = 0;
	}
	if (pRect->left <= 0) //不能超过最左边
	{
		pRect->right -= pRect->left;
		pRect->left = 0;
	}
	if (pRect->right >= ScreenX) //不能超过最右边
	{
		pRect->left += (ScreenX - pRect->right);
		pRect->right = ScreenX;
	}
	if (m_DockMode != DOCK_NONE)
	{
		SetTimer(1, 50, NULL);
	}
	else
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); //不贴边则不置顶
		KillTimer(1);
	}
}


void C记忆辅助Dlg::OnTimer(UINT nIDEvent) //直接用于收起
{
	static int a = 0;
	if (m_DockMode != DOCK_NONE && nIDEvent == 1)
	{
		POINT pt;
		RECT rc;
		GetCursorPos(&pt);
		GetWindowRect(&rc);
		if (!PtInRect(&rc, pt))
		{
			Sleep(220); //防止鼠标误出去
			GetCursorPos(&pt);
			GetWindowRect(&rc);
			if (!PtInRect(&rc, pt))
			{
				AnimateShowHide(TRUE);
				KillTimer(1);
				a = 1;
			}
		}
		if (a)//回焦点
		{
//			ShowWindow(false);
//			ShowWindow(true);
			a = 0;
		}
	}
}


LRESULT C记忆辅助Dlg::OnNcHitTest(CPoint point)//直接用于弹出
{
	if (m_bHide)
	{
		AnimateShowHide(FALSE);
		if (m_DockMode != DOCK_NONE)
		{
			SetTimer(1, 50, NULL);
		}
	}
	//必须得调基类的对应函数，否则按关闭按钮，点击标题栏系统菜单，拖拽标题栏都没有响应。
	return CDialog::OnNcHitTest(point);
}

void C记忆辅助Dlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	EndDialog(0);//双击标题栏关闭
	CDialogEx::OnNcLButtonDblClk(nHitTest, point);
}
