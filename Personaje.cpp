#include "Personaje.h"

Personaje::Personaje() : Objeto()
{
	bomba_ = 0;
	equipo_.push_back(" ");
	puntos_ = 0;
}

Personaje::Personaje(int _ataque, int _defensa, int _energia, 
std::string _nombre, char _tag, std::string _tono, int _vidas,
int _x, int _y, int _puntos, std::string _equipo):Objeto(_ataque, _defensa,
_energia, _nombre, _tag, _tono, _vidas, _x, _y)
{
	bomba_ = NULL;
	equipo_.push_back(_equipo);
	puntos_ = _puntos;
}

Personaje::~Personaje()
{
	bomba_ = 0;
	delete bomba_;
}

// -----------------------------------------------------------------------
// GETTERS
// -----------------------------------------------------------------------
int  Personaje::Get_Puntos() { return puntos_; }

// -----------------------------------------------------------------------
// SETTERS
// -----------------------------------------------------------------------
void Personaje::Set_Puntos(int i) { puntos_ += i; }

// -----------------------------------------------------------------------
// MODOS
// -----------------------------------------------------------------------
Bomba* Personaje::Dejar_Bomba()
{
	bomba_ = new Bomba(1, 0, 1, "Bomba", '@', "verde", 10, x_, y_, 1, 10);
	return bomba_;
}

// -----------------------------------------------------------------------
// VARIOS
// -----------------------------------------------------------------------
void Personaje::Mostrar_Equipo(int i)
{
	if(i == 0)
	{
		for(unsigned int j = 0; j < equipo_.size(); j++)
		{
			std::cout << " " << j << ".- " << equipo_[j] << std::endl;
		}
	}
	else std::cout << " " << i << ".- " << equipo_[i] << std::endl;
}



/*

P => cargo las regiones de ese P
E => cargo también las de ese E

Problema? si descargo las de uno y son las que tiene que cargar otro
y se cargan primero las del que tiene que cargarlo y luego se descargan
las del que avanza, nos cargamos las que ha cargado el primero

Posible solución, recorrer todos los personajes y extraer todas las regiones
que deben ser cargadas a una lista, coger la lista previa y descargar las
regiones que no estén en la lista generada, cargar las regiones de la lista
generada que no estén en la lista cargada.

[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][C][C][C][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][C][E][C][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][C][C][C][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][C][C][C][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][C][P][C][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][C][C][C][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][C][C][C][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][C][E][C][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][C][C][C][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]

*/
