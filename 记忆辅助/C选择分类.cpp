// Cѡ�����.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "Cѡ�����.h"
#include "afxdialogex.h"


// Cѡ����� �Ի���

IMPLEMENT_DYNAMIC(Cѡ�����, CDialogEx)

Cѡ�����::Cѡ�����(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cѡ�����::IDD, pParent)
	, fenlei(0)
	, �Ƿ���(0)
{

}

Cѡ�����::~Cѡ�����()
{
}

void Cѡ�����::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, fenleibox);
}


BEGIN_MESSAGE_MAP(Cѡ�����, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cѡ�����::OnBnClickedOk)
END_MESSAGE_MAP()


// Cѡ����� ��Ϣ�������


void Cѡ�����::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	fenlei = 0;
	if (!�Ƿ���)
	{
		for (int i = 0, j = 0; i < 64; i++)//�ҵ��������
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
		for (int i = 0, j = 0; i < 64; i++)//�ҵ��������
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


BOOL Cѡ�����::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString s;
	fenleibox.AddString(L"ȫ��");
	fenleibox.SetCurSel(0);//Ĭ��ȫ��
	if (!�Ƿ���)
	{
		for (int i = 0, j = 0; i < 64; i++)//���ڵķ�������Ͽ�
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
		SetWindowText(L"��ѡ����ѧϰ�ķ��ࣺ");
		for (int i = 0, j = 0; i < 64; i++)//���ڵķ�������Ͽ�
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
	// �쳣:  OCX ����ҳӦ���� FALSE
}
