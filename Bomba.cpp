#include "Bomba.h"

Bomba::Bomba(int at, int def, int ener, std::string nom, char t, std::string to, int vi,
int x, int y, int rad, int ti)
	        : Objeto(at, def, ener, nom, t, to, vi, x, y)
{
	fsmBomba_ = NULL;
	radio_Accion_ = rad;
	tiempo_vida_  = ti;
}

Bomba::Bomba(const Bomba &arg)
{
	radio_Accion_ = arg.radio_Accion_;
	tiempo_vida_ = arg.tiempo_vida_;
}

Bomba::~Bomba() { delete fsmBomba_; }

// ---------------------------------------------------------------
// GETTERS
// ---------------------------------------------------------------


// ---------------------------------------------------------------
// MÉTODOS
// ---------------------------------------------------------------
int Bomba::Cuenta_Atras()
{
	tiempo_vida_--;
	if(tiempo_vida_ == 0)
		vidas_ = 0;
	return tiempo_vida_;
}
