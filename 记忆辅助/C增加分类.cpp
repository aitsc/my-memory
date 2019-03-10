// C增加分类.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "C增加分类.h"
#include "afxdialogex.h"


// C增加分类 对话框

IMPLEMENT_DYNAMIC(C增加分类, CDialogEx)

C增加分类::C增加分类(CWnd* pParent /*=NULL*/)
	: CDialogEx(C增加分类::IDD, pParent)
	, name(_T(""))
{

}

C增加分类::~C增加分类()
{
}

void C增加分类::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, name);
	DDV_MaxChars(pDX, name, 16);
}


BEGIN_MESSAGE_MAP(C增加分类, CDialogEx)
	ON_BN_CLICKED(IDOK, &C增加分类::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C增加分类::OnBnClickedCancel)
END_MESSAGE_MAP()


// C增加分类 消息处理程序


void C增加分类::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true); //编辑框到变量
	if (1 == gongju.tianjiaFenlei(name)) EndDialog(11);
	else if (-1 == gongju.tianjiaFenlei(name))
	{
		MessageBox(L"分类数已满！");
		EndDialog(10);
	}
	else MessageBox(L"1到16个字,不含空格！(非默认)");
}


void C增加分类::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
