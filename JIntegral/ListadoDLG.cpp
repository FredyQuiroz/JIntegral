// ListadoDLG.cpp : implementation file
//

#include "stdafx.h"
#include "JIntegral.h"
#include "ListadoDLG.h"


// CListadoDLG dialog

IMPLEMENT_DYNAMIC(CListadoDLG, CDialog)

CListadoDLG::CListadoDLG(CWnd* pParent /*=NULL*/)
	: CDialog(CListadoDLG::IDD, pParent)
{

}

CListadoDLG::~CListadoDLG()
{
}

void CListadoDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LLISTADO, m_LCListado);
}


BEGIN_MESSAGE_MAP(CListadoDLG, CDialog)
	ON_BN_CLICKED(IDOK, &CListadoDLG::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CListadoDLG::OnBnClickedCancel)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CListadoDLG message handlers

void CListadoDLG::OnBnClickedOk()
{
	// OnOK();
}

void CListadoDLG::OnBnClickedCancel()
{
	ShowWindow(SW_HIDE);
	// OnCancel();
}

BOOL CListadoDLG::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_LCListado.InsertColumn(0, "Ecuacion");
	m_LCListado.InsertColumn(1, "Resultado");
	m_LCListado.InsertColumn(2, "Error");
	m_LCListado.InsertColumn(3, "rectangulos");
	m_LCListado.InsertColumn(4, "desde");
	m_LCListado.InsertColumn(5, "hasta");
	m_LCListado.InsertColumn(6, "particion");

	m_LCListado.SetExtendedStyle(LVS_EX_GRIDLINES);

	for(int i=0; i<m_LCListado.GetHeaderCtrl()->GetItemCount(); i++) 
		m_LCListado.SetColumnWidth(i, -2);
	return TRUE;
}

void CListadoDLG::AddLista(const CString &ecuacion, const CString &error, const CString &desde, const CString &hasta, const CString &rectagulos, const CString &particion, const CString &resultado) {

	if(IsWindow(m_LCListado)) {
		int pos =m_LCListado.InsertItem(m_LCListado.GetItemCount(), ecuacion);
		m_LCListado.SetItemText(pos, 1, resultado);
		m_LCListado.SetItemText(pos, 2, error);
		m_LCListado.SetItemText(pos, 3, rectagulos);
		m_LCListado.SetItemText(pos, 4, desde);
		m_LCListado.SetItemText(pos, 5, hasta);
		m_LCListado.SetItemText(pos, 6, particion);
		for(int i=0; i<m_LCListado.GetHeaderCtrl()->GetItemCount(); i++) 
			m_LCListado.SetColumnWidth(i, -1);
	}
}
void CListadoDLG::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if(IsWindow(m_LCListado)) {
		
		CRect rect;

		m_LCListado.GetWindowRect(rect);
		ScreenToClient(rect);
		rect.right= cx-10;
		rect.bottom= cy-10;
		m_LCListado.MoveWindow(rect);
	}
}
