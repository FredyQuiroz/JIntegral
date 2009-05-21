#pragma once


// CStaticGraph
# define MAX_POINTS	100

class CStaticGraph : public CStatic
{
	class CPointDouble {
	public:
		CPointDouble(double x=0, double y=0) {
			this->x= x;
			this->y=y;
		}
		void SetPoint(double x, double y) {
			this->x= x;
			this->y=y;
		}
		double x;
		double y;
	};
	DECLARE_DYNAMIC(CStaticGraph)
	CPointDouble	m_pPuntos[MAX_POINTS];
	CPtrArray		m_pRectangulos;
	int		m_nCurrentPoint;
	double		m_nMaxX;
	double		m_nMaxY;
	double		m_nMinX;
	double		m_nMinY;
	double	m_dParticionX;
	double	m_dParticionY;
	bool	m_bShowRectangles;
public:
	CStaticGraph();
	virtual ~CStaticGraph();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	virtual void PreSubclassWindow();
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
	void Clean();
	inline int GetX(double x);
	inline int GetY(double y);
	void AddPoint(double x, double y);
	void AddRectangulo(double x, double y);
	void ShowRectangles(bool show);
};


