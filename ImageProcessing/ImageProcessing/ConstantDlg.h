#pragma once


// CConstantDlg ��ȭ �����Դϴ�.

class CConstantDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConstantDlg)

public:
	CConstantDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConstantDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	double m_Constant;
};
