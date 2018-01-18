#ifndef PATRULLAR_H
#define PATRULLAR_H

#include"Estado.h"

class NPC;

class Patrullar : public Estado<NPC>
{
private:
	Patrullar(){}
	// El constructor de copia y el operador asignación(=) son privados
	Patrullar(const Patrullar& otro);
	Patrullar& operator=(const Patrullar& otro);
	~Patrullar(){}
public:
	// Singleton
	static Patrullar* Instancia();
	
	virtual void Entra(NPC*);
	virtual void Realiza(NPC*);
	virtual void Sale(NPC*);
	virtual bool Transmite_Mensaje(NPC*, const Mensaje&) { return false; };
};

#endif

