
// JIntegralDlg.cpp: archivo de implementación
//

#include "stdafx.h"
#include "JIntegral.h"
#include "JIntegralDlg.h"
# include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cuadro de diálogo de CJIntegralDlg




CJIntegralDlg::CJIntegralDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJIntegralDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bChanging=false;
}

void CJIntegralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EECUACION, m_EEcuacion);
	DDX_Control(pDX, IDC_EHASTA, m_EHasta);
	DDX_Control(pDX, IDC_EDESDE, m_EDesde);
	DDX_Control(pDX, IDC_SGRAFICA, m_SGrafica);
	DDX_Control(pDX, IDC_SMENSAJE, m_SMensaje);
	DDX_Control(pDX, IDC_SRESULTADO, m_SResultado);
	DDX_Control(pDX, IDC_EPARTICION, m_EParticion);
	DDX_Control(pDX, IDC_PPROGRESO, m_PCProgreso);
	DDX_Control(pDX, IDC_ERECTANGULOS, m_ERectangulos);
	DDX_Control(pDX, IDC_CRECTANGULOS, m_CRectangulos);
	DDX_Control(pDX, IDC_CLISTADO, m_CListado);
	DDX_Control(pDX, IDC_CTIPO, m_CBTipo);
	DDX_Control(pDX, IDC_CEJEMPLOS, m_CBEjemplos);
}

BEGIN_MESSAGE_MAP(CJIntegralDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CJIntegralDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EECUACION, &CJIntegralDlg::OnEnChangeEecuacion)
	ON_EN_CHANGE(IDC_EDESDE, &CJIntegralDlg::OnEnChangeEdesde)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_ERECTANGULOS, &CJIntegralDlg::OnEnChangeErectangulos)
	ON_EN_CHANGE(IDC_EPARTICION, &CJIntegralDlg::OnEnChangeEparticion)
	ON_BN_CLICKED(IDC_CRECTANGULOS, &CJIntegralDlg::OnBnClickedCrectangulos)
	ON_EN_CHANGE(IDC_EHASTA, &CJIntegralDlg::OnEnChangeEhasta)
	ON_BN_CLICKED(IDC_CLISTADO, &CJIntegralDlg::OnBnClickedClistado)
	ON_CBN_SELCHANGE(IDC_CTIPO, &CJIntegralDlg::OnCbnSelchangeCtipo)
	ON_BN_CLICKED(IDC_BEJEMPLO, &CJIntegralDlg::OnBnClickedBejemplo)
	ON_CBN_SELCHANGE(IDC_CEJEMPLOS, &CJIntegralDlg::OnCbnSelchangeCejemplos)
	ON_BN_CLICKED(IDC_BAYUDA, &CJIntegralDlg::OnBnClickedBayuda)
END_MESSAGE_MAP()

// Controladores de mensaje de CJIntegralDlg

BOOL CJIntegralDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de diálogo. El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	m_CBEjemplos.AddString("sen(x)");
	m_CBEjemplos.AddString("cos(x)");
	m_CBEjemplos.AddString("tan(x)");
	m_CBEjemplos.AddString("x^2");
	m_CBEjemplos.AddString("raiz(x)");
	m_CBEjemplos.AddString("2*sen(x)+x");
	m_CBEjemplos.AddString("sen(x)+x/2");
	m_CBEjemplos.AddString("1/x");
	m_CBEjemplos.AddString("x^4-x^2+1");
	m_CBEjemplos.SetCurSel(0);
	

	m_EEcuacion.SetWindowText(AfxGetApp()->GetProfileString("ecuacion", "ecuacion"));
	m_EDesde.SetWindowText(AfxGetApp()->GetProfileString("ecuacion", "desde", "0"));
	m_EHasta.SetWindowText(AfxGetApp()->GetProfileString("ecuacion", "hasta", "1"));
	m_EParticion.SetWindowText(AfxGetApp()->GetProfileString("ecuacion", "particion", "0.0001"));
	m_CRectangulos.SetCheck(AfxGetApp()->GetProfileInt("ecuacion", "show", 1));
	m_SGrafica.ShowRectangles(m_CRectangulos.GetCheck());
	m_CListado.SetCheck(1);
	m_CBTipo.AddString("Sexagesimal");
	m_CBTipo.AddString("Radian");
	m_CBTipo.SetCurSel(AfxGetApp()->GetProfileInt("ecuacion", "sexagesimal", 1));
	OnCbnSelchangeCtipo();

	CRect rect;
	GetWindowRect(rect);
	m_nCY= rect.Height();

	m_dlgListado.Create(CListadoDLG::IDD,this);
	return TRUE;
}

void CJIntegralDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono. Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CJIntegralDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CJIntegralDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CJIntegralDlg::OnBnClickedOk()
{
	CString desde, hasta,ecuacion,particion, rectangulo;
	m_EDesde.GetWindowText(desde);
	if(desde.IsEmpty()) {
		MessageBox("Por favor ingrese un limite desde");
		m_EDesde.SetFocus();
		return;
	}
	if(atof(desde)==NULL && desde!="0") {
		MessageBox("Por favor ingrese un valor valido para desde");
		m_EDesde.SetFocus();
		return;
	}
	m_EHasta.GetWindowText(hasta);
	if(hasta.IsEmpty()) {
		MessageBox("Por favor ingrese un limite hasta");
		m_EHasta.SetFocus();
		return;
	}
	if(atof(hasta)==NULL && hasta!="0") {
		MessageBox("Por favor ingrese un valor valido para hasta");
		m_EHasta.SetFocus();
		return;
	}
	if(atof(desde)==atof(hasta)) {

		MessageBox("Los limites no pueden ser iguales");
		m_EHasta.SetFocus();
		return;
	}
	m_EParticion.GetWindowText(particion);
	if(particion.IsEmpty()) {
		MessageBox("Por favor ingrese un valor para las particiones");
		m_EParticion.SetFocus();
		return;
	}
	if(atof(particion)==NULL) {
		MessageBox("Por favor ingrese un valor valido para la particion o el rectangulo");
		m_EParticion.SetFocus();
		return;
	}
	m_EEcuacion.GetWindowText(ecuacion);
	if(ecuacion.IsEmpty()) {
		MessageBox("Por favor ingrese una ecuacion");
		m_EEcuacion.SetFocus();
		return;
	}
	m_pParser.SetEcuacion(ecuacion);
	if(m_pParser.GetError()) {

		MessageBox("Por favor ingrese una ecuacion valida");
		m_EEcuacion.SetFocus();
		return;
	}
	m_ERectangulos.GetWindowText(rectangulo);

	AfxGetApp()->WriteProfileString("ecuacion", "ecuacion", ecuacion);
	AfxGetApp()->WriteProfileString("ecuacion", "desde", desde);
	AfxGetApp()->WriteProfileString("ecuacion", "hasta", hasta);
	AfxGetApp()->WriteProfileString("ecuacion", "particion", particion);

	CWaitCursor wait;

	int posicion;
	// realizamos la grafica
	double minimo= atof(desde);
	double maximo= atof(hasta);

	// limpiamos la grafica
	m_SGrafica.Clean();

	// ahora calculamos el area bajo la curva
	m_SMensaje.SetWindowText("Calculando Patrón con 1.000.000 de rectangulos");
	m_PCProgreso.SetPos(0);
	double patron=0;
	double dparticion= fabs(maximo-minimo)/1000000;
	for(double valor=minimo;valor<=maximo; valor+=dparticion) {
		posicion= abs((valor-minimo)/(maximo-minimo)*100);
		if(posicion!=m_PCProgreso.GetPos())
			m_PCProgreso.SetPos(posicion);
		double y= m_pParser.SetEcuacion(ecuacion, valor);
		patron+=y*dparticion;
	}
	m_PCProgreso.SetPos(100);
	
	m_SMensaje.SetWindowText("Calculando Area");
	m_PCProgreso.SetPos(0);
	double areatotal=0;
	dparticion= atof(particion);
	for(double valor=minimo;valor<=maximo; valor+=dparticion) {
		posicion= abs((valor-minimo)/(maximo-minimo)*100);
		if(posicion!=m_PCProgreso.GetPos())
			m_PCProgreso.SetPos(posicion);
		double y= m_pParser.SetEcuacion(ecuacion, valor);
		m_SGrafica.AddRectangulo(valor, y);
		areatotal+=y*dparticion;
	}
	m_PCProgreso.SetPos(100);
	CString resultado,error;
	resultado.Format("%lf", areatotal);
	error.Format("%lf", fabs(patron-areatotal));
	m_SResultado.SetWindowText("dx = " + resultado + " ± " + error);

	double intervalo= fabs((float)maximo-minimo)/MAX_POINTS;

	m_SMensaje.SetWindowText("Dibujando ecuacion");
	m_PCProgreso.SetPos(0);

	for( double valor= minimo; valor<=maximo; valor+=intervalo) { 
		posicion= abs((valor-minimo)/(maximo-minimo)*100);
		if(posicion!=m_PCProgreso.GetPos())
			m_PCProgreso.SetPos(posicion);
		m_SGrafica.AddPoint(valor, m_pParser.SetEcuacion(ecuacion, valor));
	}
	m_PCProgreso.SetPos(100);
	m_SGrafica.Invalidate();

	m_dlgListado.AddLista(ecuacion, error, desde, hasta, rectangulo, particion, resultado);
	if(!m_dlgListado.IsWindowVisible()) {

		CRect rect;
		GetWindowRect(rect);
		rect.left= rect.right-rect.Width()/3;
		m_dlgListado.MoveWindow(rect);
	}
	if(m_CListado.GetCheck())
		m_dlgListado.ShowWindow(SW_SHOW);

	m_SMensaje.SetWindowText("Listo");
}

void CJIntegralDlg::OnEnChangeEecuacion()
{
	CString ecuacion, desde;
	m_EEcuacion.GetWindowText(ecuacion);
	if(ecuacion.IsEmpty()) {
		
		m_SMensaje.SetWindowText("");
		return;
	}
	m_EDesde.GetWindowText(desde);
	if(atof(desde)==NULL && desde!="0") {
		m_SMensaje.SetWindowText("Por favor ingrese un valor valido para desde");
		return;
	}
	m_pParser.SetEcuacion(ecuacion, atof(desde));
	m_SMensaje.SetWindowText(m_pParser.GetStringError());
}

void CJIntegralDlg::OnEnChangeEdesde()
{
	OnEnChangeErectangulos();
}

void CJIntegralDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if(IsWindow(m_SGrafica) && nType!=SIZE_MINIMIZED) {
		CWnd *child= GetNextWindow(GW_CHILD);
		while(child) {
			CRect rect;
			child->GetWindowRect(rect);
			ScreenToClient(rect);
			if(child==&m_SGrafica) {
				rect.right=cx-5;
				rect.bottom+= cy-m_nCY;
			} else {
				rect.MoveToY(rect.top+(cy-m_nCY));
			}
			child->MoveWindow(rect);
			child= child->GetNextWindow();
		}
		m_nCY= cy;
		Invalidate();
	}
}

void CJIntegralDlg::OnEnChangeErectangulos()
{
	// actualizamos el tamano de las particiones
	if(m_bChanging)
		return;
	m_bChanging=true;
	CString temp;
	m_ERectangulos.GetWindowText(temp);
	int rectangulos= atoi(temp);
	if(rectangulos) {
		m_EDesde.GetWindowText(temp);
		double desde= atof(temp);
		m_EHasta.GetWindowText(temp);
		double hasta= atof(temp);
		double particion= fabs(hasta-desde)/rectangulos;
		temp.Format("%g", particion);
		m_EParticion.SetWindowText(temp);
		OnEnChangeEecuacion();
	} else {
		m_SMensaje.SetWindowText("Por favor ingrese un valor !=0");
	}
	m_bChanging=false;
}

void CJIntegralDlg::OnEnChangeEparticion()
{
	// actualizamos los rectangulos
	if(m_bChanging)
		return;
	m_bChanging=true;
	CString temp;
	m_EParticion.GetWindowText(temp);
	double particion= atof(temp);
	if(particion) {
		m_EDesde.GetWindowText(temp);
		double desde= atof(temp);
		m_EHasta.GetWindowText(temp);
		double hasta= atof(temp);
		int rectangulo= (int) ceil(fabs(hasta-desde)/particion);
		temp.Format("%d", rectangulo);
		m_ERectangulos.SetWindowText(temp);
		OnEnChangeEecuacion();
	} else {
		m_SMensaje.SetWindowText("Por favor ingrese un valor !=0");
	}
	m_bChanging=false;
}

void CJIntegralDlg::OnBnClickedCrectangulos()
{
	AfxGetApp()->WriteProfileInt("ecuacion", "show", m_CRectangulos.GetCheck());
	m_SGrafica.ShowRectangles(m_CRectangulos.GetCheck());
}

void CJIntegralDlg::OnEnChangeEhasta()
{
	OnEnChangeErectangulos();
}

void CJIntegralDlg::OnBnClickedClistado()
{
	m_dlgListado.ShowWindow(m_CListado.GetCheck() ? SW_SHOW : SW_HIDE);
}

void CJIntegralDlg::OnCbnSelchangeCtipo()
{
	AfxGetApp()->WriteProfileInt("ecuacion", "sexagesimal", m_CBTipo.GetCurSel());
	m_pParser.SetSexagesimal(m_CBTipo.GetCurSel()==1);
}

void CJIntegralDlg::OnBnClickedBejemplo()
{
	CString temp;
	m_CBEjemplos.GetWindowText(temp);
	m_EEcuacion.SetWindowText(temp);
}

void CJIntegralDlg::OnCbnSelchangeCejemplos()
{
	OnBnClickedBejemplo();
}

void CJIntegralDlg::OnBnClickedBayuda()
{
	ShellExecute(NULL, "open", "ayuda.html", NULL, NULL, SW_NORMAL);
}
