
// JIntegralDlg.h: archivo de encabezado
//

#pragma once
#include "afxwin.h"
# include "Parser.h"
#include "StaticGraph.h"
#include "afxcmn.h"
# include "listadodlg.h"

// Cuadro de diálogo de CJIntegralDlg
class CJIntegralDlg : public CDialog
{
// Construcción
public:
	CJIntegralDlg(CWnd* pParent = NULL);	// Constructor estándar

// Datos del cuadro de diálogo
	enum { IDD = IDD_JINTEGRAL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV
	CParser	m_pParser;
	int		m_nCY;
	bool	m_bChanging;
	CListadoDLG m_dlgListado;


// Implementación
protected:
	HICON m_hIcon;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EEcuacion;
	CEdit m_EHasta;
	CEdit m_EDesde;
	CStaticGraph m_SGrafica;
	afx_msg void OnBnClickedOk();
	CStatic m_SMensaje;
	afx_msg void OnEnChangeEecuacion();
	afx_msg void OnEnChangeEdesde();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CStatic m_SResultado;
	CEdit m_EParticion;
	CProgressCtrl m_PCProgreso;
	CEdit m_ERectangulos;
	afx_msg void OnEnChangeErectangulos();
	afx_msg void OnEnChangeEparticion();
	CButton m_CRectangulos;
	afx_msg void OnBnClickedCrectangulos();
	afx_msg void OnEnChangeEhasta();
	CButton m_CListado;
	afx_msg void OnBnClickedClistado();
	CComboBox m_CBTipo;
	afx_msg void OnCbnSelchangeCtipo();
	CComboBox m_CBEjemplos;
	afx_msg void OnBnClickedBejemplo();
	afx_msg void OnCbnSelchangeCejemplos();
	afx_msg void OnBnClickedBayuda();
};
