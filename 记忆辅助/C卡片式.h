#pragma once
#include "afxwin.h"


// C��Ƭʽ �Ի���

class C��Ƭʽ : public CDialogEx
{
	DECLARE_DYNAMIC(C��Ƭʽ)

public:
	C��Ƭʽ(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C��Ƭʽ();

// �Ի�������
	enum { IDD = IDD_KAPIAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnMoving(UINT nSide, LPRECT pRect);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString wenti;
	CString daan;
	afx_msg void OnBnClicked_jizhule();
	afx_msg void OnBnClicked_wangjile();
	CMenu menu;
	HICON m_hIcon;
	int ��Ƭ����;
	CFont  font;     //�������
	afx_msg void OnBnClicked_huoqudaan();
	int shuaxin();
	// ����ˢ�°�ť�ʹ�
//	HANDLE xiancheng;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// �ж��Ƿ��Ѱ���������ť
	int keyi;
	afx_msg void OnIdcancel();
	afx_msg void On�޸���Ŀ();
	afx_msg void Onɾ����Ŀ();
	afx_msg void On��ѧ();
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
};
