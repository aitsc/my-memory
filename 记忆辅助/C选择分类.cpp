// C选择分类.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "C选择分类.h"
#include "afxdialogex.h"


// C选择分类 对话框

IMPLEMENT_DYNAMIC(C选择分类, CDialogEx)

C选择分类::C选择分类(CWnd* pParent /*=NULL*/)
	: CDialogEx(C选择分类::IDD, pParent)
	, fenlei(0)
	, 是反向(0)
{

}

C选择分类::~C选择分类()
{
}

void C选择分类::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, fenleibox);
}


BEGIN_MESSAGE_MAP(C选择分类, CDialogEx)
	ON_BN_CLICKED(IDOK, &C选择分类::OnBnClickedOk)
END_MESSAGE_MAP()


// C选择分类 消息处理程序


void C选择分类::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	fenlei = 0;
	if (!是反向)
	{
		for (int i = 0, j = 0; i < 64; i++)//找到分类序号
		{
			if (gongju.flqk[i].cunzai == 1 && gongju.dwfl[0][i] + gongju.dwfl[1][i]>0)
			{
				if (fenleibox.GetCurSel() - 1 == j) break;
				else j++;
			}
			fenlei++;
		}
	}
	else
	{
		for (int i = 0, j = 0; i < 64; i++)//找到分类序号
		{
			if (gongju.flqk[i].cunzai == 1 && gongju.dwfl[0][i] > 0)
			{
				if (fenleibox.GetCurSel() - 1 == j) break;
				else j++;
			}
			fenlei++;
		}
	}
	EndDialog(11);
}


BOOL C选择分类::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString s;
	fenleibox.AddString(L"全部");
	fenleibox.SetCurSel(0);//默认全部
	if (!是反向)
	{
		for (int i = 0, j = 0; i < 64; i++)//存在的分类上组合框
		{
			if (gongju.flqk[i].cunzai == 1 && gongju.dwfl[0][i] + gongju.dwfl[1][i]>0)
			{
				j++;
				s = gongju.flqk[i].name;
				fenleibox.AddString(s);
			}
		}
	}
	else
	{
		SetWindowText(L"请选择反向学习的分类：");
		for (int i = 0, j = 0; i < 64; i++)//存在的分类上组合框
		{
			if (gongju.flqk[i].cunzai == 1 && gongju.dwfl[0][i] > 0)
			{
				j++;
				s = gongju.flqk[i].name;
				fenleibox.AddString(s);
			}
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
