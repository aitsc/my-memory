
// ���丨��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "���丨��Dlg.h"
#include "afxdialogex.h"
#include "Cxiugaimingzi.h"
#include "Cxiugaimima.h"
#include "Cbianji.h"
#include "C�������.h"
#include "C����˵��.h"
#include "C��Ƭʽ.h"
#include "Cѡ�����.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// C���丨��Dlg �Ի���

static int ScreenX = GetSystemMetrics(SM_CXSCREEN);//��Ļ���
static int ScreenY = GetSystemMetrics(SM_CYSCREEN);//��Ļ�߶�
enum
{
	DOCK_NONE,           //��ͣ��
	DOCK_TOP,           //ͣ���ϱ�
	DOCK_LEFT,           //ͣ�����
	DOCK_RIGHT           //ͣ���ұ�
};

C���丨��Dlg::C���丨��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C���丨��Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DockMode = DOCK_NONE; //��ʼ����Ҫ����
	m_bHide = false; //�ٴ���δ����
}

void C���丨��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C���丨��Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_MOVING()
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_USERtishi, Ontishi)
	ON_COMMAND(ID_32771, &C���丨��Dlg::Onxiugaimingzi)
	ON_COMMAND(ID_32772, &C���丨��Dlg::Onxiugaimima)
	ON_COMMAND(ID_32773, &C���丨��Dlg::Onchakanbianji)
	ON_COMMAND(ID_32775, &C���丨��Dlg::Onguanyu)
	ON_BN_CLICKED(IDC_BUTTON2, &C���丨��Dlg::OnBnClicked_Qiandao)
	ON_BN_CLICKED(IDOK, &C���丨��Dlg::OnBnClicked_Xuexi)
	ON_BN_CLICKED(IDCANCEL, &C���丨��Dlg::OnBnClicked_Fuxi)
	ON_BN_CLICKED(IDC_BUTTON1, &C���丨��Dlg::OnBnClicked_Fanxiang)
	ON_COMMAND(ID_32774, &C���丨��Dlg::Onfenleiqingkuang)
	ON_COMMAND(ID_32786, &C���丨��Dlg::Ondaochu)
	ON_WM_CREATE()
	ON_COMMAND(ID_32787, &C���丨��Dlg::On�½��û�)
	ON_STN_CLICKED(IDC_STATIC3, &C���丨��Dlg::OnStnClicked_���븴ϰ)
	ON_WM_NCLBUTTONDBLCLK()
END_MESSAGE_MAP()


// C���丨��Dlg ��Ϣ�������

BOOL C���丨��Dlg::OnInitDialog()
{	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	menu.LoadMenu(IDR_ZHUYAO);
	SetMenu(&menu);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//GetMenu()->GetSubMenu(0)->DeleteMenu(ID_32786, MF_BYCOMMAND);
	shuaxin();
	gongju.BEI_FEN();//��������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C���丨��Dlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndDialog(10); //�رճ���
	//CDialogEx::OnClose();
}

//ˢ��������
void C���丨��Dlg::shuaxin()
{
	//�û���ˢ��
	CString yhm = gongju.yhm;
	GetMenu()->DeleteMenu(1, MF_BYPOSITION);
	GetMenu()->AppendMenu(MF_ENABLED, ID_32776, yhm);
	DrawMenuBar();
	//��ǩ����ˢ��
	CString s;
	s.Format(L"�����ѱ���Ŀ��%d", gongju.fxjz[3]);
	GetDlgItem(IDC_STATIC6)->SetWindowText(s);
	s.Format(L"�ܼ�����Ŀ��%d", gongju.zjyxm);
	GetDlgItem(IDC_STATIC1)->SetWindowText(s);
	s.Format(L"��ѧϰ��Ŀ��%d", gongju.zjyxm - gongju.dxxxm);
	GetDlgItem(IDC_STATIC2)->SetWindowText(s);
	s.Format(L"����ϰ��Ŀ��%d", gongju.dfxxm);
	GetDlgItem(IDC_STATIC3)->SetWindowText(s);
	s.Format(L"��������Ŀ��%d", gongju.yzwxm);
	GetDlgItem(IDC_STATIC4)->SetWindowText(s);
	//ǩ�����ˢ��
	if (0 == gongju.lsj)
	{
		s.Format(L"��ǩ����ʼ����֮�ã�");
		GetDlgItem(IDC_STATIC5)->SetWindowText(s);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	}
	else if (gongju.xtsj > gongju.lsj + 1)
	{
		s.Format(L"���Ѷ�ǩ%d�죡", gongju.xtsj - gongju.lsj - 1);
		GetDlgItem(IDC_STATIC5)->SetWindowText(s);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	}
	else
	{
		s.Format(L"���ɹ�ǩ��%d�죡", gongju.lsj - gongju.fsj + 1);
		GetDlgItem(IDC_STATIC5)->SetWindowText(s);
		if (gongju.xtsj == gongju.lsj) GetDlgItem(IDC_BUTTON2)->EnableWindow(false);//������ǩ��
		else GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	}
	//������ťˢ��
	if (gongju.zjyxm < 15)//����15����Ŀ����ѧϰ
	{
		s.Format(L"���ڲ鿴�༭�������Ŀ��");
		GetDlgItem(IDC_STATIC5)->SetWindowText(s);
		GetDlgItem(IDOK)->EnableWindow(false);
		GetDlgItem(IDCANCEL)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
		if (gongju.lsj>0 && gongju.xtsj > gongju.lsj) GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
		else GetDlgItem(IDC_BUTTON2)->EnableWindow(false);//ǩ������
	}
	else if (gongju.zjyxm == gongju.yzwxm)//ȫ������
	{
		s.Format(L"��ϲ��ȫ��ѧ�꣡");
		GetDlgItem(IDC_STATIC5)->SetWindowText(s);
		GetDlgItem(IDOK)->EnableWindow(false);
		GetDlgItem(IDCANCEL)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	}
	else if (gongju.xtsj != gongju.lsj)//��δǩ��ʱ
	{
		GetDlgItem(IDOK)->EnableWindow(false);
		GetDlgItem(IDCANCEL)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	}
	else //һ�����
	{
		if (0 == gongju.dxxxm) GetDlgItem(IDOK)->EnableWindow(false); //ѧ����
		else GetDlgItem(IDOK)->EnableWindow(true);
		if (0 == gongju.dfxxm) GetDlgItem(IDCANCEL)->EnableWindow(false);//��ϰ����
		else GetDlgItem(IDCANCEL)->EnableWindow(true);
		if (0 == gongju.dwfl[0][64]) GetDlgItem(IDC_BUTTON1)->EnableWindow(false);//�޷���
		else GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	}
	PostMessage(WM_USERtishi, 0, 0);
}

LRESULT  C���丨��Dlg::Ontishi(WPARAM wParam, LPARAM lParam)
{
	Sleep(50);
	if (1 == gongju.yc)
	{
		MessageBox(L"��þ�ûǩ���ˣ�ע����Ŷ��");
		gongju.yc = 0;
	}
	else if (20 <= gongju.yc)
	{
		CString s;
		s.Format(L"���ݿ��ܴ�����:%d", gongju.yc);
		MessageBox(s);
	}
	else if (0 != gongju.yc)
	{
		CString s;
		s.Format(L"���ݴ����쳣:%d", gongju.yc);
		MessageBox(s);
		gongju.BEI_FEN();//�����в������쳣
	}
	return 1;
}


void C���丨��Dlg::Onxiugaimingzi()
{
	// TODO:  �ڴ���������������
	Cxiugaimingzi xiugai;
	xiugai.yuanmz = gongju.yhm;
	if(11==xiugai.DoModal()) shuaxin();//�޸���� ˢ��
}


void C���丨��Dlg::Onxiugaimima()
{
	// TODO:  �ڴ���������������
	Cxiugaimima xiugai;
	xiugai.DoModal();
}


void C���丨��Dlg::Onchakanbianji()
{
	// TODO:  �ڴ���������������
	Cbianji xiugai;
	xiugai.DoModal();
	shuaxin();//ˢ��
}


void C���丨��Dlg::Onguanyu()
{
	// TODO:  �ڴ���������������
	C����˵�� dlg;
	dlg.DoModal();
}


void C���丨��Dlg::OnBnClicked_Qiandao()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	gongju.Qiandao();
	shuaxin();
}


void C���丨��Dlg::OnBnClicked_Xuexi()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (0 < gongju.dfxxm&&MessageBox(TEXT("��ϰ��δ��ɣ��Ƿ���ȥ��ϰ��"), TEXT("�����ȸ�ϰ"), MB_YESNO) == IDYES)
	{
		OnBnClicked_Fuxi();
		return;
	}
	gongju.buchongJydl();
	C��Ƭʽ xuexi;
	ShowWindow(false);
	xuexi.��Ƭ���� = 0;
	xuexi.DoModal();
	ShowWindow(true);
	shuaxin();
}


void C���丨��Dlg::OnBnClicked_Fuxi()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	C��Ƭʽ fuxi;
	ShowWindow(false);
	fuxi.��Ƭ���� = 1;
	fuxi.DoModal();
	ShowWindow(true);
	shuaxin();
}


void C���丨��Dlg::OnBnClicked_Fanxiang()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (gongju.dwfl[0][64] <= 0)
	{
		MessageBox(L"����Ŀ���Է���");
		return;
	}
	Cѡ����� xz;
	xz.�Ƿ��� = 1;
	if (11 != xz.DoModal()) return;//δѡ�����ʱ
	gongju.�����ʼ��(xz.fenlei);
	C��Ƭʽ fanxiang;
	ShowWindow(false);
	fanxiang.��Ƭ���� = 2;
	fanxiang.DoModal();
	gongju.��������[32704] = 0;
	ShowWindow(true);
	shuaxin();
}


void C���丨��Dlg::Onfenleiqingkuang()
{
	// TODO:  �ڴ���������������
	C������� fenlei;
	fenlei.DoModal();
	shuaxin();//ˢ��
}


void C���丨��Dlg::Ondaochu()
{
	// TODO:  �ڴ���������������
	if (gongju.zjyxm <= 0)
	{
		MessageBox(L"����Ŀ���Ե�����");
		return;
	}
	Cѡ����� xz;
	if (11 != xz.DoModal()) return;
	CFileDialog filedlg(false);
	filedlg.m_ofn.lpstrTitle = L"��ѡ�񱣴�λ��";
	filedlg.m_ofn.lpstrFilter = L"�ı��ļ�(*.txt)\0*.txt\0\0";
	if (IDOK != filedlg.DoModal())
	{
		ShowWindow(false);   //��֤������Դӱ���Ի������
		ShowWindow(true);
		return;
	}
	ShowWindow(false);
	ShowWindow(true);
	CString s = filedlg.GetPathName();
	if (lstrcmpi(s.Right(4), L".txt") != 0) //ʹ�ú�׺���Զ���Ӷ����ظ�
		s += ".txt";
	if (0 == gongju.daochu(s, xz.fenlei))
		MessageBox(L"����ʧ�ܣ�");
}


void C���丨��Dlg::On�½��û�()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog filedlg(false);
	FILE *fp;
	filedlg.m_ofn.lpstrTitle = L"�½����ݿ�";
	filedlg.m_ofn.lpstrFilter = L"�����ļ�(*.ysj)\0*.ysj\0\0";
	if (IDOK != filedlg.DoModal())
	{
		ShowWindow(false);   //��֤������Դӱ���Ի������
		ShowWindow(true);
		return;
	}
	ShowWindow(false);
	ShowWindow(true);
	CString s = filedlg.GetPathName();
	if (lstrcmpi(s.Right(4), L".ysj") != 0) //ʹ�ú�׺���Զ���Ӷ����ظ�
		s += ".ysj";
	if (0 != _wfopen_s(&fp, s, L"wb+"))
	{
		MessageBox(L"�½�ʧ�ܣ�");
		return;
	}
	char c = 0;
	fwrite(L"̷��������", 2, 5, fp);//д���ʶͷ��Ĭ���û���
	for (int i = 0, c = 0; i < 86; i++)
		fwrite(&c, 1, 1, fp);
	for (int i = 0, c = 0; i < 523264; i++)
		fwrite(&c, 1, 1, fp);
	for (int i = 0, c = 0; i < 2066; i++)
		fwrite(&c, 1, 1, fp);
	int a = 525430;
	fwrite(&a, 4, 1, fp);
	MessageBox(L"�½��ɹ���");
}


void C���丨��Dlg::OnStnClicked_���븴ϰ()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (gongju.dfxxm != 0 || gongju.fxlbt->biaoshi <= 0) return;
	if (MessageBox(TEXT("��ȷ��Ҫ���븴ϰ��"), TEXT("���븴ϰ�������"), MB_YESNO) == IDNO)
	{
		return;
	}
	C��Ƭʽ srfuxi;
	ShowWindow(false);
	srfuxi.��Ƭ���� = 3;
	srfuxi.DoModal();
	ShowWindow(true);
	shuaxin();
}


void C���丨��Dlg::AnimateShowHide(BOOL bHide)
{
	if (m_DockMode == DOCK_NONE)
		return;
	m_bHide = bHide;
	const int borderWidth = 1;//���µı�Ե
	RECT rc;
	GetWindowRect(&rc);
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	//�±��жϴ��������ƶ�,��ͣ����ʽ����
	int timesY = 9; //ƽ�ƶԻ���Ĵ���,�������ò���ƽ��,���������ֵ.
	int timesX = 6;//����
	int times = 0;
	int xStep, yStep;
	int xEnd, yEnd;
	switch (m_DockMode)
	{
	case DOCK_TOP:
	{
		//�����Ʋ�
		xStep = 0;
		xEnd = rc.left;
		if (bHide)
		{
			yStep = -rc.bottom / timesY;
			yEnd = -height + borderWidth;
		}
		else//����
		{
			yStep = -rc.top / timesY;
			yEnd = 0;
		}
		times = timesY;
		break;
	}
	case DOCK_LEFT:
	{
		//�����Ʋ�
		yStep = 0;
		yEnd = rc.top;
		if (bHide)
		{
			xStep = -rc.right / timesX;
			xEnd = -width + borderWidth;
		}
		else//����
		{
			xStep = -rc.left / timesX;
			xEnd = 0;
		}
		times = timesX;
		break;
	}
	case DOCK_RIGHT:
	{
		//�����Ʋ�
		yStep = 0;
		yEnd = rc.top;
		if (bHide)
		{
			xStep = (ScreenX - rc.left) / timesX;
			xEnd = ScreenX - borderWidth;
		}
		else//����
		{
			xStep = (ScreenX - rc.right) / timesX;
			xEnd = ScreenX - width;
		}
		times = timesX;
		break;
	}
	default:
		_ASSERTE(FALSE);
	}
	//������������.
	for (int i = 0; i < times - 1; ++i)
	{
		rc.left += xStep;
		rc.top += yStep;
		MoveWindow(rc.left, rc.top, width, height, false);
		//SetWindowPos(NULL, rc.left, rc.top, 0, 0, SWP_NOSIZE | SWP_NOSENDCHANGING);
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

		Sleep(5);
	}
	SetWindowPos(NULL, xEnd, yEnd, 0, 0, SWP_NOSIZE);
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE); //�������ö�
}


void C���丨��Dlg::OnMoving(UINT nSide, LPRECT pRect)
{
	int juli = 14; //��Ч����
	//�Զ�����
	if (pRect->top <= juli) //���ϱ���Ч�����ڣ��Զ���£��
	{
		m_DockMode = DOCK_TOP;
	}
	else if (pRect->left <= juli) //�������Ч�����ڣ��Զ���£��
	{
		m_DockMode = DOCK_LEFT;
	}
	else if (ScreenX - pRect->right <= juli) //���ұ���Ч�����ڣ��Զ���£��
	{
		m_DockMode = DOCK_RIGHT;
	}
	else
	{
		m_DockMode = DOCK_NONE;
	}
	if (ScreenY < pRect->bottom)//̫�Ͳ���£
	{
		m_DockMode = DOCK_NONE;
	}
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
	if (m_DockMode != DOCK_NONE)
	{
		SetTimer(1, 50, NULL);
	}
	else
	{
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); //���������ö�
		KillTimer(1);
	}
}


void C���丨��Dlg::OnTimer(UINT nIDEvent) //ֱ����������
{
	static int a = 0;
	if (m_DockMode != DOCK_NONE && nIDEvent == 1)
	{
		POINT pt;
		RECT rc;
		GetCursorPos(&pt);
		GetWindowRect(&rc);
		if (!PtInRect(&rc, pt))
		{
			Sleep(220); //��ֹ������ȥ
			GetCursorPos(&pt);
			GetWindowRect(&rc);
			if (!PtInRect(&rc, pt))
			{
				AnimateShowHide(TRUE);
				KillTimer(1);
				a = 1;
			}
		}
		if (a)//�ؽ���
		{
//			ShowWindow(false);
//			ShowWindow(true);
			a = 0;
		}
	}
}


LRESULT C���丨��Dlg::OnNcHitTest(CPoint point)//ֱ�����ڵ���
{
	if (m_bHide)
	{
		AnimateShowHide(FALSE);
		if (m_DockMode != DOCK_NONE)
		{
			SetTimer(1, 50, NULL);
		}
	}
	//����õ�����Ķ�Ӧ���������򰴹رհ�ť�����������ϵͳ�˵�����ק��������û����Ӧ��
	return CDialog::OnNcHitTest(point);
}

void C���丨��Dlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndDialog(0);//˫���������ر�
	CDialogEx::OnNcLButtonDblClk(nHitTest, point);
}
