// Czengaixiangmu.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "Czengaixiangmu.h"
#include "afxdialogex.h"


// Czengaixiangmu 对话框

IMPLEMENT_DYNAMIC(Czengaixiangmu, CDialogEx)

Czengaixiangmu::Czengaixiangmu(CWnd* pParent /*=NULL*/)
	: CDialogEx(Czengaixiangmu::IDD, pParent)
	, zengjia(0)
	, wenti(_T(""))
	, daan(_T(""))
	, biaozhi(0)
	, 默认增加分类(0)
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


// Czengaixiangmu 消息处理程序


void Czengaixiangmu::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	EndDialog(10);
	//CDialogEx::OnClose();
}


BOOL Czengaixiangmu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString s;
	for (int i = 0, j = 0; i < 64; i++)//存在的分类上组合框
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
		SetWindowText(L"增加项目");
		box.SetCurSel(默认增加分类);//默认
	}
	else
	{
		wenti = gongju.xmsj[biaozhi - 1].wenti;
		daan = gongju.xmsj[biaozhi - 1].daan;
		UpdateData(false);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void Czengaixiangmu::OnBnClicked_huhuan()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	CString s;
	s = wenti;
	wenti = daan;
	daan = s;
	UpdateData(false);
}


void Czengaixiangmu::OnBnClicked_Ok()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (wenti == "" || daan == "")
	{
		MessageBox(L"问题和答案不能为空！");
		return;
	}
	char fenlei = 0;
	for (int i = 0, j = 0; i < 64; i++)//找到分类序号
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
			默认增加分类 = box.GetCurSel();
			EndDialog(11);
		}
		return;
	}
	if (0 != gongju.xmsj[biaozhi - 1].jieduan&&MessageBox(TEXT("您是否重新学习该项目？"), TEXT("提示"), MB_YESNO) == IDNO)
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
	// TODO:  在此添加控件通知处理程序代码
	EndDialog(10);
	//CDialogEx::OnCancel();
}
