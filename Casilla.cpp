#include "Casilla.h"

Casilla::Casilla() :contenido(' '), obstaculo(0), siguiente(nullptr), visitada(0), x(0), y(0) {}

Casilla::Casilla(char _con, bool _obs, bool _vis, int _x, int _y):
contenido(_con), obstaculo(_obs), siguiente(nullptr), visitada(_vis), x(_x), y(_y) {}

Casilla::~Casilla() {}

// ---------------------------------------------------------------
// GETTERS
// ---------------------------------------------------------------
char Casilla::Get_Contenido(){ return contenido; }
bool Casilla::Get_Obstaculo(){ return obstaculo; }
bool Casilla::Get_Visitada() { return visitada; }
int  Casilla::Get_X()        { return x; }
int  Casilla::Get_Y()        { return y; }
// ---------------------------------------------------------------
// SETTERS
// ---------------------------------------------------------------
void Casilla::Set_Contenido(char c) { contenido = c; }
void Casilla::Set_Visitada(bool b)  { visitada = b; }
void Casilla::Set_X(int i)          { x = i; }
void Casilla::Set_Y(int i)			{ y = i; }
// ---------------------------------------------------------------
// MÉTODOS
// ---------------------------------------------------------------
void Casilla::Incluir_Casilla(Casilla c)
{
	ruta.push_back(c);
}
