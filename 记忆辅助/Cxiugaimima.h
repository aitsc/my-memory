#pragma once


// Cxiugaimima �Ի���

class Cxiugaimima : public CDialogEx
{
	DECLARE_DYNAMIC(Cxiugaimima)

public:
	Cxiugaimima(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cxiugaimima();

// �Ի�������
	enum { IDD = IDD_MIMA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString yuanmima;
	CString xinmima;
	CString querenmima;
};
