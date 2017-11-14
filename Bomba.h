#ifndef BOMBA_H
#define BOMBA_H

#include "Objeto.h"

class Bomba : public Objeto {
private:
	int radio_Accion;
	int tiempo_vida;
protected:
public:
	Bomba(int _ataque, int _defensa, int _energia, std::string _nombre,
		  char _tag, int _vidas, int _x, int _y, int _radio, int _tiempo);
	Bomba(const Bomba &arg);
	~Bomba();
	
	// GETTERS
	
	
	// MÉTODOS
	int Cuenta_Atras();
};

#endif

