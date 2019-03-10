// Cxiugaimingzi.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "Cxiugaimingzi.h"
#include "afxdialogex.h"


// Cxiugaimingzi 对话框

IMPLEMENT_DYNAMIC(Cxiugaimingzi, CDialogEx)

Cxiugaimingzi::Cxiugaimingzi(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cxiugaimingzi::IDD, pParent)
	, yuanmz(_T(""))
	, xinmz(_T(""))
	, xiugaifenlei(0)
	, fenlei(0)
{

}

Cxiugaimingzi::~Cxiugaimingzi()
{
}

void Cxiugaimingzi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, yuanmz);
	DDX_Text(pDX, IDC_EDIT4, xinmz);
	DDV_MaxChars(pDX, xinmz, 16);
}


BEGIN_MESSAGE_MAP(Cxiugaimingzi, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cxiugaimingzi::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Cxiugaimingzi::OnBnClickedCancel)
END_MESSAGE_MAP()


// Cxiugaimingzi 消息处理程序


void Cxiugaimingzi::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true); //编辑框到变量
	if (!xiugaifenlei)
	{
		if (1 == gongju.xiugaiYhm(xinmz)) EndDialog(11);
		else MessageBox(L"1到5个字,不含空格！");
	}
	else
	{
		if (1 == gongju.xiugaiFenleiming(fenlei, xinmz)) EndDialog(11);
		else MessageBox(L"1到16个字,不含空格！(非默认)");
	}
}


void Cxiugaimingzi::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}