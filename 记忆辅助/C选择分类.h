#pragma once
#include "afxwin.h"


// Cѡ����� �Ի���

class Cѡ����� : public CDialogEx
{
	DECLARE_DYNAMIC(Cѡ�����)

public:
	Cѡ�����(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cѡ�����();

// �Ի�������
	enum { IDD = IDD_xuanzhe };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox fenleibox;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	char fenlei;
	// 0�����Ƿ���
	int �Ƿ���;
};
