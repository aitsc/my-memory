#pragma once
#include "afxwin.h"


// C移动分类 对话框

class C移动分类 : public CDialogEx
{
	DECLARE_DYNAMIC(C移动分类)

public:
	C移动分类(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C移动分类();

// 对话框数据
	enum { IDD = IDD_yidong };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox box1;
	CComboBox box2;
	afx_msg void OnBnClickedOk();
};
