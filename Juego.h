#ifndef JUEGO_H
#define JUEGO_H

#include <fstream>
#include <list>
#include "Auxiliar.h"
#include "Bomba.h"
#include "Mapa.h"
#include "NPC.h"
#include "Objeto.h"
#include "Personaje.h"
#include "rlutil.h"

class Juego {
friend class Auxiliar;
private:
	Bomba* bomba;
	Personaje* Bomberman;
	Mapa mapa;
	std::list<Objeto*> objetos;
	bool salir;
	int  turnos;
	
protected:
public:
	Juego();
	Juego(std::string nivelTxt);
	Juego& operator=(const Juego& otro);
	~Juego();

	// GETTERS
	bool Get_Salir() const;
	std::list<Objeto*> Get_Objetos() const;
	
	// SETTERS

	// MÉTODOS
	void Actualizar();
	void Crear_Objetos();
	void Game_Over();
	void Jugar();
	void Mover_NPC();
	void Mover_Personaje();
	void Muerto();

	void Presentacion();
	void Puntuacion();
		
};

#endif



