#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>
#include "Bomba.h"
#include "Objeto.h"

class Personaje : public Objeto
{

private:
	Bomba * bomba_;
	std::vector<std::string> equipo_;
	int  puntos_;

protected:
public:
	Personaje();
	Personaje(int _ataque, int _defensa, int _energia, std::string _nombre,
		char _tag, std::string _tono, int _vidas, int _x, int _y,
		int _puntos, std::string _equipo);
	~Personaje();

	// Getters
	int  Get_Puntos();

	// Setters
	void Set_Puntos(int i);

	// Modos
	Bomba* Dejar_Bomba();

	// Varios
	virtual void Actualiza_Estado() { return; };
	void Mostrar_Equipo(int);
	virtual bool Gestiona_Mensaje(const Mensaje&) { return false; }
};
#endif

