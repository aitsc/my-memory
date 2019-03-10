#pragma once


// C项目内容 对话框

class C项目内容 : public CDialogEx
{
	DECLARE_DYNAMIC(C项目内容)

public:
	C项目内容(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C项目内容();

// 对话框数据
	enum { IDD = IDD_ShuXing };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString wenti;
	CString daan;
	char duan;
};
