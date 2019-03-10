// C卡片式.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "C卡片式.h"
#include "afxdialogex.h"
#include "Czengaixiangmu.h"
#define 点亮记住了时间 500

// C卡片式 对话框

static int ScreenX = GetSystemMetrics(SM_CXSCREEN);//屏幕宽度
static int ScreenY = GetSystemMetrics(SM_CYSCREEN);//屏幕高度
IMPLEMENT_DYNAMIC(C卡片式, CDialogEx)

C卡片式::C卡片式(CWnd* pParent /*=NULL*/)
	: CDialogEx(C卡片式::IDD, pParent)
	, wenti(_T(""))
	, daan(_T(""))
	, 卡片类型(0)
	, keyi(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

C卡片式::~C卡片式()
{
}

void C卡片式::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, wenti);
	DDV_MaxChars(pDX, wenti, 900);
	DDX_Text(pDX, IDC_EDIT1, daan);
	DDV_MaxChars(pDX, daan, 900);
}


BEGIN_MESSAGE_MAP(C卡片式, CDialogEx)
	ON_WM_MOVING()
	ON_BN_CLICKED(IDOK1, &C卡片式::OnBnClicked_jizhule)
	ON_BN_CLICKED(IDCANCEL1, &C卡片式::OnBnClicked_wangjile)
	ON_BN_CLICKED(IDC_BUTTON1, &C卡片式::OnBnClicked_huoqudaan)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_COMMAND(IDCANCEL, &C卡片式::OnIdcancel)
	ON_COMMAND(ID_32776, &C卡片式::On修改项目)
	ON_COMMAND(ID_32777, &C卡片式::On删除项目)
	ON_COMMAND(ID_32778, &C卡片式::On重学)
	ON_WM_NCLBUTTONDBLCLK()
END_MESSAGE_MAP()


// C卡片式 消息处理程序


BOOL C卡片式::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);//显示任务栏图标
	SetMenu((menu.LoadMenu(IDR_KAPIAN), &menu));//显示菜单栏
	CEdit *m_EditAa = (CEdit *)GetDlgItem(IDC_EDIT4);     //关联控件A
	CEdit *m_EditBb = (CEdit *)GetDlgItem(IDC_EDIT1);     //关联控件B
	font.CreatePointFont(105, L"黑体");     //选择字体
	//m_EditAa->SetFont(&font);
	//m_EditBb->SetFont(&font);
	//GetDlgItem(IDC_BUTTON1)->SetFont(&font);
	if (卡片类型 == 0) SetWindowText(L"学习卡片");
	if (卡片类型 == 1) SetWindowText(L"复习卡片");
	if (卡片类型 == 2)
	{
		menu.EnableMenuItem(ID_32776, MF_BYCOMMAND | MF_DISABLED);
		menu.EnableMenuItem(ID_32777, MF_BYCOMMAND | MF_DISABLED);
		menu.EnableMenuItem(ID_32778, MF_BYCOMMAND | MF_DISABLED);
		SetWindowText(L"反向卡片");
	}
	if (卡片类型 == 3) SetWindowText(L"深入复习卡片");
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);//保证窗口在最前面
	shuaxin();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void C卡片式::OnBnClicked_jizhule()
{
	// TODO:  在此添加控件通知处理程序代码
	if (卡片类型 == 0)
	{
		gongju.学习一个(1);
	}
	else if (卡片类型 == 1)
	{
		gongju.复习一个(1);
	}
	else if (卡片类型 == 2)
	{
		gongju.反向一个(1);
	}
	else if (卡片类型 == 3)
	{
		gongju.dfxxm = 1;
		gongju.复习一个(1);
	}
	shuaxin();
}


void C卡片式::OnBnClicked_wangjile()
{
	// TODO:  在此添加控件通知处理程序代码
	if (卡片类型 == 0)
	{
		if (gongju.jydl[0].biaoshi > 0)//填充反过来
		{
			GetDlgItem(IDC_STATIC2)->SetWindowText(L"0");
			daan = gongju.xmsj[gongju.jydl[0].biaoshi - 1].daan;
		}
		else
		{
			daan = gongju.xmsj[-gongju.jydl[0].biaoshi - 1].wenti;
		}
		UpdateData(false);
		gongju.学习一个(0);
	}
	else if (卡片类型 == 1)
	{
		CString s;
		if (gongju.fxlbt->next->pingyancishu == 126)
		{
			s.Format(L"%d", gongju.fxlbt->next->pingyancishu);
		}
		else
		{
			s.Format(L"%d", gongju.fxlbt->next->pingyancishu + 1);
		}
		GetDlgItem(IDC_STATIC2)->SetWindowText(s);//刷新标签
		daan = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].daan;
		UpdateData(false);
		gongju.复习一个(0);
	}
	else if (卡片类型 == 2)
	{
		daan = gongju.xmsj[gongju.反向数组[0] - 1].wenti;
		UpdateData(false);
		gongju.反向一个(0);
	}
	else if (卡片类型 == 3)
	{
		daan = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].daan;
		UpdateData(false);
		gongju.dfxxm = 1;
		gongju.复习一个(0);
		gongju.dfxxm = 0;
	}
	if (卡片类型 != 2) //忘记了菜单不可用
	{
		menu.EnableMenuItem(ID_32776, MF_BYCOMMAND | MF_DISABLED);
		menu.EnableMenuItem(ID_32777, MF_BYCOMMAND | MF_DISABLED);
		menu.EnableMenuItem(ID_32778, MF_BYCOMMAND | MF_DISABLED);
	}
	keyi = 0;
	GetDlgItem(IDOK1)->EnableWindow(false);
	GetDlgItem(IDCANCEL1)->EnableWindow(false);
	SetDlgItemText(IDC_BUTTON1, _T("下一个"));
}


void C卡片式::OnBnClicked_huoqudaan()
{
	// TODO:  在此添加控件通知处理程序代码
	CString s;
	GetDlgItemText(GetFocus()->GetDlgCtrlID(), s);
	if (s == _T("下一个"))
	{
		shuaxin();
		if (卡片类型 != 2) //下一个菜单可用
		{
			menu.EnableMenuItem(ID_32776, MF_BYCOMMAND | MF_ENABLED);
			menu.EnableMenuItem(ID_32777, MF_BYCOMMAND | MF_ENABLED);
			menu.EnableMenuItem(ID_32778, MF_BYCOMMAND | MF_ENABLED);
		}
		return;
	}
	if (卡片类型 == 0)
	{
		if (gongju.jydl[0].biaoshi > 0)//填充反过来
		{
			daan = gongju.xmsj[gongju.jydl[0].biaoshi - 1].daan;
		}
		else
		{
			daan = gongju.xmsj[-gongju.jydl[0].biaoshi - 1].wenti;
		}
	}
	else if (卡片类型 == 1)
	{
		daan = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].daan;
	}
	else if (卡片类型 == 2)
	{
		daan = gongju.xmsj[gongju.反向数组[0] - 1].wenti;
	}
	else if (卡片类型 == 3)
	{
		daan = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].daan;
	}
	keyi = 0;
	UpdateData(false);
	GetDlgItem(IDOK1)->EnableWindow(true);
}


int C卡片式::shuaxin()//要显示下一个项目时才需要刷新
{
	//完成情况检测
	if (卡片类型 == 0)
	{
		if (0 >= gongju.dlyxs)
		{
			if (MessageBox(TEXT("是否开始下一组学习？"), TEXT("完成一组学习"), MB_YESNO) == IDNO)
			{
				EndDialog(11);
				return 0;
			}
			gongju.buchongJydl();
		}
		if (0 >= gongju.dxxxm)
		{
			MessageBox(L"已全部完成！");
			EndDialog(11);
			return 0;
		}
		if (0 == gongju.jydl[0].biaoshi) gongju.buchongJydl();
	}
	else if (卡片类型 == 1)
	{
		if (0 >= gongju.dfxxm)
		{
			MessageBox(L"恭喜复习完成！");
			EndDialog(11);
			return 0;
		}
	}
	else if (卡片类型 == 2)
	{
		if (0 >= gongju.反向数组[32704])
		{
			MessageBox(L"全部完成！");
			EndDialog(11);
			return 0;
		}
	}
	else if (卡片类型 == 3)
	{
		if (0 >= gongju.fxlbt->biaoshi)
		{
			MessageBox(L"恭喜深入复习完成！");
			EndDialog(11);
			return 0;
		}
	}
	CString s;
	//分类刷新
	if (卡片类型 == 0)
	{
		s = gongju.flqk[gongju.xmsj[abs(gongju.jydl[0].biaoshi) - 1].fenlei].name;
		GetMenu()->DeleteMenu(1, MF_BYPOSITION);
		GetMenu()->AppendMenu(MF_ENABLED, ID_32779, s);
		DrawMenuBar();
	}
	else if (卡片类型 == 1)
	{
		s = gongju.flqk[gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].fenlei].name;
		GetMenu()->DeleteMenu(1, MF_BYPOSITION);
		GetMenu()->AppendMenu(MF_ENABLED, ID_32779, s);
		DrawMenuBar();
	}
	else if (卡片类型 == 2)
	{
		s = gongju.flqk[gongju.xmsj[gongju.反向数组[0] - 1].fenlei].name;
		GetMenu()->DeleteMenu(1, MF_BYPOSITION);
		GetMenu()->AppendMenu(MF_ENABLED, ID_32779, s);
		DrawMenuBar();
	}
	else if (卡片类型 == 3)
	{
		s = gongju.flqk[gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].fenlei].name;
		GetMenu()->DeleteMenu(1, MF_BYPOSITION);
		GetMenu()->AppendMenu(MF_ENABLED, ID_32779, s);
		DrawMenuBar();
	}
	//标签刷新
	if (卡片类型 == 0)
	{
		s.Format(L"本组剩余学习个数：%d", gongju.dlyxs);
		GetDlgItem(IDC_STATIC1)->SetWindowText(s);
		if (gongju.jydl[0].biaoshi>0) s.Format(L"%d", gongju.jydl[0].lianxucishu);
		else s.Format(L"%d", -1);
		GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	}
	else if (卡片类型 == 1)
	{
		s.Format(L"剩余复习个数：%d", gongju.dfxxm);
		GetDlgItem(IDC_STATIC1)->SetWindowText(s);
		s.Format(L"%d", gongju.fxlbt->next->pingyancishu);
		GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	}
	else if (卡片类型 == 2)
	{
		s.Format(L"从%d个项目中随机抽取学习", gongju.反向数组[32704]);
		GetDlgItem(IDC_STATIC1)->SetWindowText(s);
		s = "";
		GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	}
	else if (卡片类型 == 3)
	{
		s.Format(L"剩余可深入复习个数：%d", gongju.fxlbt->biaoshi);
		GetDlgItem(IDC_STATIC1)->SetWindowText(s);
		s.Format(L"%d", gongju.fxlbt->next->pingyancishu);
		GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	}
	//内容刷新
	if (卡片类型 == 0)
	{
		if (gongju.jydl[0].biaoshi > 0)//填充反过来
		{
			wenti = gongju.xmsj[gongju.jydl[0].biaoshi - 1].wenti;
			daan = "";
		}
		else
		{
			wenti = gongju.xmsj[-gongju.jydl[0].biaoshi - 1].daan;
			daan = "";
		}
	}
	else if (卡片类型 == 1)
	{
		wenti = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].wenti;
		daan = "";
	}
	else if (卡片类型 == 2)
	{
		wenti = gongju.xmsj[gongju.反向数组[0] - 1].daan;
		daan = "";
	}
	else if (卡片类型 == 3)
	{
		wenti = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].wenti;
		daan = "";
	}
	UpdateData(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDCANCEL1)->EnableWindow(true);
	SetDlgItemText(IDC_BUTTON1, _T("获取答案"));
	GetDlgItem(IDOK1)->EnableWindow(false);//按钮暂时不可用
	SetTimer(1, 点亮记住了时间, NULL);
	//SetTimer(1, 1, NULL);
	keyi = 1;
	return 1;
}


void C卡片式::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (1 == nIDEvent&&keyi)
	{
		GetDlgItem(IDOK1)->EnableWindow(true);
		keyi = 0;
	}
	KillTimer(nIDEvent);
	CDialogEx::OnTimer(nIDEvent);
}


void C卡片式::OnIdcancel()
{
	// TODO:  在此添加命令处理程序代码
	if (卡片类型 == 1 &&  MessageBox(TEXT("您确定现在退出？"), TEXT("还未复习完！"), MB_YESNO) == IDNO)
	{
		return;
	}
	EndDialog(11);
}


void C卡片式::On修改项目()
{
	// TODO:  在此添加命令处理程序代码
	Czengaixiangmu xiugai;
	xiugai.zengjia = 0;
	if (卡片类型 == 0)
	{
		xiugai.biaozhi = abs(gongju.jydl[0].biaoshi);
	}
	else if (卡片类型 == 1)
	{
		xiugai.biaozhi = gongju.fxlbt->next->biaoshi;
	}
	else if (卡片类型 == 2)
	{
	}
	else if (卡片类型 == 3)
	{
		xiugai.biaozhi = gongju.fxlbt->next->biaoshi;
	}
	if (0 != xiugai.biaozhi && 11 == xiugai.DoModal())
	{
		shuaxin();
	}
}


void C卡片式::On删除项目()
{
	// TODO:  在此添加命令处理程序代码
	if (15 == gongju.zjyxm)
	{
		MessageBox(L"项目不能在15个以下！");
		return;
	}
	if (MessageBox(TEXT("您确定要删除这条记录？"), TEXT("删除"), MB_YESNO) == IDNO)
	{
		return;
	}
	int biaoshi = 0;
	if (卡片类型 == 0)
	{
		biaoshi = abs(gongju.jydl[0].biaoshi);
	}
	else if (卡片类型 == 1)
	{
		biaoshi = gongju.fxlbt->next->biaoshi;
	}
	else if (卡片类型 == 2)
	{
	}
	else if (卡片类型 == 3)
	{
		biaoshi = gongju.fxlbt->next->biaoshi;
	}
	if (0 != biaoshi && 1 == gongju.shanchuXiangmu(biaoshi))
	{
		shuaxin();
	}
}


void C卡片式::On重学()//重学一个当前学习组减少一个，不管刷新后重学后的又回到队列中
{
	// TODO:  在此添加命令处理程序代码
	if (MessageBox(TEXT("您确定要重学此项目？"), TEXT("重学项目"), MB_YESNO) == IDNO)
	{
		return;
	}
	int biaoshi = 0;
	CString wenti0, daan0;
	char fenlei0;
	if (卡片类型 == 0)
	{
		biaoshi = abs(gongju.jydl[0].biaoshi);
	}
	else if (卡片类型 == 1)
	{
		biaoshi = gongju.fxlbt->next->biaoshi;
	}
	else if (卡片类型 == 2)
	{
	}
	else if (卡片类型 == 3)
	{
		biaoshi = gongju.fxlbt->next->biaoshi;
	}
	if (0 != biaoshi)
	{
		wenti0 = gongju.xmsj[biaoshi - 1].wenti;
		daan0 = gongju.xmsj[biaoshi - 1].daan;
		fenlei0 = gongju.xmsj[biaoshi - 1].fenlei;
		if (0 < gongju.xiugaiXiangmu(biaoshi, 1, wenti0, daan0, fenlei0))
		{
			shuaxin();
		}
	}
}

void C卡片式::OnMoving(UINT nSide, LPRECT pRect)
{
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
	if (pRect->bottom >= ScreenY) //不能超过最下边
	{
		pRect->top += (ScreenY - pRect->bottom);
		pRect->bottom = ScreenY;
	}
}

void C卡片式::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);//最小化窗口
	CDialogEx::OnNcLButtonDblClk(nHitTest, point);
}
