// Cxiugaimingzi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "Cxiugaimingzi.h"
#include "afxdialogex.h"


// Cxiugaimingzi �Ի���

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


// Cxiugaimingzi ��Ϣ�������


void Cxiugaimingzi::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true); //�༭�򵽱���
	if (!xiugaifenlei)
	{
		if (1 == gongju.xiugaiYhm(xinmz)) EndDialog(11);
		else MessageBox(L"1��5����,�����ո�");
	}
	else
	{
		if (1 == gongju.xiugaiFenleiming(fenlei, xinmz)) EndDialog(11);
		else MessageBox(L"1��16����,�����ո�(��Ĭ��)");
	}
}


void Cxiugaimingzi::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}