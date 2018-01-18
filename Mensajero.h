#ifndef MENSAJERO_H
#define MENSAJERO_H

#include<set>
#include"Mensaje.h"

class Mensajero 
{
private:
	Mensaje* mensaje_;
	std::set<Mensaje*> colaMensajes_;
	
protected:
public:
	Mensajero();
	~Mensajero();
	
	// ===================================================================================
	// MÉTODOS
	// ===================================================================================
	void Entregar_Mensaje(int, long, void*, int);
	
	
};

#endif

