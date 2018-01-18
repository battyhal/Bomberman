#ifndef BOMBA_H
#define BOMBA_H

#include <cassert>
#include <iostream>
#include "Estado.h"
#include "Maquina_Estados_Objetos.h"
#include "Objeto.h"

//class Estado;

class Bomba : public Objeto 
{
private:
	Maquina_Estados_Objetos<Bomba>* fsmBomba_;
	int radio_Accion_;
	int tiempo_vida_;
protected:
public:
	Bomba(int, int, int, std::string, char, std::string, int, int, int, int, int);
	Bomba(const Bomba&);
	~Bomba();

	// =======================================================================================
	// MÉTODOS
	// =======================================================================================
	void Actualiza_Estado(){ return; };
	bool Gestiona_Mensaje(const Mensaje&) { return false; };
	int  Cuenta_Atras();
};

#endif

