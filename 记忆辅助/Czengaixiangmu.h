#pragma once
#include "afxwin.h"


// Czengaixiangmu �Ի���

class Czengaixiangmu : public CDialogEx
{
	DECLARE_DYNAMIC(Czengaixiangmu)

public:
	Czengaixiangmu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Czengaixiangmu();

// �Ի�������
	enum { IDD = IDD_XGXM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	int zengjia;
	virtual BOOL OnInitDialog();
	CString wenti;
	CString daan;
	afx_msg void OnBnClicked_huhuan();
	afx_msg void OnBnClicked_Ok();
	afx_msg void OnBnClicked_Cancel();
	// ��Ͽ��������
	CComboBox box;
	short biaozhi;
	//���Ƿ������������λ��
	char Ĭ�����ӷ���;
};
