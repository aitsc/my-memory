// C分类情况.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "C分类情况.h"
#include "afxdialogex.h"
#include "Cxiugaimingzi.h"
#include "C增加分类.h"
#include "C移动分类.h"


// C分类情况 对话框

IMPLEMENT_DYNAMIC(C分类情况, CDialogEx)

C分类情况::C分类情况(CWnd* pParent /*=NULL*/)
	: CDialogEx(C分类情况::IDD, pParent)
{

}

C分类情况::~C分类情况()
{
}

void C分类情况::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(C分类情况, CDialogEx)
	ON_BN_CLICKED(IDOK1, &C分类情况::OnBnClicked_zhenjia)
	ON_BN_CLICKED(IDCANCEL1, &C分类情况::OnBnClicked_shanchu)
	ON_BN_CLICKED(IDC_BUTTON1, &C分类情况::OnBnClicked_xiugai)
	ON_BN_CLICKED(IDC_BUTTON2, &C分类情况::OnBnClicked_yidong)
END_MESSAGE_MAP()


// C分类情况 消息处理程序


BOOL C分类情况::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i = 0; i < 64; i++) listbiaoshi[i] = 0;//初始化列表标识
	SetMenu((menu.LoadMenu(IDR_LIST), &menu));//显示菜单栏
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//选择整行+网格线
	m_list.InsertColumn(0, L"序号", LVCFMT_LEFT, 37);
	m_list.InsertColumn(1, L"分类名", LVCFMT_LEFT, 300);
	m_list.InsertColumn(2, L"拥有项目数", LVCFMT_LEFT, 80);
	showlist();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


int C分类情况::showlist()
{
	m_list.DeleteAllItems();//清空列表防止重复
	int i, j;
	CString s;
	for (i = 0, j = 0; i < 64; i++)
	{
		if (1 == gongju.flqk[i].cunzai)
		{
			s.Format(L"%d", j + 1);
			m_list.InsertItem(j, s);
			m_list.SetItemText(j, 1, gongju.flqk[i].name);//分类名
			s.Format(L"%d", gongju.dwfl[0][i] + gongju.dwfl[1][i]);
			m_list.SetItemText(j, 2, s);//包涵项目数
			listbiaoshi[j] = i;
			j++;
		}
	}
	s.Format(L"（当前列表中共%d条分类）", j);
	GetMenu()->DeleteMenu(0, MF_BYPOSITION);
	GetMenu()->AppendMenu(MF_ENABLED, ID_qwe, s);
	DrawMenuBar();
	return 0;
}


void C分类情况::OnBnClicked_zhenjia()
{
	// TODO:  在此添加控件通知处理程序代码
	C增加分类 zenjia;
	zenjia.DoModal();
	showlist();
}


void C分类情况::OnBnClicked_shanchu()
{
	// TODO:  在此添加控件通知处理程序代码
	int i = m_list.GetSelectionMark();//获取位置
	if (-1 == i)
	{
		MessageBox(L"请选择一个分类！");
		return;
	}
	if (0 == i)
	{
		MessageBox(L"不可操作默认分类！");
		return;
	}
	CString s = L"您确定要删除分类 “";
	s = s + gongju.flqk[listbiaoshi[i]].name + L"”？";
	if (gongju.dwfl[0][listbiaoshi[i]] + gongju.dwfl[1][listbiaoshi[i]] > 0)
	{
		if (MessageBox(s, TEXT("这将删除该分类下的所有项目！"), MB_YESNO) == IDNO)
		{
			m_list.SetSelectionMark(-1);//重置位置
			return;
		}
		if (gongju.zjyxm >= 15 && gongju.dwfl[0][listbiaoshi[i]] + gongju.dwfl[1][listbiaoshi[i]] > gongju.zjyxm - 15)
		{
			MessageBox(L"总项目不可少于15！");
			return;
		}
	}
	gongju.shanchufenlei(listbiaoshi[i]);//删除分类
	showlist();
}


void C分类情况::OnBnClicked_xiugai()
{
	// TODO:  在此添加控件通知处理程序代码
	int i = m_list.GetSelectionMark();//获取位置
	if (-1 == i)
	{
		MessageBox(L"请选择一个分类！");
		return;
	}
	if (0 == i)
	{
		MessageBox(L"不可操作默认分类！");
		return;
	}
	Cxiugaimingzi xiugai;
	xiugai.fenlei = listbiaoshi[i];
	xiugai.yuanmz = gongju.flqk[listbiaoshi[i]].name;
	xiugai.xiugaifenlei = 1;
	xiugai.DoModal();
	showlist();
}


void C分类情况::OnBnClicked_yidong()
{
	// TODO:  在此添加控件通知处理程序代码
	C移动分类 yidong;
	yidong.DoModal();
	showlist();
}
