#ifndef ESTADO_H
#define ESTADO_H

#include <iostream>

class Mensaje;

template<class entidad>
class Estado 
{
private:
protected:
public:
	virtual ~Estado(){}
	
	virtual void Entra(entidad*)   = 0;
	virtual void Realiza(entidad*) = 0;
	virtual void Sale(entidad*)    = 0;
	virtual bool Transmite_Mensaje(entidad*, const Mensaje&) = 0;
};
#endif
