#ifndef JUEGO_H
#define JUEGO_H

#include <fstream>
#include <list>
#include "Bomba.h"
#include "Mapa.h"
#include "NPC.h"
#include "Objeto.h"
#include "Personaje.h"
#include "rlutil.h"

class Juego {
private:
	Bomba* bomba;
	Personaje* Bomberman;
	Mapa mapa;
	std::list<Objeto*> objetos;
	std::list<Objeto*>::iterator Obj;
	std::list<Objeto*>::iterator Obj2;
	bool salir;
	int  turnos;
	
protected:
public:
	Juego();
	Juego(std::string nivelTxt);
	~Juego();

	// GETTERS
	bool Get_Salir() const;

	// MÈTODOS
	void Actualizar();
	void Crear_Objetos();
	void Game_Over();
	bool Jugar();
	void Mover_NPC();
	void Mover_Personaje();
	void Muerto();

	void Presentacion();
	void Puntuacion();
	
	// TEMPORAL
	void dibujarMapa();
	void verDatosObjetos();
	
};

#endif



