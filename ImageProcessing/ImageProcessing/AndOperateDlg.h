#pragma once


// CAndOperateDlg ��ȭ �����Դϴ�.

class CAndOperateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAndOperateDlg)

public:
	CAndOperateDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAndOperateDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_AndValue;
};
