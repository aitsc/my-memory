// Cxiugaimima.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "Cxiugaimima.h"
#include "afxdialogex.h"


// Cxiugaimima 对话框

IMPLEMENT_DYNAMIC(Cxiugaimima, CDialogEx)

Cxiugaimima::Cxiugaimima(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cxiugaimima::IDD, pParent)
	, yuanmima(_T(""))
	, xinmima(_T(""))
	, querenmima(_T(""))
{

}

Cxiugaimima::~Cxiugaimima()
{
}

void Cxiugaimima::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, yuanmima);
	DDV_MaxChars(pDX, yuanmima, 10);
	DDX_Text(pDX, IDC_EDIT4, xinmima);
	DDV_MaxChars(pDX, xinmima, 10);
	DDX_Text(pDX, IDC_EDIT5, querenmima);
	DDV_MaxChars(pDX, querenmima, 10);
}


BEGIN_MESSAGE_MAP(Cxiugaimima, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cxiugaimima::OnBnClickedOk)
END_MESSAGE_MAP()


// Cxiugaimima 消息处理程序


void Cxiugaimima::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true); //编辑框到变量
	CString s1, s2, s3;
	s1.Format(L"%d", _ttoi(yuanmima));
	s2.Format(L"%d", _ttoi(xinmima));
	s3.Format(L"%d", _ttoi(querenmima));
	if (yuanmima != s1&&yuanmima != "" || xinmima != s2&&xinmima != "" || querenmima != s3&&querenmima != "")
	{
		MessageBox(L"密码只能包涵数字或不填！");
		yuanmima = "";
		xinmima = "";
		querenmima = "";
		UpdateData(false);
		return;
	}
	if (xinmima != querenmima)
	{
		MessageBox(L"新密码和确认密码输入不一致！");
		return;
	}
	int a;
	fseek(gongju.fp, 12, 0);
	fread(&a, 4, 1, gongju.fp);
	if (a < 0 && (a | 0x80000000) != (_ttoi(yuanmima)|0x80000000))
	{
		MessageBox(L"原密码错误！");
		yuanmima = "";
		UpdateData(false);
		return;
	}
	if ("" == xinmima)
	{
		a = 0;
		fseek(gongju.fp, 12, 0);
		fwrite(&a, 4, 1, gongju.fp);
	}
	else
	{
		a = _ttoi(xinmima) | 0x80000000;
		fseek(gongju.fp, 12, 0);
		fwrite(&a, 4, 1, gongju.fp);
	}
	EndDialog(11);
}
