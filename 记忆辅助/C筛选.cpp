// C筛选.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "C筛选.h"
#include "afxdialogex.h"


// C筛选 对话框

IMPLEMENT_DYNAMIC(C筛选, CDialogEx)

C筛选::C筛选(CWnd* pParent /*=NULL*/)
	: CDialogEx(C筛选::IDD, pParent)
	, m_cjsj1(0)
	, m_cjsj2(CTime::GetCurrentTime())
	, shijianq(0)
	, shijianh(0)
	, fenlei(0)
	, zhuangtai(0)
{

}

C筛选::~C筛选()
{
}

void C筛选::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_cjsj1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_cjsj2);
	//  DDX_Control(pDX, IDC_COMBOBOXEX1, fenleibox);
	//  DDX_Control(pDX, IDC_COMBOBOXEX2, zhuangtaibox);
	DDX_Control(pDX, IDC_COMBO1, fenleibox);
	DDX_Control(pDX, IDC_COMBO2, zhuangtaibox);
}


BEGIN_MESSAGE_MAP(C筛选, CDialogEx)
	ON_BN_CLICKED(IDOK, &C筛选::OnBnClicked_Ok)
END_MESSAGE_MAP()


// C筛选 消息处理程序


BOOL C筛选::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cjsj1 = gongju.riqizhuanhua((short)shijianq, m_cjsj1);
	m_cjsj2 = gongju.riqizhuanhua((short)shijianh, m_cjsj1);
	UpdateData(false);
	CString s;
	fenleibox.AddString(L"全部");
	fenleibox.SetCurSel(0);//默认全部
	for (int i = 0, j = 0; i < 64; i++)//存在的分类上组合框
	{
		if (gongju.flqk[i].cunzai == 1)
		{
			j++;
			s = gongju.flqk[i].name;
			fenleibox.AddString(s);
			if (fenlei == i) fenleibox.SetCurSel(j);
		}
	}
	zhuangtaibox.AddString(L"待学习");
	zhuangtaibox.AddString(L"已掌握");
	zhuangtaibox.AddString(L"备复习");
	zhuangtaibox.AddString(L"全部");
	zhuangtaibox.SetCurSel(zhuangtai);//默认全部
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void C筛选::OnBnClicked_Ok()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_cjsj1 > m_cjsj2)
	{
		MessageBox(L"前面时间不能大于后面时间！");
		return;
	}
	shijianq = gongju.riqizhuanhua(m_cjsj1.GetYear(), m_cjsj1.GetMonth(), m_cjsj1.GetDay());
	shijianh = gongju.riqizhuanhua(m_cjsj2.GetYear(), m_cjsj2.GetMonth(), m_cjsj2.GetDay());
	fenlei = 0;
	for (int i = 0, j = 0; i < 64; i++)//找到分类序号
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
