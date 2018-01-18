#ifndef ATACAR_H
#define ATACAR_H

#include"Estado.h"

class NPC;

class Atacar : public Estado<NPC>
{
private:
	Atacar(){};
	// El constructor de copia y el operador asignación(=) son privados
	Atacar(const Atacar&);
	Atacar& operator=(const Atacar&);
	~Atacar(){}
public:
	// Singleton
	static Atacar* Instancia();
	
	virtual void Entra(NPC*);
	virtual void Realiza(NPC*);
	virtual void Sale(NPC*);
	virtual bool Transmite_Mensaje(NPC*, const Mensaje&) { return false; }
};

#endif

