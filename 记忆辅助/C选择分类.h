#pragma once
#include "afxwin.h"


// C选择分类 对话框

class C选择分类 : public CDialogEx
{
	DECLARE_DYNAMIC(C选择分类)

public:
	C选择分类(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C选择分类();

// 对话框数据
	enum { IDD = IDD_xuanzhe };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox fenleibox;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	char fenlei;
	// 0代表不是反向
	int 是反向;
};
