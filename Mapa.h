#ifndef MAPA_H
#define MAPA_H

#include <fstream>
#include <iostream>
#include <list>
#include "Constantes.h"
#include "Objeto.h"
#include "rlutil.h"

class Mapa {

private:
	const char esquinaInfDcha = 188;
	const char esquinaInfIzda = 200;
	const char esquinaSupDcha = 187;
	const char esquinaSupIzda = 201;
	const char lateral = 186;
	const char suelo = 205;
	const char Cemento = 'X';
	const char Adobe   = 177;
	
	//  Como un array 2D se almacena en la memoria del ordenador como un array 1D 
	//  se puede declarar igualmente de la forma " char matriz[alto * ancho] "
	//  y se sigue la fórmula " y * ANCHO + x " para llegar a la casilla x, y 	 
	char  matrizFija[ALTO * ANCHO];
	
	// La matriz dinámica se usará para cargar mapas de archivo de texto de los que 
	// no sabemos las dimensiones 
	int  altoMatrizDinamica;
	int  anchoMatrizDinamica;
	char *matrizDinamica;  
protected:

public:
	Mapa();
	Mapa(std::string nivelTxt);
	~Mapa();

	// GETTERS
	int  Get_Ancho_Mapa();
	int  Get_Alto_Mapa();
	char Get_Contenido_Casilla(int x, int y);
	// SETTERS
	void Set_Casilla(int x, int y, char c);
	// MÉTODOS
	void Dibujar_Jugador_Muerto();
	void Dibujar_Mapa(std::list<Objeto*>& o);
	void Dibujar_Marco();
};

#endif

