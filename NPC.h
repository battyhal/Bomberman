#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <vector>
#include "Objeto.h"

class NPC : public Objeto {
private:
	std::vector<std::string> equipo;

protected:
public:
	NPC();
	NPC(int _ataque, int _defensa, int _energia, std::string _nombre, char _tag, 
		int _vidas, int _x, int _y, int _puntos, std::string _equipo);
	~NPC();
};

#endif

