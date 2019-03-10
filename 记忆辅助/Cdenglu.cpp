// Cdenglu.cpp : 实现文件
//

#include "stdafx.h"
#include "记忆辅助.h"
#include "Cdenglu.h"
#include "afxdialogex.h"



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// Cdenglu 对话框

IMPLEMENT_DYNAMIC(Cdenglu, CDialogEx)

Cdenglu::Cdenglu(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cdenglu::IDD, pParent)
	, lujing(_T(""))
	, mima(_T(""))
	, 用户名(_T(""))
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
	DDX_Text(pDX, IDC_EDIT1, 用户名);
}


BEGIN_MESSAGE_MAP(Cdenglu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Cdenglu::OnBnClicked_Xinjian)
	ON_BN_CLICKED(IDOK, &Cdenglu::OnBnClicked_Dakai)
	ON_BN_CLICKED(IDCANCEL, &Cdenglu::OnBnClicked_Queding)
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// Cdenglu 消息处理程序


void Cdenglu::OnBnClicked_Xinjian()//新建按钮
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog filedlg(false);
	filedlg.m_ofn.lpstrTitle = L"新建数据库";
	filedlg.m_ofn.lpstrFilter = L"数据文件(*.ysj)\0*.ysj\0\0";
	if (IDOK != filedlg.DoModal())
	{
		ShowWindow(false);   //保证焦点可以从保存对话框回来
		ShowWindow(true);
		return;
	}
	ShowWindow(false);
	ShowWindow(true);
	CString s = filedlg.GetPathName();
	if (lstrcmpi(s.Right(4), L".ysj") != 0) //使得后缀名自动添加而不重复
		s += ".ysj";
	if (0 != _wfopen_s(&fp, s, L"wb+"))
	{
		MessageBox(L"新建失败！");
		return;
	}
	char c = 0;
	fwrite(L"谭不忘初心", 2, 5, fp);//写入标识头和默认用户名
	for (int i = 0,c=0; i < 86; i++)
		fwrite(&c, 1, 1, fp);
	for (int i = 0, c = 0; i < 35408; i++)//测试
		fwrite(&c, 1, 1, fp);
	for (int i = 0, c = 0; i < 523264 - 35408; i++)
		fwrite(&c, 1, 1, fp);
	for (int i = 0,c=0; i < 2066; i++)
		fwrite(&c, 1, 1, fp);
	int a = 525430;
	fwrite(&a, 4, 1, fp);
	MessageBox(L"新建成功！");
	UpdateData(true);
	if (lujing == "")
	{
		lujing = s;
		wchar_t yhm[6] = { 0 };
		fseek(fp, 2, 0);
		fread(yhm, 2, 5, fp);
		用户名 = yhm;
		UpdateData(false);
	}
	fclose(fp);
}


void Cdenglu::OnBnClicked_Dakai()//打开按钮
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog filedlg(true);
	filedlg.m_ofn.lpstrTitle = L"打开数据库";
	filedlg.m_ofn.lpstrFilter = L"数据文件(*.ysj)\0*.ysj\0\0";
	if (IDOK != filedlg.DoModal())
	{
		ShowWindow(false);
		ShowWindow(true);
		return;
	}
	ShowWindow(false);
	ShowWindow(true);
	lujing = filedlg.GetPathName();
	if (0 == jiance()) return;  //错误检测
	fseek(fp,15,0);
	char c;
	fread(&c, 1, 1, fp);
	if (c>=0) //是否存在密码
	{
		fseek(fp, 0, 0);//指针定位开头
		EndDialog(11);//结束登录对话框
		return;//程序返回
	}
	wchar_t yhm[6] = { 0 };
	fseek(fp, 2, 0);
	fread(yhm, 2, 5, fp);
	用户名 = yhm;
	fclose(fp);
	UpdateData(false);//变量到编辑框
}


void Cdenglu::OnBnClicked_Queding()//确定按钮
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true); //编辑框到变量
	if (0 == jiance()) return;  //错误检测
	fseek(fp, 12, 0);
	int dumima;  //读取的密码
	fread(&dumima, 4, 1, fp); //不改变字节顺序
	if (dumima >= 0) //是否存在密码
	{
		fseek(fp, 0, 0);//指针定位开头
		EndDialog(11);//接受登录对话框
		return;//程序返回
	}
	int xiemima = _ttoi(mima)|0x80000000; //写的密码转换
	if (dumima != xiemima) //密码是否正确
	{
		fclose(fp);
		MessageBox(L"密码错误！");
		Sleep(250); //防止恶意刷密码
		mima = ""; 
		UpdateData(false);//变量到编辑框
		return;
	}
	fseek(fp, 0, 0); //密码正确
	EndDialog(11);
	return;
}


void Cdenglu::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	EndDialog(10); //关闭程序
	CDialogEx::OnClose();
}


BOOL Cdenglu::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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
	// TODO:  在此添加额外的初始化
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	if (lujing != "")
	{
		if (0 == jiance()) //错误检测
		{
			EndDialog(10); //关闭程序
			return TRUE; 
		}
		fseek(fp, 15, 0);
		char c;
		fread(&c, 1, 1, fp);
		if (c >= 0) //是否存在密码
		{
			fseek(fp, 0, 0);//指针定位开头
			EndDialog(11);//结束登录对话框
			return TRUE;//程序返回
		}
		wchar_t yhm[6] = { 0 };
		fseek(fp, 2, 0);
		fread(yhm, 2, 5, fp);
		用户名 = yhm;
		fclose(fp);
		UpdateData(false);//变量到编辑框
	}
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);//保证窗口在最前面
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void Cdenglu::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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


int Cdenglu::jiance()//检测文件是否正确
{
	if (0 != _wfopen_s(&fp, lujing, L"rb+"))
	{
		MessageBox(L"进入数据失败！");
		return 0;
	}
	fseek(fp, 0, SEEK_END);//文件指针移动到末尾
	int n = ftell(fp);//文件大小获取
	if (n == -1)
	{
		fclose(fp);
		MessageBox(L"数据库过大！");
		return 0;
	}
	fseek(fp, 0, 0);
	short bs;
	fread(&bs, 2, 1, fp);
	if (-29651 != bs)
	{
		fclose(fp);
		MessageBox(L"文件格式错误！");
		return 0;
	}
	if (n<525430)
	{
		fclose(fp);
		MessageBox(L"文件损坏！");
		return 0;
	}
	return 1;
}

void Cdenglu::OnDropFiles(HDROP hDropInfo)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	wchar_t filePath[5120];
	DragQueryFile(hDropInfo, 0, filePath, sizeof(filePath));//获取拖拽的第一个文件的路径
	lujing = filePath;
	CString s1;
	s1 = lujing.Right(4);
	s1.MakeUpper();//全变大写
	if (s1 != ".YSJ")
	{
		MessageBox(L"后缀名错误！");
		return;
	}
	if (0 == jiance()) return;  //错误检测
	fseek(fp, 15, 0);
	char c;
	fread(&c, 1, 1, fp);
	if (c >= 0) //是否存在密码
	{
		fseek(fp, 0, 0);//指针定位开头
		EndDialog(11);//结束登录对话框
		return;//程序返回
	}
	wchar_t yhm[6] = { 0 };
	fseek(fp, 2, 0);
	fread(yhm, 2, 5, fp);
	用户名 = yhm;
	fclose(fp);
	UpdateData(false);//变量到编辑框
	CDialogEx::OnDropFiles(hDropInfo);
}


BOOL Cdenglu::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (WM_KEYDOWN == pMsg->message && 13 == pMsg->wParam)
	{
		if (GetDlgItem(IDC_EDIT3) == GetFocus())
		{
			OnBnClicked_Queding();
			return FALSE;//进一步处理返回0值
		}
		else
		{
			return FALSE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
