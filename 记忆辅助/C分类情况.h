#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// C������� �Ի���

class C������� : public CDialogEx
{
	DECLARE_DYNAMIC(C�������)

public:
	C�������(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C�������();

// �Ի�������
	enum { IDD = IDD_FENLEI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int listbiaoshi[64];
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	CMenu menu;
	int showlist();
	afx_msg void OnBnClicked_zhenjia();
	afx_msg void OnBnClicked_shanchu();
	afx_msg void OnBnClicked_xiugai();
	afx_msg void OnBnClicked_yidong();
};
