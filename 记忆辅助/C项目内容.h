#pragma once


// C��Ŀ���� �Ի���

class C��Ŀ���� : public CDialogEx
{
	DECLARE_DYNAMIC(C��Ŀ����)

public:
	C��Ŀ����(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C��Ŀ����();

// �Ի�������
	enum { IDD = IDD_ShuXing };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString wenti;
	CString daan;
	char duan;
};
