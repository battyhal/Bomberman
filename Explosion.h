#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Estado.h"

class Bomba;

class Explosion : public Estado<Bomba>
{
private:
	Explosion(){}
	Explosion(const Explosion &arg){}
	~Explosion(){}
protected:
public:
	// Singleton
	static Explosion* Get_Instancia();
	
	virtual void Entra(Bomba*);
	virtual void Realiza(Bomba*);
	virtual void Sale(Bomba*);
	virtual bool Transmite_Mensaje(Bomba*, const Mensaje&) { return false; };
};

#endif

