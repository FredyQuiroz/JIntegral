#pragma once
# define	PI				3.1415926535
# define	SEXAGESIMAL
# define	RAD(x)			PI*x/180

# define	DELIMITADOR		1
# define	VARIABLE		2
# define	NUMERO			3
# define	SIN				4
# define	COS				5
# define	RAIZ			6
# define	TAN				7
# define	LN				9
# define	LOG				10

class CParser
{
	bool		m_bSexagesimal;
	const char	*m_pszEcuacion;
	char		m_pszToken[80];
	double		m_nValue;
	char		m_cTipo_tok;
	int			m_nError;
	double		m_dResultado;
	void evalua( double *result);
	void adicion( double *result);
	void multiplicacion( double *result);
	void potencia( double *result);
	void signo( double *result);
	void trigonometricas( double *result);
	void parentesis( double *result);
	void obt_token( void);
	void monario(char o, double *result);
	void serror( int error);
	int esdelim( char c);
	void numero(double *result);
public:
	CParser(void);
	~CParser(void);
	double SetEcuacion(const CString &ecuacion, double valor=0);
	int GetError();
	char *GetStringError();
	void SetSexagesimal(bool sexagesimal);
};
