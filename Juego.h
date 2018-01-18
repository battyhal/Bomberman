#ifndef JUEGO_H
#define JUEGO_H

#include <cassert>
#include <fstream>
#include <list>
#include "Auxiliar.h"
#include "Bomba.h"
#include "EstadoJuego.h"
#include "Mapa.h"
#include "Maquina_Estados_Juego.h"
#include "NPC.h"
#include "Objeto.h"
#include "Personaje.h"
#include "rlutil.h"

class EstadoJuego;
//  ======================================================================================
/// La clase juego se convierte en singleton para implementar sistema de menús
//  ======================================================================================
class Juego {
private:
	Bomba* bomba_;
	Personaje* Bomberman_;
	EstadoJuego* estadoActual_;
	Mapa* mapa_;
	Maquina_Estados_Juego* maquinaEstados_;
	std::list<Objeto*> objetos_;
	bool salir_;
	int  turnos_;
	
	Juego();
	Juego(std::string nivelTxt);
	Juego& operator=(const Juego& otro);
protected:
public:
	~Juego();

	// GETTERS
	static Juego* Get_Instancia();
	Maquina_Estados_Juego* Get_Maquina_Estados();
	bool Get_Salir() const;
	std::list<Objeto*> Get_Objetos() const;
	
	// SETTERS

	// MÉTODOS
	void Actualiza();
	void Actualiza_Estado();
	void Cambia_Estado(EstadoJuego*);
	void Elimina_Estado(EstadoJuego*);
	void Incluye_Estado(EstadoJuego*);
	void Crea_Objetos();
	void Fondo_Bomberman();
	void Game_Over();
	void Jugar();
	void Mueve_NPC();
	void Mueve_Personaje();
	void Muerto();

	void Puntuacion();
		
};

typedef Juego ElJuego;

#endif



