#pragma once


// CStressTransformDlg ��ȭ �����Դϴ�.

class CStressTransformDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStressTransformDlg)

public:
	CStressTransformDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CStressTransformDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_stressMin;
	int m_stressMax;
};
