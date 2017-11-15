#ifndef AUXILIAR_H
#define AUXILIAR_H

/* Esta clase sirve para dibujar el mapa y los objetos.
   Si incluyo una referencia a 'Mapa' en la clase 'Objeto'
   se producen dependencias cruzadas y se generan multitud 
   de fallos. */
#include <list>
#include "Casilla.h"
#include "Constantes.h"
#include "Objeto.h"
#include "rlutil.h"

class Auxiliar {
private:
protected:
public:
	std::list<Objeto*> lista_objetos_auxiliar;
	Casilla* mapa_auxiliar;
	
	Auxiliar();
	~Auxiliar();
	
	// MÉTODOS
	void Dibujar_Mapa();
};

#endif

