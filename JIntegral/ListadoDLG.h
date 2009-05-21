#pragma once
#include "afxcmn.h"


// CListadoDLG dialog

class CListadoDLG : public CDialog
{
	DECLARE_DYNAMIC(CListadoDLG)

public:
	CListadoDLG(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListadoDLG();

// Dialog Data
	enum { IDD = IDD_LISTADODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_LCListado;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void AddLista(const CString &ecuacion, const CString &error, const CString &desde, const CString &hasta, const CString &rectagulos, const CString &particion, const CString &resultado);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
