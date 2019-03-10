// C项目内容.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "C项目内容.h"
#include "afxdialogex.h"


// C项目内容 对话框

IMPLEMENT_DYNAMIC(C项目内容, CDialogEx)

C项目内容::C项目内容(CWnd* pParent /*=NULL*/)
	: CDialogEx(C项目内容::IDD, pParent)
	, wenti(_T(""))
	, daan(_T(""))
	, duan(-128)
{

}

C项目内容::~C项目内容()
{
}

void C项目内容::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, wenti);
	DDV_MaxChars(pDX, wenti, 900);
	DDX_Text(pDX, IDC_EDIT1, daan);
	DDV_MaxChars(pDX, daan, 900);
}


BEGIN_MESSAGE_MAP(C项目内容, CDialogEx)
END_MESSAGE_MAP()


// C项目内容 消息处理程序


BOOL C项目内容::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString s;
	s.Format(L"%d", duan);
	GetDlgItem(IDC_STATIC1)->SetWindowText(s);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
