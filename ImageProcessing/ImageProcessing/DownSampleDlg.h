#pragma once


// CDownSampleDlg ��ȭ �����Դϴ�.

class CDownSampleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDownSampleDlg)

public:
	CDownSampleDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDownSampleDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_DownSampleRate;
};
