#pragma once


// C���ӷ��� �Ի���

class C���ӷ��� : public CDialogEx
{
	DECLARE_DYNAMIC(C���ӷ���)

public:
	C���ӷ���(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C���ӷ���();

// �Ի�������
	enum { IDD = IDD_ZENJIAFENLEI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString name;
};
