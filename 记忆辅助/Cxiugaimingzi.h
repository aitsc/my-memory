#pragma once


// Cxiugaimingzi �Ի���

class Cxiugaimingzi : public CDialogEx
{
	DECLARE_DYNAMIC(Cxiugaimingzi)

public:
	Cxiugaimingzi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Cxiugaimingzi();

// �Ի�������
	enum { IDD = IDD_MINGZI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ԭ����
	CString yuanmz;
	// ������
	CString xinmz;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
//	afx_msg void OnEnChangeEdit1();
	int xiugaifenlei;
	char fenlei;
};
