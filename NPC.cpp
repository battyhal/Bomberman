#include "NPC.h"

NPC::NPC() : Objeto(){}

NPC::NPC(int _ataque, int _defensa, int _energia, std::string _nombre, char _tag, 
		 int _vidas, int _x, int _y, int _puntos, std::string _equipo)
	    : Objeto(_ataque, _defensa, _energia, _nombre, _tag, _vidas, _x, _y)
{
	equipo.push_back(_equipo);
}

NPC::~NPC() {}

