#pragma once
#include "afxwin.h"


// C�ƶ����� �Ի���

class C�ƶ����� : public CDialogEx
{
	DECLARE_DYNAMIC(C�ƶ�����)

public:
	C�ƶ�����(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C�ƶ�����();

// �Ի�������
	enum { IDD = IDD_yidong };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox box1;
	CComboBox box2;
	afx_msg void OnBnClickedOk();
};
