#pragma once
#include "afxwin.h"


// Czengaixiangmu 对话框

class Czengaixiangmu : public CDialogEx
{
	DECLARE_DYNAMIC(Czengaixiangmu)

public:
	Czengaixiangmu(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Czengaixiangmu();

// 对话框数据
	enum { IDD = IDD_XGXM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	int zengjia;
	virtual BOOL OnInitDialog();
	CString wenti;
	CString daan;
	afx_msg void OnBnClicked_huhuan();
	afx_msg void OnBnClicked_Ok();
	afx_msg void OnBnClicked_Cancel();
	// 组合框关联变量
	CComboBox box;
	short biaozhi;
	//不是分类名，是相对位置
	char 默认增加分类;
};
