// StaticGraph.cpp : implementation file
//

#include "stdafx.h"
#include "JIntegral.h"
#include "StaticGraph.h"
# include <math.h>

// CStaticGraph

IMPLEMENT_DYNAMIC(CStaticGraph, CStatic)

CStaticGraph::CStaticGraph()
{
	m_nCurrentPoint=0;
	m_nMaxX=1;
	m_nMaxY=1;
	m_nMinX=-1;
	m_nMinY=-1;
	m_bShowRectangles=true;
}

CStaticGraph::~CStaticGraph()
{
	Clean();
}


BEGIN_MESSAGE_MAP(CStaticGraph, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_DRAWITEM_REFLECT()
END_MESSAGE_MAP()

// CStaticGraph message handlers

void CStaticGraph::Clean() {

	m_nCurrentPoint=0;
	m_nMaxX=1;
	m_nMaxY=1;
	m_nMinX=-1;
	m_nMinY=-1;
	m_dParticionX=0;
	m_dParticionY=0;
	for(int i=0; i<m_pRectangulos.GetCount(); i++) {
		CPointDouble *punto= (CPointDouble *)m_pRectangulos[i];
		delete punto;
	}
	m_pRectangulos.RemoveAll();
}

void CStaticGraph::AddRectangulo(double x, double y) {

	if(x>m_nMaxX) 
		m_nMaxX=x;
	else if(x<m_nMinX)
		m_nMinX=x;
	if(y>m_nMaxY)
		m_nMaxY=y;
	else if(y<m_nMinY)
		m_nMinY=y;
	m_pRectangulos.Add(new CPointDouble(x,y));
}

void CStaticGraph::AddPoint(double x, double y) {

	if(m_nCurrentPoint>=MAX_POINTS)
		return;
	if(x>m_nMaxX) 
		m_nMaxX=x;
	else if(x<m_nMinX)
		m_nMinX=x;
	if(y>m_nMaxY)
		m_nMaxY=y;
	else if(y<m_nMinY)
		m_nMinY=y;
	m_pPuntos[m_nCurrentPoint].SetPoint(x, y);
	m_nCurrentPoint++;
}

int CStaticGraph::GetX(double x) {

	return m_dParticionX*(x-m_nMinX);
}

int CStaticGraph::GetY(double y) {

	return m_dParticionY*(m_nMaxY-y);
}

void CStaticGraph::ShowRectangles(bool show) {

	m_bShowRectangles=show;
	Invalidate();
}

# define CLARIDAD 100

BOOL CStaticGraph::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	// dibujamos el fondo blanco
	pDC->FillSolidRect(rect, RGB(255,255,255));
	
	m_dParticionX= rect.Width()/fabs((float)m_nMaxX-m_nMinX);
	m_dParticionY= rect.Height()/fabs((float)m_nMaxY-m_nMinY);

	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CPen gridx(PS_DASH, 1, RGB(255,CLARIDAD,CLARIDAD));

	CPen *oldPen= pDC->SelectObject(&gridx);
	pDC->SetTextColor(RGB(255,CLARIDAD,CLARIDAD));

	// ahora dibujamos las grillas
	double intervalo= (m_nMaxY-m_nMinY)/4;
	CString temp;
	for(double valor=m_nMinY+intervalo; valor<m_nMaxY; valor+=intervalo ) {

		temp.Format("y=%g", valor);
		pDC->TextOut(GetX(m_nMinX),GetY(valor),temp);
		pDC->MoveTo(GetX(m_nMinX), GetY(valor));
		pDC->LineTo(GetX(m_nMaxX), GetY(valor));
	}

	CPen gridy(PS_DASH, 1, RGB(CLARIDAD,255,CLARIDAD));
	pDC->SelectObject(&gridy);
	pDC->SetTextColor(RGB(CLARIDAD,255,CLARIDAD));

	intervalo= (m_nMaxX-m_nMinX)/4;
	for(double valor=m_nMinX+intervalo; valor<m_nMaxX; valor+=intervalo ) {

		temp.Format("x=%g", valor);
		pDC->TextOut(GetX(valor),GetY(m_nMinY)-18,temp);
		pDC->MoveTo(GetX(valor), GetY(m_nMinY));
		pDC->LineTo(GetX(valor), GetY(m_nMaxY));
	}

	pDC->SelectObject(&pen);

	// dibujamos el eje X
	pDC->MoveTo(GetX(m_nMinX), GetY(0));
	pDC->LineTo(GetX(m_nMaxX), GetY(0));

	// dibujamos el eje y
	pDC->MoveTo(GetX(0), GetY(m_nMinY));
	pDC->LineTo(GetX(0), GetY(m_nMaxY));

	pDC->SelectObject(oldPen);
	return TRUE;
}

void CStaticGraph::PreSubclassWindow()
{
	CStatic::PreSubclassWindow();
	ModifyStyle(0, SS_OWNERDRAW);
}

void CStaticGraph::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
		
	CRect rect;
	GetClientRect(rect);

	m_dParticionX= rect.Width()/fabs((float)m_nMaxX-m_nMinX);
	m_dParticionY= rect.Height()/fabs((float)m_nMaxY-m_nMinY);

	CDC*  pDC     = CDC::FromHandle(lpDrawItemStruct->hDC);

	CPen pen(PS_SOLID, 1, RGB(0,0,255));
	CPen *pPen= pDC->SelectObject(&pen);

	// dibujamos la grafica
	CPoint puntos[MAX_POINTS];
	for(int i=0; i<MAX_POINTS; i++) {
		
		// pDC->SetPixel(GetX(m_pPuntos[i].x), GetY(m_pPuntos[i].y), RGB(0,0,255));
		puntos[i].SetPoint(GetX(m_pPuntos[i].x), GetY(m_pPuntos[i].y));
	}
	pDC->MoveTo(puntos[0].x, puntos[0].y);
	pDC->PolylineTo(puntos, MAX_POINTS);

	// ahora dibujamos los rectangulos
	if(m_bShowRectangles) {
		CPen pen1(PS_SOLID, 1, RGB(255,0,255));
		CBrush *oldbrush= (CBrush *)pDC->SelectStockObject(NULL_BRUSH);
		pDC->SelectObject(&pen1);

		for(int i=0;i<m_pRectangulos.GetCount()-1; i++) {
			
			CPointDouble *uno= (CPointDouble *)m_pRectangulos[i];
			CPointDouble *dos= (CPointDouble *)m_pRectangulos[i+1];

			rect.SetRect(GetX(uno->x), GetY(0), GetX(dos->x), GetY(dos->y));
			pDC->Rectangle(rect);
		}
		pDC->SelectObject(oldbrush);
	}
	pDC->SelectObject(pPen);
}
