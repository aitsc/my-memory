// Cdenglu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���丨��.h"
#include "Cdenglu.h"
#include "afxdialogex.h"



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cdenglu �Ի���

IMPLEMENT_DYNAMIC(Cdenglu, CDialogEx)

Cdenglu::Cdenglu(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cdenglu::IDD, pParent)
	, lujing(_T(""))
	, mima(_T(""))
	, �û���(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

Cdenglu::~Cdenglu()
{
}

void Cdenglu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, lujing);
	DDX_Text(pDX, IDC_EDIT3, mima);
	DDV_MaxChars(pDX, mima, 10);
	DDX_Text(pDX, IDC_EDIT1, �û���);
}


BEGIN_MESSAGE_MAP(Cdenglu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Cdenglu::OnBnClicked_Xinjian)
	ON_BN_CLICKED(IDOK, &Cdenglu::OnBnClicked_Dakai)
	ON_BN_CLICKED(IDCANCEL, &Cdenglu::OnBnClicked_Queding)
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// Cdenglu ��Ϣ�������


void Cdenglu::OnBnClicked_Xinjian()//�½���ť
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog filedlg(false);
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
	for (int i = 0,c=0; i < 86; i++)
		fwrite(&c, 1, 1, fp);
	for (int i = 0, c = 0; i < 35408; i++)//����
		fwrite(&c, 1, 1, fp);
	for (int i = 0, c = 0; i < 523264 - 35408; i++)
		fwrite(&c, 1, 1, fp);
	for (int i = 0,c=0; i < 2066; i++)
		fwrite(&c, 1, 1, fp);
	int a = 525430;
	fwrite(&a, 4, 1, fp);
	MessageBox(L"�½��ɹ���");
	UpdateData(true);
	if (lujing == "")
	{
		lujing = s;
		wchar_t yhm[6] = { 0 };
		fseek(fp, 2, 0);
		fread(yhm, 2, 5, fp);
		�û��� = yhm;
		UpdateData(false);
	}
	fclose(fp);
}


void Cdenglu::OnBnClicked_Dakai()//�򿪰�ť
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog filedlg(true);
	filedlg.m_ofn.lpstrTitle = L"�����ݿ�";
	filedlg.m_ofn.lpstrFilter = L"�����ļ�(*.ysj)\0*.ysj\0\0";
	if (IDOK != filedlg.DoModal())
	{
		ShowWindow(false);
		ShowWindow(true);
		return;
	}
	ShowWindow(false);
	ShowWindow(true);
	lujing = filedlg.GetPathName();
	if (0 == jiance()) return;  //������
	fseek(fp,15,0);
	char c;
	fread(&c, 1, 1, fp);
	if (c>=0) //�Ƿ��������
	{
		fseek(fp, 0, 0);//ָ�붨λ��ͷ
		EndDialog(11);//������¼�Ի���
		return;//���򷵻�
	}
	wchar_t yhm[6] = { 0 };
	fseek(fp, 2, 0);
	fread(yhm, 2, 5, fp);
	�û��� = yhm;
	fclose(fp);
	UpdateData(false);//�������༭��
}


void Cdenglu::OnBnClicked_Queding()//ȷ����ť
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true); //�༭�򵽱���
	if (0 == jiance()) return;  //������
	fseek(fp, 12, 0);
	int dumima;  //��ȡ������
	fread(&dumima, 4, 1, fp); //���ı��ֽ�˳��
	if (dumima >= 0) //�Ƿ��������
	{
		fseek(fp, 0, 0);//ָ�붨λ��ͷ
		EndDialog(11);//���ܵ�¼�Ի���
		return;//���򷵻�
	}
	int xiemima = _ttoi(mima)|0x80000000; //д������ת��
	if (dumima != xiemima) //�����Ƿ���ȷ
	{
		fclose(fp);
		MessageBox(L"�������");
		Sleep(250); //��ֹ����ˢ����
		mima = ""; 
		UpdateData(false);//�������༭��
		return;
	}
	fseek(fp, 0, 0); //������ȷ
	EndDialog(11);
	return;
}


void Cdenglu::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	EndDialog(10); //�رճ���
	CDialogEx::OnClose();
}


BOOL Cdenglu::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	if (lujing != "")
	{
		if (0 == jiance()) //������
		{
			EndDialog(10); //�رճ���
			return TRUE; 
		}
		fseek(fp, 15, 0);
		char c;
		fread(&c, 1, 1, fp);
		if (c >= 0) //�Ƿ��������
		{
			fseek(fp, 0, 0);//ָ�붨λ��ͷ
			EndDialog(11);//������¼�Ի���
			return TRUE;//���򷵻�
		}
		wchar_t yhm[6] = { 0 };
		fseek(fp, 2, 0);
		fread(yhm, 2, 5, fp);
		�û��� = yhm;
		fclose(fp);
		UpdateData(false);//�������༭��
	}
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);//��֤��������ǰ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void Cdenglu::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


int Cdenglu::jiance()//����ļ��Ƿ���ȷ
{
	if (0 != _wfopen_s(&fp, lujing, L"rb+"))
	{
		MessageBox(L"��������ʧ�ܣ�");
		return 0;
	}
	fseek(fp, 0, SEEK_END);//�ļ�ָ���ƶ���ĩβ
	int n = ftell(fp);//�ļ���С��ȡ
	if (n == -1)
	{
		fclose(fp);
		MessageBox(L"���ݿ����");
		return 0;
	}
	fseek(fp, 0, 0);
	short bs;
	fread(&bs, 2, 1, fp);
	if (-29651 != bs)
	{
		fclose(fp);
		MessageBox(L"�ļ���ʽ����");
		return 0;
	}
	if (n<525430)
	{
		fclose(fp);
		MessageBox(L"�ļ��𻵣�");
		return 0;
	}
	return 1;
}

void Cdenglu::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	wchar_t filePath[5120];
	DragQueryFile(hDropInfo, 0, filePath, sizeof(filePath));//��ȡ��ק�ĵ�һ���ļ���·��
	lujing = filePath;
	CString s1;
	s1 = lujing.Right(4);
	s1.MakeUpper();//ȫ���д
	if (s1 != ".YSJ")
	{
		MessageBox(L"��׺������");
		return;
	}
	if (0 == jiance()) return;  //������
	fseek(fp, 15, 0);
	char c;
	fread(&c, 1, 1, fp);
	if (c >= 0) //�Ƿ��������
	{
		fseek(fp, 0, 0);//ָ�붨λ��ͷ
		EndDialog(11);//������¼�Ի���
		return;//���򷵻�
	}
	wchar_t yhm[6] = { 0 };
	fseek(fp, 2, 0);
	fread(yhm, 2, 5, fp);
	�û��� = yhm;
	fclose(fp);
	UpdateData(false);//�������༭��
	CDialogEx::OnDropFiles(hDropInfo);
}


BOOL Cdenglu::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && 13 == pMsg->wParam)
	{
		if (GetDlgItem(IDC_EDIT3) == GetFocus())
		{
			OnBnClicked_Queding();
			return FALSE;//��һ��������0ֵ
		}
		else
		{
			return FALSE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
