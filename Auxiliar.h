#ifndef AUXILIAR_H
#define AUXILIAR_H

/* Esta clase es para dibujar el mapa y los objetos. Si incluyo una referencia a 'Mapa'
  en la clase 'Objeto' hay dependencias cruzadas y se generan multitud de fallos. */
#include <list>
#include "Constantes.h"
#include "Nodo.h"
#include "Objeto.h"
#include "rlutil.h"

class Auxiliar
{
private:
protected:
public:
	std::list<Objeto*> listaObjetosAuxiliar_;
	Nodo** mapaAuxiliar_;
	
	Auxiliar();
	Auxiliar(std::list<Objeto*>&, Mapa&);
	~Auxiliar();
	
	// =======================================================================
	// MÉTODOS
	// =======================================================================
	void Dibujar_Mapa();
};

#endif

