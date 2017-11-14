#include "Bomba.h"

Bomba::Bomba(int _ataque, int _defensa, int _energia, std::string _nombre,
			 char _tag, int _vidas, int _x, int _y, int _radio, int _tiempo) 
	        : Objeto(_ataque, _defensa, _energia, _nombre, _tag, _vidas, _x, _y)
{
	radio_Accion = _radio;
	tiempo_vida  = _tiempo;
}

Bomba::Bomba(const Bomba &arg) 
{
	radio_Accion = arg.radio_Accion;
	tiempo_vida = arg.tiempo_vida;
	
	//return *this;
}

Bomba::~Bomba() {}

// ---------------------------------------------------------------
// GETTERS 
// ---------------------------------------------------------------


// ---------------------------------------------------------------
// MÉTODOS
// ---------------------------------------------------------------
int Bomba::Cuenta_Atras()
{
	tiempo_vida--;
	if(tiempo_vida == 0)
		vidas = 0;
	return tiempo_vida;
}
