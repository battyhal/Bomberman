#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H

#include<iostream>
#include"rlutil.h"

class Juego;

class EstadoJuego {
private:
protected:
public:
	virtual ~EstadoJuego(){}
	
	virtual bool Entra()   = 0;
	virtual void Realiza() = 0;
	virtual bool Sale()    = 0;
	
	virtual std::string Get_ID() const = 0;
		
};
#endif

