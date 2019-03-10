#pragma once


// Cxiugaimima 对话框

class Cxiugaimima : public CDialogEx
{
	DECLARE_DYNAMIC(Cxiugaimima)

public:
	Cxiugaimima(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cxiugaimima();

// 对话框数据
	enum { IDD = IDD_MIMA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString yuanmima;
	CString xinmima;
	CString querenmima;
};
