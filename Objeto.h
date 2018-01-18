#ifndef OBJETO_H
#define OBJETO_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <math.h>
#include <random>
#include <string>
#include "Nodo.h"
#include "Mapa.h"
#include "Mensaje.h""

class Objeto
{
private:
protected:
		int ataque_;
		int defensa_;
		int energia_;
		std::string nombre_;
		std::list<Nodo*> ruta_;
		char tag_;
		std::string tono_;
		int vidas_;
		int x_;
		int y_;

public:
		Objeto();
		Objeto(int, int, int, std::string, char, std::string, int, int, int);
		virtual ~Objeto();

	// ===================================================================================
	// GETTERS
	// ===================================================================================
		int  Get_Ataque();
		int  Get_Defensa();
		int  Get_Energia();
		std::string Get_Nombre();
		char Get_Tag();
		int  Get_Tono();
		int  Get_Vidas();
		int  Get_X();
		int  Get_Y();

	// ===================================================================================
	// SETTERS
	// ===================================================================================
		void Set_Ataque(int);
		void Set_Defensa(int);
		void Set_Energia(int);
		void Set_Tag(char);
		void Set_Tono(char);
		void Set_Vidas(int);
		void Set_X(int);
		void Set_Y(int);

	// ===================================================================================
	// MÉTODOS
	// ===================================================================================
	
		/// Movimiento -------------------------------------------------------------------
		void Mueve(int i, int, int);
		void Mueve_Por_Ruta();
		
		/// Pathfinding ------------------------------------------------------------------
		void Backtracking(int, int);
		void Busca_Caminos(int, int);
		
		/// Varios -----------------------------------------------------------------------
		virtual void Actualiza_Estado() = 0;
		virtual bool Gestiona_Mensaje(const Mensaje&) = 0;
		void Ver_Ruta();

};

#endif

