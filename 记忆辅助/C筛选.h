#pragma once
#include "atltime.h"
#include "afxcmn.h"
#include "afxwin.h"


// C筛选 对话框

class C筛选 : public CDialogEx
{
	DECLARE_DYNAMIC(C筛选)

public:
	C筛选(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C筛选();

// 对话框数据
	enum { IDD = IDD_shaixuan };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// 最早时间
	CTime m_cjsj1;
	// 最晚时间
	CTime m_cjsj2;
//	CComboBoxEx fenleibox;
//	CComboBoxEx zhuangtaibox;
	afx_msg void OnBnClicked_Ok();
	CComboBox fenleibox;
	CComboBox zhuangtaibox;
	short shijianq;
	short shijianh;
	char fenlei;
	char zhuangtai;
};
