
// ���丨��Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#define WM_USERtishi WM_USER+1

// C���丨��Dlg �Ի���
class C���丨��Dlg : public CDialogEx
{
// ����
public:
	C���丨��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	int m_DockMode;//�Ի���ͣ��״̬
	BOOL m_bHide;//true--�Ի�������

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	CMenu menu;
public:
	afx_msg void OnClose();
	afx_msg LRESULT Ontishi(WPARAM wParam, LPARAM lParam);
public:
	void shuaxin();
//	afx_msg void On32771();
	afx_msg void Onxiugaimingzi();
	afx_msg void Onxiugaimima();
//	afx_msg void On32773();
	afx_msg void Onchakanbianji();
	afx_msg void Onguanyu();
	afx_msg void OnBnClicked_Qiandao();
	afx_msg void OnBnClicked_Xuexi();
	afx_msg void OnBnClicked_Fuxi();
	afx_msg void OnBnClicked_Fanxiang();
	afx_msg void Onfenleiqingkuang();
	afx_msg void Ondaochu();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	virtual HRESULT accDoDefaultAction(VARIANT varChild);
	afx_msg void On�½��û�();
	afx_msg void OnStnClicked_���븴ϰ();

protected:
	//����ͣ��״̬������ͣ��ʱ����װID == 1�ļ�ʱ���������ƶԻ����Ƴ�����Ļ��/��/�ϱ߽�
	afx_msg void OnMoving(UINT nSide, LPRECT pRect);
	//�����ż�ʱ����Ϣ���֣����ҶԻ�����ͣ��״̬�����ҹ�겻�ڶԻ����ڣ�
	//��ô�ѶԻ����Ƴ�����Ļ�߽磬ֻ��n������������Ļ�ڣ�ͬʱɾ�����ż�ʱ����
	afx_msg void OnTimer(UINT nIDEvent);
	//�������������Ϣʱ���Ի���������Ļ�߽�֮�⣬��ô�ѶԻ����ƽ�����Ļ�߽磬ͬʱ��װID == 1�ļ�ʱ����
	afx_msg LRESULT OnNcHitTest(CPoint point);
	//�����ƽ�/���Ի���
	void AnimateShowHide(BOOL bHide);
public:
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
};
