#ifndef MAQUINA_ESTADOS_JUEGO_H
#define MAQUINA_ESTADOS_JUEGO_H

#include<vector>
#include"EstadoJuego.h"

class Juego;

class Maquina_Estados_Juego
{
private:
	std::vector<EstadoJuego*> estadosJuego_;
protected:
public:
	void Actualizar();
	void Cambiar_Estado(EstadoJuego*);
	void Eliminar_Estado(EstadoJuego*);
	void Incluir_Estado(EstadoJuego*);
	
};

#endif

