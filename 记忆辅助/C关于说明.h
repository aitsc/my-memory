#pragma once


// C关于说明 对话框

class C关于说明 : public CDialogEx
{
	DECLARE_DYNAMIC(C关于说明)

public:
	C关于说明(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C关于说明();

// 对话框数据
	enum { IDD = IDD_SHUOMING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString 说明;
	virtual BOOL OnInitDialog();
};
