// C���ӷ���.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "C���ӷ���.h"
#include "afxdialogex.h"


// C���ӷ��� �Ի���

IMPLEMENT_DYNAMIC(C���ӷ���, CDialogEx)

C���ӷ���::C���ӷ���(CWnd* pParent /*=NULL*/)
	: CDialogEx(C���ӷ���::IDD, pParent)
	, name(_T(""))
{

}

C���ӷ���::~C���ӷ���()
{
}

void C���ӷ���::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, name);
	DDV_MaxChars(pDX, name, 16);
}


BEGIN_MESSAGE_MAP(C���ӷ���, CDialogEx)
	ON_BN_CLICKED(IDOK, &C���ӷ���::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &C���ӷ���::OnBnClickedCancel)
END_MESSAGE_MAP()


// C���ӷ��� ��Ϣ�������


void C���ӷ���::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true); //�༭�򵽱���
	if (1 == gongju.tianjiaFenlei(name)) EndDialog(11);
	else if (-1 == gongju.tianjiaFenlei(name))
	{
		MessageBox(L"������������");
		EndDialog(10);
	}
	else MessageBox(L"1��16����,�����ո�(��Ĭ��)");
}


void C���ӷ���::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
