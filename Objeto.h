#ifndef OBJETO_H
#define OBJETO_H

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <random>
#include <string>

class Objeto {
private:
protected:
	int  ataque;
	int  defensa;
	int  energia;
	std::string nombre;
	char tag;
	int  vidas;
	int  x;
	int  y;
public:
	Objeto();
	Objeto(int _ataque, int _defensa, int _energia, std::string _nombre,
		   char _tag, int _vidas, int _x, int _y);
	virtual ~Objeto();
	
	// Getters
	int  Get_Ataque();
	int  Get_Defensa();
	int  Get_Energia();
	std::string Get_Nombre();
	char Get_Tag();
	int  Get_Vidas();
	int  Get_X();
	int  Get_Y();
	
	// Setters
	void Set_Ataque(int i);
	void Set_Defensa(int i);
	void Set_Energia(int i);
	void Set_Tag(char c);
	void Set_Vidas(int i);
	void Set_X(int i);
	void Set_Y(int i);
	
	// MÉTODOS
	virtual int  Cuenta_Atras();
	void Mover(int i, int _x, int _y);
	void Perseguir(int _x, int _y);
};

#endif

