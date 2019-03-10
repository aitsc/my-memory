
// 记忆辅助Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#define WM_USERtishi WM_USER+1

// C记忆辅助Dlg 对话框
class C记忆辅助Dlg : public CDialogEx
{
// 构造
public:
	C记忆辅助Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	int m_DockMode;//对话框停靠状态
	BOOL m_bHide;//true--对话框收起

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CMenu menu;
public:
	afx_msg void OnClose();
	afx_msg LRESULT Ontishi(WPARAM wParam, LPARAM lParam);
public:
	void shuaxin();
//	afx_msg void On32771();
	afx_msg void Onxiugaimingzi();
	afx_msg void Onxiugaimima();
//	afx_msg void On32773();
	afx_msg void Onchakanbianji();
	afx_msg void Onguanyu();
	afx_msg void OnBnClicked_Qiandao();
	afx_msg void OnBnClicked_Xuexi();
	afx_msg void OnBnClicked_Fuxi();
	afx_msg void OnBnClicked_Fanxiang();
	afx_msg void Onfenleiqingkuang();
	afx_msg void Ondaochu();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	virtual HRESULT accDoDefaultAction(VARIANT varChild);
	afx_msg void On新建用户();
	afx_msg void OnStnClicked_深入复习();

protected:
	//更改停靠状态，，当停靠时，安装ID == 1的计时器。并限制对话框移出主屏幕左/右/上边界
	afx_msg void OnMoving(UINT nSide, LPRECT pRect);
	//当１号计时器消息出现，而且对话框处于停靠状态，而且光标不在对话框内，
	//那么把对话框移出主屏幕边界，只留n个像素在主屏幕内，同时删除１号计时器。
	afx_msg void OnTimer(UINT nIDEvent);
	//当触发了这个消息时，对话框处于主屏幕边界之外，那么把对话框移进主屏幕边界，同时安装ID == 1的计时器。
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//慢慢移进/出对话框
	void AnimateShowHide(BOOL bHide);
public:
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
};
