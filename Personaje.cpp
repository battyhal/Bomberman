#include "Personaje.h"

Personaje::Personaje() : Objeto()
{
	bomba = 0;
	equipo.push_back(" ");
	puntos = 0;
}

Personaje::Personaje(int _ataque, int _defensa, int _energia, std::string _nombre, char _tag, 
					 int _vidas, int _x, int _y, int _puntos, std::string _equipo) 
					: Objeto(_ataque, _defensa, _energia, _nombre, _tag, _vidas, _x, _y)
{
	bomba = NULL;
	equipo.push_back(_equipo);
	puntos = _puntos;
}

Personaje::~Personaje() 
{
	bomba = 0;
	delete bomba;
}

// ---------------------------------------------------------------
// GETTERS 
// ---------------------------------------------------------------
int  Personaje::Get_Puntos() { return puntos; }

// ---------------------------------------------------------------
// SETTERS
// ---------------------------------------------------------------
void Personaje::Set_Puntos(int i) { puntos += i; }

// ---------------------------------------------------------------
// MODOS
// ---------------------------------------------------------------
Bomba* Personaje::Dejar_Bomba()
{
	bomba = new Bomba(1, 0, 1, "Bomba", '@', 10, x, y, 1, 10);
	return bomba;
}

// --------------------------------------------------------------------------
// VARIOS 
// --------------------------------------------------------------------------
void Personaje::Mostrar_Equipo(int i)
{
	if(i == 0)
	{
		for(unsigned int j = 0; j < equipo.size(); j++)
		{
			std::cout << " " << j << ".- " << equipo[j] << std::endl;  
		}
	}
	else std::cout << " " << i << ".- " << equipo[i] << std::endl;  
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
