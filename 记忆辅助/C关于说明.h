#pragma once


// C����˵�� �Ի���

class C����˵�� : public CDialogEx
{
	DECLARE_DYNAMIC(C����˵��)

public:
	C����˵��(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C����˵��();

// �Ի�������
	enum { IDD = IDD_SHUOMING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString ˵��;
	virtual BOOL OnInitDialog();
};
