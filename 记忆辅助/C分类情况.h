#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// C分类情况 对话框

class C分类情况 : public CDialogEx
{
	DECLARE_DYNAMIC(C分类情况)

public:
	C分类情况(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C分类情况();

// 对话框数据
	enum { IDD = IDD_FENLEI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int listbiaoshi[64];
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	CMenu menu;
	int showlist();
	afx_msg void OnBnClicked_zhenjia();
	afx_msg void OnBnClicked_shanchu();
	afx_msg void OnBnClicked_xiugai();
	afx_msg void OnBnClicked_yidong();
};
