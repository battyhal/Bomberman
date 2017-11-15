#ifndef CASILLA_H
#define CASILLA_H

#include <list>

class Casilla {
private:
	char contenido;
	bool obstaculo;
	std::list<Casilla> ruta;
	Casilla* siguiente;
	bool visitada;
	int x;
	int y;
	
protected:
public:
	Casilla();
	Casilla(char _con, bool _obs, bool _vis, int _x, int _y);
	~Casilla();
	
	// GETTERS
	char Get_Contenido();
	bool Get_Obstaculo();
	bool Get_Visitada();
	int  Get_X();
	int  Get_Y();
	
	// SETTERS
	void Set_Contenido(char c);
	void Set_Obstaculo(bool b);
	void Set_Visitada(bool b);
	void Set_X(int i);
	void Set_Y(int i);
	
	// MÉTODOS
	void Incluir_Casilla(Casilla c);
	
	
};

#endif

