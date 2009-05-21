#include "StdAfx.h"
#include "parser.h"
# include <math.h>

CParser::CParser(void)
{
	m_nError=0;
	m_dResultado=0;
	m_pszEcuacion=0;
	m_nValue=0;
	m_bSexagesimal=true;
}

CParser::~CParser(void)
{
}

void CParser::evalua( double *result) {

	obt_token();
	if(!*m_pszToken) {

		serror(2);
		return;
	}
	adicion(result);
}

void CParser::adicion( double *result) {

	char op;
	double temp;
	multiplicacion( result);
	while( (op=*m_pszToken)== '+' || (op=*m_pszToken)== '-') {

		obt_token();
		multiplicacion(&temp);
		switch( op) {

			case '-':
				*result= *result-temp;
				break;
			case '+':
				*result= *result+temp;
				break;
		}
	}
}

void CParser::multiplicacion( double *result) {

	char op;
	double temp;
	potencia( result);
	while( (op=*m_pszToken)== '*' || (op=*m_pszToken)== '/' || (op=*m_pszToken)== '%') {

		obt_token();
		potencia(&temp);
		switch( op) {

			case '*':
				*result= *result*temp;
				break;
			case '/':
				*result= *result/temp;
				break;
			case '%':
				*result= (int) *result%(int)temp;
				break;
		}
	}
}

void CParser::potencia( double *result) {

	double temp=0, ex;
	int t;
	signo( result);
	if( *m_pszToken== '^') {

		obt_token();
		potencia(&temp);
		ex= *result;
		if( temp==0.0) {

			*result= 1.0;
			return;
		}
		for( t=(int)temp-1; t>0; --t) *result= (*result)*(double) ex;
	}
}

void CParser::signo( double *result) {

	char op=0;

	if( (m_cTipo_tok== DELIMITADOR) && *m_pszToken=='+' || *m_pszToken== '-') {

		op= *m_pszToken;
		obt_token();
	}
	trigonometricas(result);
	if( op=='-') *result= -(*result);
}

void CParser::trigonometricas( double *result) {

	char op=0;

	if( (m_cTipo_tok>= SIN)) {

		op= m_cTipo_tok;
		obt_token();
	}
	parentesis(result);
	if( op>=SIN) {
	
		if(m_bSexagesimal && (op==SIN || op==COS || op==TAN)) 
			*result= RAD(*result);
		if( op==SIN)
			*result= sin(*result);
		else if( op==COS)
			*result= cos(*result);
		else if( op==TAN)
			*result= tan(*result);
		else if( op==RAIZ)
			*result= sqrt(*result);
		else if(op==LN)
			*result= log(*result); 
		else if(op==LOG)
			*result= log10(*result);
	}
}

void CParser::parentesis( double *result) {

	if((*m_pszToken== '(')) {

		obt_token();
		adicion(result);
		if(*m_pszToken!=')')
			serror(1);
		obt_token();
	}
	else numero(result);
}

void CParser::numero( double *result) {

	if( m_cTipo_tok==NUMERO) {

		if(m_pszToken[0]=='x')
			*result= m_nValue;
		else if(m_pszToken[0]=='e')
			*result= exp((double)1);
		else *result= atof( m_pszToken);
		obt_token();
		return;
	}
	serror(0);
}

void CParser::serror( int error) {

	m_nError= error+1;
}

void CParser::obt_token( void) {

	char *temp;
	m_cTipo_tok=0;
	for( int i=0; i<80; i++) {
		if( m_pszToken[i]==0)
			break;
		m_pszToken[i]=0;
	}
	temp=m_pszToken;
	*temp= '\0';
	if(!*m_pszEcuacion) return;
	while(isspace(*m_pszEcuacion)) 
		++m_pszEcuacion;
	if( strchr("+-*/^%=()", *m_pszEcuacion)) {

		m_cTipo_tok= DELIMITADOR;
		*temp++= *m_pszEcuacion++;
	} else if(*m_pszEcuacion=='x' || *m_pszEcuacion=='e') {
		m_cTipo_tok= NUMERO;
		*temp++= *m_pszEcuacion++;
	} else if(!strncmp(m_pszEcuacion,"sen", 3)|| !strncmp(m_pszEcuacion,"cos",3)
			|| !strncmp(m_pszEcuacion,"tan",3) || !strncmp(m_pszEcuacion,"raiz",4)) {

		if( *m_pszEcuacion=='s')
			m_cTipo_tok= SIN;
		else if( *m_pszEcuacion=='r')
			m_cTipo_tok= RAIZ;
		else if( *m_pszEcuacion=='c')
			m_cTipo_tok= COS;
		else if( *m_pszEcuacion=='t')
			m_cTipo_tok=TAN;
		m_pszEcuacion++;
		m_pszEcuacion++;
		if( m_cTipo_tok==RAIZ) 
			m_pszEcuacion++;
		*temp++=*m_pszEcuacion++;
	} else if(!strncmp(m_pszEcuacion,"ln",2) || !strncmp(m_pszEcuacion, "log", 3)) {
		m_pszEcuacion++;
		if(*m_pszEcuacion=='o') {
			m_cTipo_tok=LOG;
			m_pszEcuacion++;
		} else m_cTipo_tok=LN;
		*temp++=*m_pszEcuacion++;
	} else if( isalpha( *m_pszEcuacion)) {
		while( !esdelim(*m_pszEcuacion)) 
			*temp++=*m_pszEcuacion++;
		m_cTipo_tok= VARIABLE;
	} else if( isdigit(*m_pszEcuacion)) {

		while( !esdelim(*m_pszEcuacion)) *temp++=*m_pszEcuacion++;
		m_cTipo_tok=NUMERO;
	}
	temp= '\0';
}

int CParser::esdelim( char c) {

	if( strchr(" +-/*%^=()",c) || c==9 || c=='\r' || c==0)
		return 1;
	return 0;
}

double CParser::SetEcuacion(const CString &ecuacion, double valor) {
	
	if( !ecuacion)
		return 0;
	
	m_pszEcuacion= (const char *) ecuacion;
	m_nValue= valor;
	m_nError= 0;
	evalua( &m_dResultado);
	return m_dResultado;
}

int CParser::GetError() {

	return m_nError;
}

char *CParser::GetStringError() {

	static char *e[]= {
		"",
		"Error de sintaxis",
		"Parentesis no emparejados",
		"No hay expresion"
	};
	return e[m_nError];
}

void CParser::SetSexagesimal(bool sexagesimal) {

	m_bSexagesimal=sexagesimal;
}