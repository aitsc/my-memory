// Czengaixiangmu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "Czengaixiangmu.h"
#include "afxdialogex.h"


// Czengaixiangmu �Ի���

IMPLEMENT_DYNAMIC(Czengaixiangmu, CDialogEx)

Czengaixiangmu::Czengaixiangmu(CWnd* pParent /*=NULL*/)
	: CDialogEx(Czengaixiangmu::IDD, pParent)
	, zengjia(0)
	, wenti(_T(""))
	, daan(_T(""))
	, biaozhi(0)
	, Ĭ�����ӷ���(0)
{

}

Czengaixiangmu::~Czengaixiangmu()
{
}

void Czengaixiangmu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, wenti);
	DDV_MaxChars(pDX, wenti, 900);
	DDX_Text(pDX, IDC_EDIT2, daan);
	DDV_MaxChars(pDX, daan, 900);
	DDX_Control(pDX, IDC_COMBO1, box);
}


BEGIN_MESSAGE_MAP(Czengaixiangmu, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &Czengaixiangmu::OnBnClicked_huhuan)
	ON_BN_CLICKED(IDOK, &Czengaixiangmu::OnBnClicked_Ok)
	ON_BN_CLICKED(IDCANCEL, &Czengaixiangmu::OnBnClicked_Cancel)
END_MESSAGE_MAP()


// Czengaixiangmu ��Ϣ�������


void Czengaixiangmu::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndDialog(10);
	//CDialogEx::OnClose();
}


BOOL Czengaixiangmu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString s;
	for (int i = 0, j = 0; i < 64; i++)//���ڵķ�������Ͽ�
	{
		if (gongju.flqk[i].cunzai == 1)
		{
			s = gongju.flqk[i].name;
			box.AddString(s);
			if (0 < biaozhi&&gongju.xmsj[biaozhi - 1].fenlei == i) box.SetCurSel(j);
			j++;
		}
	}
	if (zengjia)
	{
		SetWindowText(L"������Ŀ");
		box.SetCurSel(Ĭ�����ӷ���);//Ĭ��
	}
	else
	{
		wenti = gongju.xmsj[biaozhi - 1].wenti;
		daan = gongju.xmsj[biaozhi - 1].daan;
		UpdateData(false);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void Czengaixiangmu::OnBnClicked_huhuan()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CString s;
	s = wenti;
	wenti = daan;
	daan = s;
	UpdateData(false);
}


void Czengaixiangmu::OnBnClicked_Ok()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (wenti == "" || daan == "")
	{
		MessageBox(L"����ʹ𰸲���Ϊ�գ�");
		return;
	}
	char fenlei = 0;
	for (int i = 0, j = 0; i < 64; i++)//�ҵ��������
	{
		if (gongju.flqk[i].cunzai == 1)
		{
			if (box.GetCurSel() == j) break;
			else j++;
		}
		fenlei++;
	}
	if (zengjia)
	{
		if (0 >= gongju.tianjiaXiangmu(wenti, daan, fenlei))
		{
			EndDialog(10);
		}
		else
		{
			Ĭ�����ӷ��� = box.GetCurSel();
			EndDialog(11);
		}
		return;
	}
	if (0 != gongju.xmsj[biaozhi - 1].jieduan&&MessageBox(TEXT("���Ƿ�����ѧϰ����Ŀ��"), TEXT("��ʾ"), MB_YESNO) == IDNO)
	{
		if (0 >= gongju.xiugaiXiangmu(biaozhi, 0, wenti, daan, fenlei)) EndDialog(10);
		else EndDialog(11);
		return;
	}
	if (0 >= gongju.xiugaiXiangmu(biaozhi, 1, wenti, daan, fenlei)) EndDialog(10);
	else EndDialog(11);
}


void Czengaixiangmu::OnBnClicked_Cancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	EndDialog(10);
	//CDialogEx::OnCancel();
}
