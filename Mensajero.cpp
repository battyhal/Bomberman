#include "Mensajero.h"

Mensajero::Mensajero():mensaje_(nullptr) {}
Mensajero::~Mensajero() { delete mensaje_; }

// ======================================================================================
// M�TODOS
// ======================================================================================
void Mensajero::Entregar_Mensaje(int em, long hor, void* inf, int re)
{
	mensaje_= new Mensaje(em, hor, inf, re);
	colaMensajes_.insert(mensaje_);
}

// ==========================================================================
// GETTERS
// ==========================================================================

// ==========================================================================
// SETTERS
// ==========================================================================

// ==========================================================================
// M�TODOS
// ==========================================================================