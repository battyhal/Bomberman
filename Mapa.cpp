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

