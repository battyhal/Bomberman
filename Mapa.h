#ifndef MAPA_H
#define MAPA_H

#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <math.h>
#include <utility>
#include <vector>
#include "Constantes.h"
#include "Nodo.h"
#include "rlutil.h"

// Singleton que va a comprobar colisiones
class Mapa {
private:
	Mapa();
	Mapa(std::string nivelTxt);
	Mapa& operator=(const Mapa&);
	Nodo** matriz;  
	int nodosVisitados = 0;
	std::vector<std::pair<int, int>> portales;
	std::list<Nodo*> rutaMapa; 
	std::vector<Nodo*> vecinos;
	std::vector<Nodo> visitadas;
protected:
public:
	static Mapa* Instancia();
	~Mapa();

	// GETTERS
	int Get_Nodos_Visitadas();
	int Get_Ancho_Mapa();
	int Get_Alto_Mapa();
	Nodo*& Get_Nodo(int, int);
	char Get_Contenido_Nodo(int, int);
	float Get_Local();
	Nodo** Get_Matriz();
	int Get_Portales(int, char);
	std::list<Nodo*> Get_Ruta_Mapa();
	void Get_Vecinos(int, int);
	
	// SETTERS
	void Set_Nodo(char, bool, bool, int, int);
	void Set_Contenido_Nodo(char, int, int);
	
	// MÉTODOS
	void A_Star(int, int, int, int);
	int* Adyacentes(int, int, int, int);
	bool Buscar_Atajo(int, int, int, int);
	void Reset_Visitadas();
	void Usar_Portal(int, int);
	
};

#endif

