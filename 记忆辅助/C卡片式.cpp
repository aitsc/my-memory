// C��Ƭʽ.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "C��Ƭʽ.h"
#include "afxdialogex.h"
#include "Czengaixiangmu.h"
#define ������ס��ʱ�� 500

// C��Ƭʽ �Ի���

static int ScreenX = GetSystemMetrics(SM_CXSCREEN);//��Ļ���
static int ScreenY = GetSystemMetrics(SM_CYSCREEN);//��Ļ�߶�
IMPLEMENT_DYNAMIC(C��Ƭʽ, CDialogEx)

C��Ƭʽ::C��Ƭʽ(CWnd* pParent /*=NULL*/)
	: CDialogEx(C��Ƭʽ::IDD, pParent)
	, wenti(_T(""))
	, daan(_T(""))
	, ��Ƭ����(0)
	, keyi(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

C��Ƭʽ::~C��Ƭʽ()
{
}

void C��Ƭʽ::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, wenti);
	DDV_MaxChars(pDX, wenti, 900);
	DDX_Text(pDX, IDC_EDIT1, daan);
	DDV_MaxChars(pDX, daan, 900);
}


BEGIN_MESSAGE_MAP(C��Ƭʽ, CDialogEx)
	ON_WM_MOVING()
	ON_BN_CLICKED(IDOK1, &C��Ƭʽ::OnBnClicked_jizhule)
	ON_BN_CLICKED(IDCANCEL1, &C��Ƭʽ::OnBnClicked_wangjile)
	ON_BN_CLICKED(IDC_BUTTON1, &C��Ƭʽ::OnBnClicked_huoqudaan)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_COMMAND(IDCANCEL, &C��Ƭʽ::OnIdcancel)
	ON_COMMAND(ID_32776, &C��Ƭʽ::On�޸���Ŀ)
	ON_COMMAND(ID_32777, &C��Ƭʽ::Onɾ����Ŀ)
	ON_COMMAND(ID_32778, &C��Ƭʽ::On��ѧ)
	ON_WM_NCLBUTTONDBLCLK()
END_MESSAGE_MAP()


// C��Ƭʽ ��Ϣ�������


BOOL C��Ƭʽ::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);//��ʾ������ͼ��
	SetMenu((menu.LoadMenu(IDR_KAPIAN), &menu));//��ʾ�˵���
	CEdit *m_EditAa = (CEdit *)GetDlgItem(IDC_EDIT4);     //�����ؼ�A
	CEdit *m_EditBb = (CEdit *)GetDlgItem(IDC_EDIT1);     //�����ؼ�B
	font.CreatePointFont(105, L"����");     //ѡ������
	//m_EditAa->SetFont(&font);
	//m_EditBb->SetFont(&font);
	//GetDlgItem(IDC_BUTTON1)->SetFont(&font);
	if (��Ƭ���� == 0) SetWindowText(L"ѧϰ��Ƭ");
	if (��Ƭ���� == 1) SetWindowText(L"��ϰ��Ƭ");
	if (��Ƭ���� == 2)
	{
		menu.EnableMenuItem(ID_32776, MF_BYCOMMAND | MF_DISABLED);
		menu.EnableMenuItem(ID_32777, MF_BYCOMMAND | MF_DISABLED);
		menu.EnableMenuItem(ID_32778, MF_BYCOMMAND | MF_DISABLED);
		SetWindowText(L"����Ƭ");
	}
	if (��Ƭ���� == 3) SetWindowText(L"���븴ϰ��Ƭ");
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);//��֤��������ǰ��
	shuaxin();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void C��Ƭʽ::OnBnClicked_jizhule()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (��Ƭ���� == 0)
	{
		gongju.ѧϰһ��(1);
	}
	else if (��Ƭ���� == 1)
	{
		gongju.��ϰһ��(1);
	}
	else if (��Ƭ���� == 2)
	{
		gongju.����һ��(1);
	}
	else if (��Ƭ���� == 3)
	{
		gongju.dfxxm = 1;
		gongju.��ϰһ��(1);
	}
	shuaxin();
}


void C��Ƭʽ::OnBnClicked_wangjile()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (��Ƭ���� == 0)
	{
		if (gongju.jydl[0].biaoshi > 0)//��䷴����
		{
			GetDlgItem(IDC_STATIC2)->SetWindowText(L"0");
			daan = gongju.xmsj[gongju.jydl[0].biaoshi - 1].daan;
		}
		else
		{
			daan = gongju.xmsj[-gongju.jydl[0].biaoshi - 1].wenti;
		}
		UpdateData(false);
		gongju.ѧϰһ��(0);
	}
	else if (��Ƭ���� == 1)
	{
		CString s;
		if (gongju.fxlbt->next->pingyancishu == 126)
		{
			s.Format(L"%d", gongju.fxlbt->next->pingyancishu);
		}
		else
		{
			s.Format(L"%d", gongju.fxlbt->next->pingyancishu + 1);
		}
		GetDlgItem(IDC_STATIC2)->SetWindowText(s);//ˢ�±�ǩ
		daan = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].daan;
		UpdateData(false);
		gongju.��ϰһ��(0);
	}
	else if (��Ƭ���� == 2)
	{
		daan = gongju.xmsj[gongju.��������[0] - 1].wenti;
		UpdateData(false);
		gongju.����һ��(0);
	}
	else if (��Ƭ���� == 3)
	{
		daan = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].daan;
		UpdateData(false);
		gongju.dfxxm = 1;
		gongju.��ϰһ��(0);
		gongju.dfxxm = 0;
	}
	if (��Ƭ���� != 2) //�����˲˵�������
	{
		menu.EnableMenuItem(ID_32776, MF_BYCOMMAND | MF_DISABLED);
		menu.EnableMenuItem(ID_32777, MF_BYCOMMAND | MF_DISABLED);
		menu.EnableMenuItem(ID_32778, MF_BYCOMMAND | MF_DISABLED);
	}
	keyi = 0;
	GetDlgItem(IDOK1)->EnableWindow(false);
	GetDlgItem(IDCANCEL1)->EnableWindow(false);
	SetDlgItemText(IDC_BUTTON1, _T("��һ��"));
}


void C��Ƭʽ::OnBnClicked_huoqudaan()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString s;
	GetDlgItemText(GetFocus()->GetDlgCtrlID(), s);
	if (s == _T("��һ��"))
	{
		shuaxin();
		if (��Ƭ���� != 2) //��һ���˵�����
		{
			menu.EnableMenuItem(ID_32776, MF_BYCOMMAND | MF_ENABLED);
			menu.EnableMenuItem(ID_32777, MF_BYCOMMAND | MF_ENABLED);
			menu.EnableMenuItem(ID_32778, MF_BYCOMMAND | MF_ENABLED);
		}
		return;
	}
	if (��Ƭ���� == 0)
	{
		if (gongju.jydl[0].biaoshi > 0)//��䷴����
		{
			daan = gongju.xmsj[gongju.jydl[0].biaoshi - 1].daan;
		}
		else
		{
			daan = gongju.xmsj[-gongju.jydl[0].biaoshi - 1].wenti;
		}
	}
	else if (��Ƭ���� == 1)
	{
		daan = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].daan;
	}
	else if (��Ƭ���� == 2)
	{
		daan = gongju.xmsj[gongju.��������[0] - 1].wenti;
	}
	else if (��Ƭ���� == 3)
	{
		daan = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].daan;
	}
	keyi = 0;
	UpdateData(false);
	GetDlgItem(IDOK1)->EnableWindow(true);
}


int C��Ƭʽ::shuaxin()//Ҫ��ʾ��һ����Ŀʱ����Ҫˢ��
{
	//���������
	if (��Ƭ���� == 0)
	{
		if (0 >= gongju.dlyxs)
		{
			if (MessageBox(TEXT("�Ƿ�ʼ��һ��ѧϰ��"), TEXT("���һ��ѧϰ"), MB_YESNO) == IDNO)
			{
				EndDialog(11);
				return 0;
			}
			gongju.buchongJydl();
		}
		if (0 >= gongju.dxxxm)
		{
			MessageBox(L"��ȫ����ɣ�");
			EndDialog(11);
			return 0;
		}
		if (0 == gongju.jydl[0].biaoshi) gongju.buchongJydl();
	}
	else if (��Ƭ���� == 1)
	{
		if (0 >= gongju.dfxxm)
		{
			MessageBox(L"��ϲ��ϰ��ɣ�");
			EndDialog(11);
			return 0;
		}
	}
	else if (��Ƭ���� == 2)
	{
		if (0 >= gongju.��������[32704])
		{
			MessageBox(L"ȫ����ɣ�");
			EndDialog(11);
			return 0;
		}
	}
	else if (��Ƭ���� == 3)
	{
		if (0 >= gongju.fxlbt->biaoshi)
		{
			MessageBox(L"��ϲ���븴ϰ��ɣ�");
			EndDialog(11);
			return 0;
		}
	}
	CString s;
	//����ˢ��
	if (��Ƭ���� == 0)
	{
		s = gongju.flqk[gongju.xmsj[abs(gongju.jydl[0].biaoshi) - 1].fenlei].name;
		GetMenu()->DeleteMenu(1, MF_BYPOSITION);
		GetMenu()->AppendMenu(MF_ENABLED, ID_32779, s);
		DrawMenuBar();
	}
	else if (��Ƭ���� == 1)
	{
		s = gongju.flqk[gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].fenlei].name;
		GetMenu()->DeleteMenu(1, MF_BYPOSITION);
		GetMenu()->AppendMenu(MF_ENABLED, ID_32779, s);
		DrawMenuBar();
	}
	else if (��Ƭ���� == 2)
	{
		s = gongju.flqk[gongju.xmsj[gongju.��������[0] - 1].fenlei].name;
		GetMenu()->DeleteMenu(1, MF_BYPOSITION);
		GetMenu()->AppendMenu(MF_ENABLED, ID_32779, s);
		DrawMenuBar();
	}
	else if (��Ƭ���� == 3)
	{
		s = gongju.flqk[gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].fenlei].name;
		GetMenu()->DeleteMenu(1, MF_BYPOSITION);
		GetMenu()->AppendMenu(MF_ENABLED, ID_32779, s);
		DrawMenuBar();
	}
	//��ǩˢ��
	if (��Ƭ���� == 0)
	{
		s.Format(L"����ʣ��ѧϰ������%d", gongju.dlyxs);
		GetDlgItem(IDC_STATIC1)->SetWindowText(s);
		if (gongju.jydl[0].biaoshi>0) s.Format(L"%d", gongju.jydl[0].lianxucishu);
		else s.Format(L"%d", -1);
		GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	}
	else if (��Ƭ���� == 1)
	{
		s.Format(L"ʣ�ิϰ������%d", gongju.dfxxm);
		GetDlgItem(IDC_STATIC1)->SetWindowText(s);
		s.Format(L"%d", gongju.fxlbt->next->pingyancishu);
		GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	}
	else if (��Ƭ���� == 2)
	{
		s.Format(L"��%d����Ŀ�������ȡѧϰ", gongju.��������[32704]);
		GetDlgItem(IDC_STATIC1)->SetWindowText(s);
		s = "";
		GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	}
	else if (��Ƭ���� == 3)
	{
		s.Format(L"ʣ������븴ϰ������%d", gongju.fxlbt->biaoshi);
		GetDlgItem(IDC_STATIC1)->SetWindowText(s);
		s.Format(L"%d", gongju.fxlbt->next->pingyancishu);
		GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	}
	//����ˢ��
	if (��Ƭ���� == 0)
	{
		if (gongju.jydl[0].biaoshi > 0)//��䷴����
		{
			wenti = gongju.xmsj[gongju.jydl[0].biaoshi - 1].wenti;
			daan = "";
		}
		else
		{
			wenti = gongju.xmsj[-gongju.jydl[0].biaoshi - 1].daan;
			daan = "";
		}
	}
	else if (��Ƭ���� == 1)
	{
		wenti = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].wenti;
		daan = "";
	}
	else if (��Ƭ���� == 2)
	{
		wenti = gongju.xmsj[gongju.��������[0] - 1].daan;
		daan = "";
	}
	else if (��Ƭ���� == 3)
	{
		wenti = gongju.xmsj[gongju.fxlbt->next->biaoshi - 1].wenti;
		daan = "";
	}
	UpdateData(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDCANCEL1)->EnableWindow(true);
	SetDlgItemText(IDC_BUTTON1, _T("��ȡ��"));
	GetDlgItem(IDOK1)->EnableWindow(false);//��ť��ʱ������
	SetTimer(1, ������ס��ʱ��, NULL);
	//SetTimer(1, 1, NULL);
	keyi = 1;
	return 1;
}


void C��Ƭʽ::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (1 == nIDEvent&&keyi)
	{
		GetDlgItem(IDOK1)->EnableWindow(true);
		keyi = 0;
	}
	KillTimer(nIDEvent);
	CDialogEx::OnTimer(nIDEvent);
}


void C��Ƭʽ::OnIdcancel()
{
	// TODO:  �ڴ���������������
	if (��Ƭ���� == 1 &&  MessageBox(TEXT("��ȷ�������˳���"), TEXT("��δ��ϰ�꣡"), MB_YESNO) == IDNO)
	{
		return;
	}
	EndDialog(11);
}


void C��Ƭʽ::On�޸���Ŀ()
{
	// TODO:  �ڴ���������������
	Czengaixiangmu xiugai;
	xiugai.zengjia = 0;
	if (��Ƭ���� == 0)
	{
		xiugai.biaozhi = abs(gongju.jydl[0].biaoshi);
	}
	else if (��Ƭ���� == 1)
	{
		xiugai.biaozhi = gongju.fxlbt->next->biaoshi;
	}
	else if (��Ƭ���� == 2)
	{
	}
	else if (��Ƭ���� == 3)
	{
		xiugai.biaozhi = gongju.fxlbt->next->biaoshi;
	}
	if (0 != xiugai.biaozhi && 11 == xiugai.DoModal())
	{
		shuaxin();
	}
}


void C��Ƭʽ::Onɾ����Ŀ()
{
	// TODO:  �ڴ���������������
	if (15 == gongju.zjyxm)
	{
		MessageBox(L"��Ŀ������15�����£�");
		return;
	}
	if (MessageBox(TEXT("��ȷ��Ҫɾ��������¼��"), TEXT("ɾ��"), MB_YESNO) == IDNO)
	{
		return;
	}
	int biaoshi = 0;
	if (��Ƭ���� == 0)
	{
		biaoshi = abs(gongju.jydl[0].biaoshi);
	}
	else if (��Ƭ���� == 1)
	{
		biaoshi = gongju.fxlbt->next->biaoshi;
	}
	else if (��Ƭ���� == 2)
	{
	}
	else if (��Ƭ���� == 3)
	{
		biaoshi = gongju.fxlbt->next->biaoshi;
	}
	if (0 != biaoshi && 1 == gongju.shanchuXiangmu(biaoshi))
	{
		shuaxin();
	}
}


void C��Ƭʽ::On��ѧ()//��ѧһ����ǰѧϰ�����һ��������ˢ�º���ѧ����ֻص�������
{
	// TODO:  �ڴ���������������
	if (MessageBox(TEXT("��ȷ��Ҫ��ѧ����Ŀ��"), TEXT("��ѧ��Ŀ"), MB_YESNO) == IDNO)
	{
		return;
	}
	int biaoshi = 0;
	CString wenti0, daan0;
	char fenlei0;
	if (��Ƭ���� == 0)
	{
		biaoshi = abs(gongju.jydl[0].biaoshi);
	}
	else if (��Ƭ���� == 1)
	{
		biaoshi = gongju.fxlbt->next->biaoshi;
	}
	else if (��Ƭ���� == 2)
	{
	}
	else if (��Ƭ���� == 3)
	{
		biaoshi = gongju.fxlbt->next->biaoshi;
	}
	if (0 != biaoshi)
	{
		wenti0 = gongju.xmsj[biaoshi - 1].wenti;
		daan0 = gongju.xmsj[biaoshi - 1].daan;
		fenlei0 = gongju.xmsj[biaoshi - 1].fenlei;
		if (0 < gongju.xiugaiXiangmu(biaoshi, 1, wenti0, daan0, fenlei0))
		{
			shuaxin();
		}
	}
}

void C��Ƭʽ::OnMoving(UINT nSide, LPRECT pRect)
{
	//Խ����
	if (pRect->top <= 0) //���ܳ������ϱ�
	{
		pRect->bottom -= pRect->top;
		pRect->top = 0;
	}
	if (pRect->left <= 0) //���ܳ��������
	{
		pRect->right -= pRect->left;
		pRect->left = 0;
	}
	if (pRect->right >= ScreenX) //���ܳ������ұ�
	{
		pRect->left += (ScreenX - pRect->right);
		pRect->right = ScreenX;
	}
	if (pRect->bottom >= ScreenY) //���ܳ������±�
	{
		pRect->top += (ScreenY - pRect->bottom);
		pRect->bottom = ScreenY;
	}
}

void C��Ƭʽ::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);//��С������
	CDialogEx::OnNcLButtonDblClk(nHitTest, point);
}
