// C�ƶ�����.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "C�ƶ�����.h"
#include "afxdialogex.h"


// C�ƶ����� �Ի���

IMPLEMENT_DYNAMIC(C�ƶ�����, CDialogEx)

C�ƶ�����::C�ƶ�����(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�ƶ�����::IDD, pParent)
{

}

C�ƶ�����::~C�ƶ�����()
{
}

void C�ƶ�����::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, box1);
	DDX_Control(pDX, IDC_COMBO2, box2);
}


BEGIN_MESSAGE_MAP(C�ƶ�����, CDialogEx)
	ON_BN_CLICKED(IDOK, &C�ƶ�����::OnBnClickedOk)
END_MESSAGE_MAP()


// C�ƶ����� ��Ϣ�������


BOOL C�ƶ�����::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString s;
	for (int i = 0; i < 64; i++)//���ڵķ�������Ͽ�
	{
		if (gongju.flqk[i].cunzai == 1)
		{
			s = gongju.flqk[i].name;
			box1.AddString(s);
			box2.AddString(s);
		}
	}
	box1.SetCurSel(0);//Ĭ��
	box2.SetCurSel(0);//Ĭ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void C�ƶ�����::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	char fenlei1 = 0, fenlei2 = 0;
	for (int i = 0, j = 0; i < 64; i++)//�ҵ��������
	{
		if (gongju.flqk[i].cunzai == 1)
		{
			if (box1.GetCurSel() == j) break;
			else j++;
		}
		fenlei1++;
	}
	for (int i = 0, j = 0; i < 64; i++)//�ҵ��������
	{
		if (gongju.flqk[i].cunzai == 1)
		{
			if (box2.GetCurSel() == j) break;
			else j++;
		}
		fenlei2++;
	}
	CString s;
	s.Format(L"�ɹ��ƶ���%d����Ŀ��", gongju.�ƶ�����(fenlei1, fenlei2));
	MessageBox(s);
	EndDialog(11);
}
