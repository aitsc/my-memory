#pragma once
#include "afxwin.h"


// C卡片式 对话框

class C卡片式 : public CDialogEx
{
	DECLARE_DYNAMIC(C卡片式)

public:
	C卡片式(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C卡片式();

// 对话框数据
	enum { IDD = IDD_KAPIAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnMoving(UINT nSide, LPRECT pRect);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString wenti;
	CString daan;
	afx_msg void OnBnClicked_jizhule();
	afx_msg void OnBnClicked_wangjile();
	CMenu menu;
	HICON m_hIcon;
	int 卡片类型;
	CFont  font;     //字体对象
	afx_msg void OnBnClicked_huoqudaan();
	int shuaxin();
	// 用于刷新按钮和答案
//	HANDLE xiancheng;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 判断是否已按下其他按钮
	int keyi;
	afx_msg void OnIdcancel();
	afx_msg void On修改项目();
	afx_msg void On删除项目();
	afx_msg void On重学();
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
};
