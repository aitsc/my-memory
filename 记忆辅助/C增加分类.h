#pragma once


// C增加分类 对话框

class C增加分类 : public CDialogEx
{
	DECLARE_DYNAMIC(C增加分类)

public:
	C增加分类(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C增加分类();

// 对话框数据
	enum { IDD = IDD_ZENJIAFENLEI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString name;
};
