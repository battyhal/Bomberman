#ifndef Nodo_H
#define Nodo_H

#include <iostream>
#include <vector>

class Nodo {
friend class Mapa;
private:
	Nodo* abajo_;
	Nodo* arriba_;
	Nodo* derecha_;
	Nodo* izquierda_;
	Nodo* padre_;
	Nodo* portal_;
	char contenido_;
	float distanciaGlobal_;
	float distanciaLocal_;
	bool obstaculo_;
	std::vector<Nodo*>vecinos_;
	bool visitado_;
	int x_;
	int y_;	
protected:
public:
	Nodo();
	Nodo(char c, bool o, bool v, int x, int y);
	Nodo& operator=(const Nodo& otro);
	~Nodo();
	
	// GETTERS
	Nodo* Get_Abajo();
	Nodo* Get_Arriba();
	Nodo* Get_Derecha();
	Nodo* Get_Izquierda();
	Nodo* Get_Padre();
	Nodo* Get_Portal();
	char  Get_Contenido();
	float Get_Global();
	float Get_Local();
	bool  Get_Obstaculo();
	std::vector<Nodo*> Get_Vecinos();
	bool  Get_Visitado();
	int   Get_X();
	int   Get_Y();
	
	// SETTERS
	void Set_Abajo(Nodo*);
	void Set_Arriba(Nodo*);
	void Set_Derecha(Nodo*);
	void Set_Izquierda(Nodo*);
	void Set_Padre(Nodo*);
	void Set_Portal(Nodo*);
	void Set_Contenido(char c);
	void Set_Distancia_Global(float f);
	void Set_Distancia_Local(float f);
	void Set_Obstaculo(bool b);
	void Set_Visitado(bool b);
	void Set_X(int i);
	void Set_Y(int i);
	
	// MÉTODOS
	void Incluir_Vecino(Nodo* n);
	void Ver_Todo();
	
	
};

#endif

