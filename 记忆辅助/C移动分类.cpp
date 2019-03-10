// C移动分类.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "C移动分类.h"
#include "afxdialogex.h"


// C移动分类 对话框

IMPLEMENT_DYNAMIC(C移动分类, CDialogEx)

C移动分类::C移动分类(CWnd* pParent /*=NULL*/)
	: CDialogEx(C移动分类::IDD, pParent)
{

}

C移动分类::~C移动分类()
{
}

void C移动分类::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, box1);
	DDX_Control(pDX, IDC_COMBO2, box2);
}


BEGIN_MESSAGE_MAP(C移动分类, CDialogEx)
	ON_BN_CLICKED(IDOK, &C移动分类::OnBnClickedOk)
END_MESSAGE_MAP()


// C移动分类 消息处理程序


BOOL C移动分类::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString s;
	for (int i = 0; i < 64; i++)//存在的分类上组合框
	{
		if (gongju.flqk[i].cunzai == 1)
		{
			s = gongju.flqk[i].name;
			box1.AddString(s);
			box2.AddString(s);
		}
	}
	box1.SetCurSel(0);//默认
	box2.SetCurSel(0);//默认
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void C移动分类::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	char fenlei1 = 0, fenlei2 = 0;
	for (int i = 0, j = 0; i < 64; i++)//找到分类序号
	{
		if (gongju.flqk[i].cunzai == 1)
		{
			if (box1.GetCurSel() == j) break;
			else j++;
		}
		fenlei1++;
	}
	for (int i = 0, j = 0; i < 64; i++)//找到分类序号
	{
		if (gongju.flqk[i].cunzai == 1)
		{
			if (box2.GetCurSel() == j) break;
			else j++;
		}
		fenlei2++;
	}
	CString s;
	s.Format(L"成功移动了%d个项目！", gongju.移动分类(fenlei1, fenlei2));
	MessageBox(s);
	EndDialog(11);
}
