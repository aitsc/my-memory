#pragma once
#include "atltime.h"
#include "afxcmn.h"
#include "afxwin.h"


// Cɸѡ �Ի���

class Cɸѡ : public CDialogEx
{
	DECLARE_DYNAMIC(Cɸѡ)

public:
	Cɸѡ(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cɸѡ();

// �Ի�������
	enum { IDD = IDD_shaixuan };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// ����ʱ��
	CTime m_cjsj1;
	// ����ʱ��
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
