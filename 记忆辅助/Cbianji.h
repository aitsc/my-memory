#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Cbianji �Ի���

class Cbianji : public CDialogEx
{
	DECLARE_DYNAMIC(Cbianji)

public:
	Cbianji(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cbianji();

// �Ի�������
	enum { IDD = IDD_BIANJI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	CMenu menu;
	//�б��ʶ��˳��
	short listbiaoshi[32704];
	// ɸѡʱ���ǰʱ��
	short shijianq;
	// ɸѡʱ��ĺ�ʱ��
	short shijianh;
	// ���ĸ�����
	char fenlei;
	// ��ʲô״̬��
	char zhuangtai;
	// ˢ���б�
	int showlist();
	// ��������ʹ𰸵Ĺؼ���
	afx_msg void OnBnClicked_Zenjia();
	afx_msg void OnClose();
	afx_msg void OnBnClicked_Shanchu();
	afx_msg void OnBnClicked_Shaixuan();
	CString sousuo;
	afx_msg void OnBnClicked_Sousuo();
	afx_msg void OnBnClicked_Xiugai();
	afx_msg void OnBnClicked_Daoru();
	int ��������(FILE* fp);
	afx_msg void OnNMRDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	//���Ƿ������������λ��
	char Ĭ�����ӷ���;
	afx_msg void OnBnClicked_Chongxue();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int ��ǰҳ��;
	afx_msg void OnBnClicked_��һҳ();
	afx_msg void OnBnClicked_��һҳ();
	int ��ҳ��;
	int ��ҳ;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void �����ļ�(CString ��ַ);
};
