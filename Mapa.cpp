#include "Mapa.h"

Mapa::Mapa()
{
	//  Como un array 2D se almacena en la memoria del ordenador como un array 1D 
	//  se puede declarar igualmente de la forma " char matriz[alto * ancho] "
	//  y se sigue la fórmula " y * ANCHO + x " para llegar a la casilla x, y 	  
	for(int j = 0; j < ANCHO; j++)
	{
		for(int k = 0; k < ALTO; k++)
		{
			/*if(j % 2 != 0 && k % 2 != 0)
				matrizFija[k * ANCHO + j] = Adobe;*/
			if(j % 3 != 0 && k % 3 != 0)
				matrizFija[k * ANCHO + j] = Adobe;
			else matrizFija[k * ANCHO + j] = ' ';
		}
	}
	// Se iguala a NULL porque no se va a utilizar
	altoMatrizDinamica  = 0;
	anchoMatrizDinamica = 0;
	matrizDinamica = NULL;
}

Mapa::Mapa(std::string archivoTxt)
{
	// Se inicializa a ' ' porque no se va a utilizar 
	for(int j = 0; j < ANCHO; j++)
	{
		for(int k = 0; k < ALTO; k++)
		{
			matrizFija[k * ANCHO + j] = ' ';
		}
	}
	// Se crea el flujo de apertura de archivo
	std::ifstream archivo;
	archivo.open(archivoTxt);
	// Si falla se devuelve un error
	if(archivo.fail())
	{
		perror(archivoTxt.c_str());
		system("pause");
		exit(1);
	}
	// Se crean dos cadenas que almacenarán los
	// datos del archivo de texto línea por línea
	std::string cadena;
	std::string cadena2;
	altoMatrizDinamica = 0;
	anchoMatrizDinamica = 0;
	while(getline(archivo, cadena))
	{
		// Para saber la anchura de la cadena 
		if(cadena.length() + 1 > anchoMatrizDinamica)
			anchoMatrizDinamica = cadena.length() + 1;
		// Para incluir el salto de linea al final de cada cadena
		cadena2 += '\n';
		// Cadena2 va almacenando todas las lineas separadas por un '\n'
		cadena2 += cadena;
		// Para saber la altura del archivo se va incrementando 1 
		altoMatrizDinamica++;
	}
	// La longitud debe ser igual a la de cadena2 + 1 caracter para almacenar el último '\n'
	int longitud = cadena2.length() + 1;
	matrizDinamica = new char[longitud];
	// strncpy se usa para copiar el contenido de cadena2 en matrizDinamica
	strncpy(matrizDinamica, cadena2.c_str(), longitud);
}

Mapa::~Mapa(){ delete[] matrizDinamica; }

// ---------------------------------------------------------------
// GETTERS
// ---------------------------------------------------------------
int Mapa::Get_Ancho_Mapa()
{ 
	if(matrizDinamica == NULL)
		return ANCHO; 
	else return anchoMatrizDinamica; 
}
int Mapa::Get_Alto_Mapa()
{ 
	if(matrizDinamica == NULL)
		return ALTO; 
	else return altoMatrizDinamica; 
}
char Mapa::Get_Contenido_Casilla(int x, int y) 
{ 
	if(matrizDinamica == NULL)
		return matrizFija[y * ANCHO + x]; 
	else return matrizDinamica[y * anchoMatrizDinamica + x];
}

// ---------------------------------------------------------------
// SETTERS
// ---------------------------------------------------------------
void Mapa::Set_Casilla(int x, int y, char c)
{
	if(matrizDinamica == NULL)
		matrizFija[y * ANCHO + x] = c;
	else matrizDinamica[y * anchoMatrizDinamica + x] = c;
}

// ---------------------------------------------------------------
// MÉTODOS
// ---------------------------------------------------------------
void Mapa::Dibujar_Jugador_Muerto()
{
	char muerto[9][47] = {
		"                                              ",
			" *     *  *   *  ******  *****  *******  *****",
			" * * * *  *   *  *       *   *     *     *   *",
			" *  *  *  *   *  *       *   *     *     *   *",
			" *     *  *   *  ***     * **      *     *   *",
			" *     *  *   *  *       *  *      *     *   *",
			" *     *   ***   ******  *   *     *     *****",
			"                                              ",
	};
	for(int j = 0; j < 9; j++)
	{
		for(int k = 0; k < 47; k++)
		{
			std::cout << muerto[j][k];
		}
		std::cout << "\n";
	}
}

void Mapa::Dibujar_Mapa(std::list<Objeto*>& o)
{
	if(matrizDinamica == NULL)
	{
		// Dibujar contenido matriz fija
		gotoxy(20, 3);
		for(int j = 0; j < ALTO; j++)
		{
			for(int k = 0; k < ANCHO; k++)
			{
				bool dibujado = false;
				for(std::list<Objeto*>::iterator it = o.begin(); !dibujado && it != o.end(); it++)
				{
					if((*it)->Get_X() == k && (*it)->Get_Y() == j)
					{
						// Si Bomberman está muerto 
						if((*it)->Get_Nombre() == "Bomberman")
						{
							if((*it)->Get_Vidas() == 0)
								Dibujar_Jugador_Muerto();
						}
						// Si hay una bomba dibuja siempre la bomba 
						if((*it)->Get_Nombre() == "Bomba")
							std::cout << '@';
						else std::cout << (*it)->Get_Tag();
						dibujado = true;
					}
				}
				if(!dibujado)
				{
					std::cout << matrizFija[j * ANCHO + k];										
				}
			}
			gotoxy(20, j + 4);
		}			
	}
	else 
	{
		// Dibujar contenido matriz dinámica
		gotoxy(20, 3);
		for(int j = 0; j < altoMatrizDinamica; j++)
		{
			for(int k = 0; k < anchoMatrizDinamica; k++)
			{
				bool dibujado = false;
				for(std::list<Objeto*>::iterator it = o.begin(); !dibujado && it != o.end(); it++)
				{
					if((*it)->Get_X() == k && (*it)->Get_Y() == j)
					{
						// Si Bomberman está muerto 
						if((*it)->Get_Nombre() == "Bomberman")
						{
							if((*it)->Get_Vidas() == 0)
								Dibujar_Jugador_Muerto();
						}
						// Si hay una bomba dibuja siempre la bomba 
						if((*it)->Get_Nombre() == "Bomba")
							std::cout << '@';
						else std::cout << (*it)->Get_Tag();
						dibujado = true;
					}
				}
				if(!dibujado)
				{
					std::cout << matrizDinamica[j * anchoMatrizDinamica + k];										
				}
			}
			//gotoxy(20, j + 4);
		}
	}	
}

void Mapa::Dibujar_Marco()
{
	// Dibujar marco
	gotoxy(4, 2);
	for(int l = 0; l <= ALTO; l++)
	{
		for(int m = 0; m <= ANCHO + 20; m++)
		{
			if(l == 0 || l == ALTO || m == 0 || m == ANCHO + 20)
				std::cout << '*';
			else std::cout << ' ';
		}
		gotoxy(4, l + 5);
	}
}


////******* FUNCIONES PARA CARGAR DATOS DE UN FICHERO DE TEXTO **********////
/*std::vector<std::string> levelData;
void loadData(std::string fileName)
{
	std::ifstream file;
	file.open(fileName);
	if(file.fail())
	{
		perror(fileName.c_str());
		system("pause");
		exit(1);
	}
	
	std::string line;
	while(getline(file, line))
	{
		levelData.push_back(line);
	}
	
	file.close();
}*/
////******* FUNCIONES PARA CARGAR DATOS DE UN FICHERO DE TEXTO **********////
void showData(std::vector<std::string>& s)
{
	for(std::vector<std::string>::iterator it = s.begin(); it != s.end(); it++)
	{
		std::cout << (*it);
		std::cout << "\n";
	}
}

/*

0  1  2  3  4
0 [ ][ ][ ][ ][ ]
1 [ ][ ][ ][ ][ ]
2 [ ][P][ ][ ][ ]
3 [ ][ ][ ][ ][ ]
4 [ ][ ][ ][E][ ]

P: Y2,X1
E: Y4,X3

E.Y > P.Y <--- Está hacia arriba el jugador
E.X > P.X <--- Está hacia la izquierda
O subimos o nos movemos a la izquierda [Aleatorio : tiras aleatorio 0-100 y si sale 0-50 uno 51-100 otro]
E.X < P.X <--- Está hacia la derecha
O subimos o nos movemos a la derecha [Aleatorio : tiras aleatorio 0-100 y si sale 0-50 uno 51-100 otro]
E.X == P.X <--- Está en la misma columna
Subimos
E.Y < P.Y <--- Está hacia abajo
E.X > P.X <--- Está hacia la izquierda
O bajamos o vamos a la izquierda [Aleatorio : tiras aleatorio 0-100 y si sale 0-50 uno 51-100 otro]
E.X < P.X <--- Está hacia la derecha
O bajamos o vamos a la derecha [Aleatorio : tiras aleatorio 0-100 y si sale 0-50 uno 51-100 otro]
E.X == P.X <--- Está en la misma columna
Bajamos
E.Y == P.Y <--- Está en la misma fila
E.X > P.X <--- Está hacia la izquierda
Nos vamos a la izquierda
E.X < P.X <--- Está hacia la derecha
Nos vamos a la derecha
E.X == P.X <--- Está en la misma columna
Estamos encima




/
-    	    /
/
X
/
/
/             +



0  1  2  3  4  5  6  7  8  9
0 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
1 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
2 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
3 [ ][ ][ ][ ][ ][T][ ][ ][ ][ ]
4 [ ][ ][ ][ ][T][T][ ][ ][P][P]
5 [ ][ ][ ][T][T][T][ ][ ][P][P]
6 [ ][ ][ ][T][T][T][T][ ][P][P]
7 [T][T][T][T][T][T][T][T][T][T]
8 [T][T][T][T][T][T][T][T][T][T]
9 [T][T][T][T][T][T][T][T][T][T]

[A][A][A]
[A][P][A]
[T][T][T]
A A A A A
\|/ \|/
A -P- A - T
/|\ /|\
T T T T T


[A][A][A][A][A][A][A][A][A][A][A]
[A][A][A][A][A][A][A][A][A][A][A]
[T][T][T][P][T][T][T][W][W][W][W]
[T][T][T][T][T][T][T][T][W][W][W]
[T][T][T][T][T][T][T][T][T][W][W]
[T][T][T][T][T][T][T][T][T][T][T]



0  1  2  3  4  5  6  7  8  9
0 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
1 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
2 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
3 [T][W][W][W][W][W][W][W][W][W]
4 [T][T][W][W][W][W][W][W][W][W]
5 [T][T][T][W][W][W][W][W][W][W]
6 [T][T][T][T][W][W][W][W][W][W]
7 [T][T][T][T][T][T][T][W][W][W]
8 [T][T][T][T][T][T][T][T][W][W]
9 [T][T][T][T][T][T][T][T][T][W]

* * *
* P *
* * *



ListaCoordenadas => Aprox 100 coordenadas que representan una coordenada de zona y una de casilla cada una
ListaEntidades => 1.000.000 Entidades (NPC, Jugadores, Árboles, etc)
ListaRepresentable => Aquí se generan una lista de entre X e Y elementos




*/
