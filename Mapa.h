#ifndef MAPA_H
#define MAPA_H

#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include "Casilla.h"
#include "Constantes.h"
#include "rlutil.h"

class Mapa {
friend class Auxiliar;
private:
	// Como un array 2D se almacena en la memoria del ordenador como un array 1D 
	// se puede declarar igualmente de la forma " char matriz[alto * ancho] "
	// y se sigue la fórmula " x * ANCHO + y " para llegar a la casilla x, y 	 
	Casilla matrizFija[ALTO * ANCHO];
	
	// La matriz dinámica se usará para cargar mapas de archivo de texto de los que 
	// no sabemos las dimensiones 
	int  altoMatrizDinamica;
	unsigned int anchoMatrizDinamica;
	Casilla *matrizDinamica;  
	
	std::vector<Casilla> ruta; 
	std::vector<Casilla> visitadas;
protected:

public:
	Mapa();
	Mapa(std::string nivelTxt);
	Mapa& operator=(const Mapa& otro);
	~Mapa();

	// GETTERS
	int  Get_Ancho_Mapa();
	int  Get_Alto_Mapa();
	char Get_Contenido_Casilla(int x, int y);
	Casilla* Get_Matriz_Fija();
	
	// SETTERS
	void Set_Casilla(int x, int y, char c);
	
	// MÉTODOS
	int  Backtracking(Casilla& origen, Casilla& destino);
	Casilla Buscar_Adyacentes(Casilla& origen, Casilla& destino);
	void Dibujar_Jugador_Muerto();
	void Dibujar_Marco();
	
};

#endif

