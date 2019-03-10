#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Cbianji 对话框

class Cbianji : public CDialogEx
{
	DECLARE_DYNAMIC(Cbianji)

public:
	Cbianji(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Cbianji();

// 对话框数据
	enum { IDD = IDD_BIANJI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	CMenu menu;
	//列表标识的顺序
	short listbiaoshi[32704];
	// 筛选时间的前时间
	short shijianq;
	// 筛选时间的后时间
	short shijianh;
	// 是哪个分类
	char fenlei;
	// 是什么状态的
	char zhuangtai;
	// 刷新列表
	int showlist();
	// 搜索问题和答案的关键字
	afx_msg void OnBnClicked_Zenjia();
	afx_msg void OnClose();
	afx_msg void OnBnClicked_Shanchu();
	afx_msg void OnBnClicked_Shaixuan();
	CString sousuo;
	afx_msg void OnBnClicked_Sousuo();
	afx_msg void OnBnClicked_Xiugai();
	afx_msg void OnBnClicked_Daoru();
	int 导入数据(FILE* fp);
	afx_msg void OnNMRDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	//不是分类名，是相对位置
	char 默认增加分类;
	afx_msg void OnBnClicked_Chongxue();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int 当前页码;
	afx_msg void OnBnClicked_上一页();
	afx_msg void OnBnClicked_下一页();
	int 总页码;
	int 换页;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void 导入文件(CString 地址);
};
