// Cɸѡ.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "Cɸѡ.h"
#include "afxdialogex.h"


// Cɸѡ �Ի���

IMPLEMENT_DYNAMIC(Cɸѡ, CDialogEx)

Cɸѡ::Cɸѡ(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cɸѡ::IDD, pParent)
	, m_cjsj1(0)
	, m_cjsj2(CTime::GetCurrentTime())
	, shijianq(0)
	, shijianh(0)
	, fenlei(0)
	, zhuangtai(0)
{

}

Cɸѡ::~Cɸѡ()
{
}

void Cɸѡ::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_cjsj1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_cjsj2);
	//  DDX_Control(pDX, IDC_COMBOBOXEX1, fenleibox);
	//  DDX_Control(pDX, IDC_COMBOBOXEX2, zhuangtaibox);
	DDX_Control(pDX, IDC_COMBO1, fenleibox);
	DDX_Control(pDX, IDC_COMBO2, zhuangtaibox);
}


BEGIN_MESSAGE_MAP(Cɸѡ, CDialogEx)
	ON_BN_CLICKED(IDOK, &Cɸѡ::OnBnClicked_Ok)
END_MESSAGE_MAP()


// Cɸѡ ��Ϣ�������


BOOL Cɸѡ::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_cjsj1 = gongju.riqizhuanhua((short)shijianq, m_cjsj1);
	m_cjsj2 = gongju.riqizhuanhua((short)shijianh, m_cjsj1);
	UpdateData(false);
	CString s;
	fenleibox.AddString(L"ȫ��");
	fenleibox.SetCurSel(0);//Ĭ��ȫ��
	for (int i = 0, j = 0; i < 64; i++)//���ڵķ�������Ͽ�
	{
		if (gongju.flqk[i].cunzai == 1)
		{
			j++;
			s = gongju.flqk[i].name;
			fenleibox.AddString(s);
			if (fenlei == i) fenleibox.SetCurSel(j);
		}
	}
	zhuangtaibox.AddString(L"��ѧϰ");
	zhuangtaibox.AddString(L"������");
	zhuangtaibox.AddString(L"����ϰ");
	zhuangtaibox.AddString(L"ȫ��");
	zhuangtaibox.SetCurSel(zhuangtai);//Ĭ��ȫ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void Cɸѡ::OnBnClicked_Ok()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_cjsj1 > m_cjsj2)
	{
		MessageBox(L"ǰ��ʱ�䲻�ܴ��ں���ʱ�䣡");
		return;
	}
	shijianq = gongju.riqizhuanhua(m_cjsj1.GetYear(), m_cjsj1.GetMonth(), m_cjsj1.GetDay());
	shijianh = gongju.riqizhuanhua(m_cjsj2.GetYear(), m_cjsj2.GetMonth(), m_cjsj2.GetDay());
	fenlei = 0;
	for (int i = 0, j = 0; i < 64; i++)//�ҵ��������
	{
		if (gongju.flqk[i].cunzai == 1)
		{
			if (fenleibox.GetCurSel() - 1 == j) break;
			else j++;
		}
		fenlei++;
	}
	zhuangtai = zhuangtaibox.GetCurSel();
	EndDialog(11);
}
