#pragma once


// Cdenglu 对话框

class Cdenglu : public CDialogEx
{
	DECLARE_DYNAMIC(Cdenglu)

public:
	Cdenglu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cdenglu();

// 对话框数据
	enum { IDD = IDD_DENGLU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked_Xinjian();
public:
	afx_msg void OnBnClicked_Dakai();
	CString lujing;
	CString mima;
	afx_msg void OnBnClicked_Queding();
	afx_msg void OnClose();
	FILE *fp;
protected:
	HICON m_hIcon;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	int jiance();
	CString 用户名;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
