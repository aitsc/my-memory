// C��Ŀ����.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "C��Ŀ����.h"
#include "afxdialogex.h"


// C��Ŀ���� �Ի���

IMPLEMENT_DYNAMIC(C��Ŀ����, CDialogEx)

C��Ŀ����::C��Ŀ����(CWnd* pParent /*=NULL*/)
	: CDialogEx(C��Ŀ����::IDD, pParent)
	, wenti(_T(""))
	, daan(_T(""))
	, duan(-128)
{

}

C��Ŀ����::~C��Ŀ����()
{
}

void C��Ŀ����::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, wenti);
	DDV_MaxChars(pDX, wenti, 900);
	DDX_Text(pDX, IDC_EDIT1, daan);
	DDV_MaxChars(pDX, daan, 900);
}


BEGIN_MESSAGE_MAP(C��Ŀ����, CDialogEx)
END_MESSAGE_MAP()


// C��Ŀ���� ��Ϣ�������


BOOL C��Ŀ����::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString s;
	s.Format(L"%d", duan);
	GetDlgItem(IDC_STATIC1)->SetWindowText(s);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
