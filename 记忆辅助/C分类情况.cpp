// C�������.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "C�������.h"
#include "afxdialogex.h"
#include "Cxiugaimingzi.h"
#include "C���ӷ���.h"
#include "C�ƶ�����.h"


// C������� �Ի���

IMPLEMENT_DYNAMIC(C�������, CDialogEx)

C�������::C�������(CWnd* pParent /*=NULL*/)
	: CDialogEx(C�������::IDD, pParent)
{

}

C�������::~C�������()
{
}

void C�������::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(C�������, CDialogEx)
	ON_BN_CLICKED(IDOK1, &C�������::OnBnClicked_zhenjia)
	ON_BN_CLICKED(IDCANCEL1, &C�������::OnBnClicked_shanchu)
	ON_BN_CLICKED(IDC_BUTTON1, &C�������::OnBnClicked_xiugai)
	ON_BN_CLICKED(IDC_BUTTON2, &C�������::OnBnClicked_yidong)
END_MESSAGE_MAP()


// C������� ��Ϣ�������


BOOL C�������::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	for (int i = 0; i < 64; i++) listbiaoshi[i] = 0;//��ʼ���б��ʶ
	SetMenu((menu.LoadMenu(IDR_LIST), &menu));//��ʾ�˵���
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//ѡ������+������
	m_list.InsertColumn(0, L"���", LVCFMT_LEFT, 37);
	m_list.InsertColumn(1, L"������", LVCFMT_LEFT, 300);
	m_list.InsertColumn(2, L"ӵ����Ŀ��", LVCFMT_LEFT, 80);
	showlist();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


int C�������::showlist()
{
	m_list.DeleteAllItems();//����б��ֹ�ظ�
	int i, j;
	CString s;
	for (i = 0, j = 0; i < 64; i++)
	{
		if (1 == gongju.flqk[i].cunzai)
		{
			s.Format(L"%d", j + 1);
			m_list.InsertItem(j, s);
			m_list.SetItemText(j, 1, gongju.flqk[i].name);//������
			s.Format(L"%d", gongju.dwfl[0][i] + gongju.dwfl[1][i]);
			m_list.SetItemText(j, 2, s);//������Ŀ��
			listbiaoshi[j] = i;
			j++;
		}
	}
	s.Format(L"����ǰ�б��й�%d�����ࣩ", j);
	GetMenu()->DeleteMenu(0, MF_BYPOSITION);
	GetMenu()->AppendMenu(MF_ENABLED, ID_qwe, s);
	DrawMenuBar();
	return 0;
}


void C�������::OnBnClicked_zhenjia()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	C���ӷ��� zenjia;
	zenjia.DoModal();
	showlist();
}


void C�������::OnBnClicked_shanchu()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i = m_list.GetSelectionMark();//��ȡλ��
	if (-1 == i)
	{
		MessageBox(L"��ѡ��һ�����࣡");
		return;
	}
	if (0 == i)
	{
		MessageBox(L"���ɲ���Ĭ�Ϸ��࣡");
		return;
	}
	CString s = L"��ȷ��Ҫɾ������ ��";
	s = s + gongju.flqk[listbiaoshi[i]].name + L"����";
	if (gongju.dwfl[0][listbiaoshi[i]] + gongju.dwfl[1][listbiaoshi[i]] > 0)
	{
		if (MessageBox(s, TEXT("�⽫ɾ���÷����µ�������Ŀ��"), MB_YESNO) == IDNO)
		{
			m_list.SetSelectionMark(-1);//����λ��
			return;
		}
		if (gongju.zjyxm >= 15 && gongju.dwfl[0][listbiaoshi[i]] + gongju.dwfl[1][listbiaoshi[i]] > gongju.zjyxm - 15)
		{
			MessageBox(L"����Ŀ��������15��");
			return;
		}
	}
	gongju.shanchufenlei(listbiaoshi[i]);//ɾ������
	showlist();
}


void C�������::OnBnClicked_xiugai()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i = m_list.GetSelectionMark();//��ȡλ��
	if (-1 == i)
	{
		MessageBox(L"��ѡ��һ�����࣡");
		return;
	}
	if (0 == i)
	{
		MessageBox(L"���ɲ���Ĭ�Ϸ��࣡");
		return;
	}
	Cxiugaimingzi xiugai;
	xiugai.fenlei = listbiaoshi[i];
	xiugai.yuanmz = gongju.flqk[listbiaoshi[i]].name;
	xiugai.xiugaifenlei = 1;
	xiugai.DoModal();
	showlist();
}


void C�������::OnBnClicked_yidong()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	C�ƶ����� yidong;
	yidong.DoModal();
	showlist();
}
