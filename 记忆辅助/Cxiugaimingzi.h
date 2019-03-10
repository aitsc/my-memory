#pragma once


// Cxiugaimingzi 对话框

class Cxiugaimingzi : public CDialogEx
{
	DECLARE_DYNAMIC(Cxiugaimingzi)

public:
	Cxiugaimingzi(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cxiugaimingzi();

// 对话框数据
	enum { IDD = IDD_MINGZI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 原名称
	CString yuanmz;
	// 新名称
	CString xinmz;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
//	afx_msg void OnEnChangeEdit1();
	int xiugaifenlei;
	char fenlei;
};
