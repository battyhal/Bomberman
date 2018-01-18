#include "Mapa.h"

Mapa::Mapa():matriz(new Nodo*[ALTO * ANCHO]), rutaMapa(0), visitadas(0)
{
	// Iniciar todos los valores de matriz a 0
	std::memset(matriz, 0, ALTO * ANCHO * sizeof(int));
	
	// Crear todos los Nodos vacios
	for(int j = 0; j < ANCHO; j++)
	{
		for(int k = 0; k < ALTO; k++)
		{
			Set_Nodo(' ', false, false, j, k);
		}
	}
	
	// Obstáculos
	for (int i = 0; i < ANCHO; i++)
	{
		for(int j = 0; j < ALTO; j++)
		{
			if(i % 2 == 0 && j % 2 == 0)
			{			
				matriz[j * ANCHO  + i]->Set_Contenido(Adobe);
				matriz[j * ANCHO  + i]->Set_Obstaculo(true);
			}
		}
	}
	
	// Nodos Teletransporte 
	Nodo*& portal1 = Get_Nodo(3, 5);
	Nodo*& portal2 = Get_Nodo(10, 13);
	portal1->Set_Portal(portal2);
	portal2->Set_Portal(portal1);
	portal1->Set_Contenido('X');
	portal2->Set_Contenido('X');
	portal1->Set_Distancia_Local(0.0);
	portal2->Set_Distancia_Local(0.0);
	portales.push_back(std::make_pair(portal1->Get_X(), portal1->Get_Y()));
	portales.push_back(std::make_pair(portal2->Get_X(), portal2->Get_Y()));
	
	// Marco
	for (int i = 0; i < ANCHO; i++)
	{
		for(int j = 0; j < ALTO; j++)
		{
			if(i == 0 || i == ANCHO - 1 || j == 0 || j == ALTO - 1)
			{
				matriz[j * ANCHO + i]->Set_Contenido(Adobe);
				matriz[j * ANCHO + i]->Set_Obstaculo(true);
			}
		}
	}
}

Mapa::Mapa(std::string archivoTxt)
{
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
	int largoCadena = 0;
	int longitudMaxima = 0;
	while(getline(archivo, cadena))
	{
		// Para saber la anchura de la cadena
		largoCadena = cadena.length() + 1;
		if(largoCadena > longitudMaxima)
			longitudMaxima = largoCadena;
		// Para incluir el salto de linea al final de cada cadena
		cadena2 += '\n';
		// Cadena2 va almacenando todas las lineas separadas por un '\n'
		cadena2 += cadena;
		// Para saber la altura del archivo se va incrementando 1
	}
	// La longitud debe ser igual a la de cadena2 + 1 caracter para almacenar el último '\n'
	longitudMaxima = cadena2.length() + 1;
	matriz = new Nodo*[longitudMaxima];
	// strncpy se usa para copiar el contenido de cadena2 en matrizDinamica
	//(matrizDinamica, cadena2.c_str(), longitud);
}

Mapa& Mapa::operator=(const Mapa& otro)
{
	if(this != &otro)
	{
		for(int j = 0; j < ANCHO; j++)
		{
			for(int k = 0; k < ALTO; k++)
			{
				matriz[k * ANCHO + j] = otro.matriz[k * ANCHO + j];
			}
		}
		rutaMapa = otro.rutaMapa;
		visitadas = otro.visitadas;
	}
	return *this;
}

Mapa::~Mapa()
{
	for(int j = 0; j < ANCHO; j++)
	{
		for(int k = 0; k < ALTO; k++)
		{
			delete Get_Nodo(j, k);
		}
	}
	delete[] matriz;
}
Mapa* Mapa::Instancia()
{
	static Mapa instancia;
	return &instancia;
}
// ---------------------------------------------------------------
// GETTERS
// ---------------------------------------------------------------
int  Mapa::Get_Nodos_Visitadas(){ return nodosVisitados; };
int  Mapa::Get_Ancho_Mapa(){ return ANCHO; }
int  Mapa::Get_Alto_Mapa() { return ALTO;  }

Nodo*& Mapa::Get_Nodo(int x, int y){ return matriz[y * ANCHO + x]; }

char Mapa::Get_Contenido_Nodo(int x, int y)
{
	Nodo*& aux = Get_Nodo(x, y);
	return aux->Get_Contenido();
}

float Mapa::Get_Local()
{
	for (int i = 0; i < ANCHO; i++)
	{
		for(int j= 0; j < ALTO; j++)
		{
			if(Get_Nodo(i, j)->Get_Local() == 0)
				std::cout << " Nodo Local(" << i << ", " << j << ") = 0\n";
		}
	}
	return 1;
}

Nodo** Mapa::Get_Matriz()
{ 
	Nodo** otraMatriz = new Nodo*[ALTO * ANCHO];
	for (int i = 0; i < ANCHO; i++)
	{
		for(int j= 0; j < ALTO; j++)
		{
			otraMatriz[j * ANCHO + i] = matriz[j * ANCHO + i];
		}
	}
	return otraMatriz; 
}

int Mapa::Get_Portales(int orden, char xy)
{
	if(xy == 'x')
		return portales.at(orden).first;
	else if(xy == 'y')
		return portales.at(orden).second;
}

std::list<Nodo*> Mapa::Get_Ruta_Mapa(){ return rutaMapa; }

void Mapa::Get_Vecinos(int x, int y)
{
	std::ofstream salida("prueba.txt");
	
	Nodo*& aux = Get_Nodo(x, y);
	if(aux)
	{
		std::vector<Nodo*> n = aux->Get_Vecinos();
		salida << "\n N.size = " << n.size() << "\n";
		if(n.size() > 0)
		{
			salida << "\n Vecinos de Nodo(" << x <<", " << y << ") = " << n.size();
			int contador = 0;
			for(auto it : aux->vecinos_)
			{
				salida << "\n Vecino[" << contador << "](x, y) = " << it->Get_X()
				<< ", " << it->Get_Y();
				salida << "\n";
				contador++;
			}
		}
		else salida << " Vector Vecinos de " << x << y << " vacio\n";
	}
	salida.close();
}
// ---------------------------------------------------------------
// SETTERS
// ---------------------------------------------------------------
void Mapa::Set_Nodo(char con, bool obs, bool vis, int x, int y)
{
	Nodo*& aux = Get_Nodo(x, y);
	if(aux == nullptr)
	{
		aux = new Nodo(con, obs, vis, x, y);

		if(y < ALTO - 1) // ABAJO
		{
			Nodo*& vecino = Get_Nodo(x, y + 1);
			aux->Set_Abajo(vecino);
			aux->Incluir_Vecino(new Nodo(con, obs, vis, x, y + 1));
			if(vecino)
				vecino->Set_Arriba(aux);
		}
		if(y > 0) // ARRIBA
		{
			Nodo*& vecino = Get_Nodo(x, y - 1);
			aux->Set_Arriba(vecino);
			aux->Incluir_Vecino(new Nodo(con, obs, vis, x, y - 1));
			if(vecino)
				vecino->Set_Abajo(aux);
		}
		if(x < ANCHO - 1) // DERECHA
		{
			Nodo*& vecino = Get_Nodo(x + 1, y);
			aux->Set_Derecha(vecino);
			aux->Incluir_Vecino(new Nodo(con, obs, vis, x + 1, y));
			if(vecino)
				vecino->Set_Izquierda(aux);
		}
		if(x > 0) // IZQUIERDA
		{
			Nodo*& vecino = Get_Nodo(x - 1, y);
			aux->Set_Izquierda(vecino);
			aux->Incluir_Vecino(new Nodo(con, obs, vis, x - 1, y));
			if(vecino)
				vecino->Set_Derecha(aux);
		}
	}
	else
	{
		aux->Set_Contenido(con);
		aux->Set_Obstaculo(obs);
		aux->Set_Visitado(vis);
	}
}

void Mapa::Set_Contenido_Nodo(char c, int x, int y)
{ matriz[y * ANCHO + x]->Set_Contenido(c); }

// ---------------------------------------------------------------
// MÉTODOS
// ---------------------------------------------------------------
void Mapa::A_Star(int npcX, int npcY, int persX, int persY)    
{
	// LAMBDAS
	auto distancia = [](Nodo* a, Nodo* b) 
	{
		return sqrtf((a->Get_X() - b->Get_X())*(a->Get_X() - b->Get_X()) +
				    (a->Get_Y() - b->Get_Y())*(a->Get_Y() - b->Get_Y()));
	};
	
	auto heuristica = [distancia](Nodo* a, Nodo* b)
	{
		return distancia(a, b);
	};
	
	Nodo* matrizAux = new Nodo[ANCHO * ALTO];
	// Inicializar Nodos
	Nodo vacio(' ', false, false, 0, 0);
	for(int i = 0; i < ANCHO; i++)
	{
		for(int j = 0; j < ALTO; j++)
		{
			matrizAux[j * ANCHO + i] = vacio;
			matrizAux[j * ANCHO + i].Set_X(i);
			matrizAux[j * ANCHO + i].Set_Y(j);
		}
	}
	
	// Poner obstáculos
	for (int i = 0; i < ANCHO; i++)
	{
		for(int j = 0; j < ALTO; j++)
		{
			if(i % 2 == 0 && j % 2 == 0)
			{			
				matrizAux[j * ANCHO + i].Set_Contenido(Adobe);
				matrizAux[j * ANCHO + i].Set_Obstaculo(true);
			}
		}
	}
	
	// Teletransporte
	/*Nodo* auxFinal = &matrizAux[persY * ANCHO + persX];
	Nodo* portal1 = &matrizAux[5 * ANCHO + 3];
	Nodo* portal2 = &matrizAux[13 * ANCHO + 10];
	portal1->Set_Distancia_Local(-0.1);
	portal1->Set_Distancia_Global(heuristica(portal1, auxFinal));
	portal2->Set_Portal(portal1);
	portal2->Set_Distancia_Local(-0.1);
	portal2->Set_Distancia_Global(heuristica(portal2, auxFinal));
	portal1->Set_Portal(portal2);*/
	
	// Almacenar conexiones en vecinos
	for(int x = 0; x < ANCHO; x++)
	{	for(int y = 0; y < ALTO; y++)
		{
			if(y < ALTO - 1) // ABAJO
			{
				matrizAux[y * ANCHO + x].Incluir_Vecino(&matrizAux[(y + 1)
														* ANCHO + x]);
			}
			if(y > 0) // ARRIBA
			{
				matrizAux[y * ANCHO + x].Incluir_Vecino(&matrizAux[(y - 1)
														* ANCHO + x]);
			}
			if(x < ANCHO - 1) // DERECHA
			{
				matrizAux[y * ANCHO + x].Incluir_Vecino(&matrizAux[y *
					                                    ANCHO + (x + 1)]);
			}
			if(x > 0) // IZQUIERDA
			{
				matrizAux[y * ANCHO + x].Incluir_Vecino(&matrizAux[y *
					                                    ANCHO + (x - 1)]);
			}
		}
	}
	
	// Inicializar inicio y fin para que correspondan a npc y personaje
	Nodo* nodoInicial = &matrizAux[npcY * ANCHO + npcX];
	Nodo* nodoFinal = &matrizAux[persY * ANCHO + persX];
	nodoInicial->Set_Distancia_Local(0.0);
	nodoInicial->Set_Distancia_Global(heuristica(nodoInicial, nodoFinal));
	Nodo* nodoActual = nodoInicial;
	
	// Incluir nodo inicio a lista de nodos no testeados para asegurar que
	// se testea. Según avanza el algoritmo los nodos que se vayan 
	// descubriendo se añaden a esta lista para ser testeados 
	std::list<Nodo*> nodosNoTesteados;
	nodosNoTesteados.push_back(nodoActual);
	
	//--------------------------------------------------------------------
	// LÓGICA A_STAR 
	//--------------------------------------------------------------------
	
	// Si la lista de nodos no testeados contiene nodos, indica que puede 
	// haber caminos mejores sin explorar. Aunque paremos de buscar al 
	// llegar al objetivo, puede haber mejores caminos sin probar
	while(!nodosNoTesteados.empty() && nodoActual != nodoFinal)
	{
		// Ordenar los nodos sin testear x distancia global, l d - va l 1º
		nodosNoTesteados.sort([](Nodo* lhs, Nodo* rhs)
		{ return lhs->Get_Global() < rhs->Get_Global(); });
		
		// El primer nodo de la lista de nodos sin testear es en potencia 
		// el más cercano a la meta. La lista también puede contener nodos
		// que han sido visitados, así que hay que descartar este...
		while(!nodosNoTesteados.empty() 
			  && nodosNoTesteados.front()->Get_Visitado())
			nodosNoTesteados.pop_front();
		
		//... o acabar porque no haya nodos válidos para testear
		if(nodosNoTesteados.empty())
			break;
		
		nodoActual = nodosNoTesteados.front();
		nodoActual->Set_Visitado(true); // Sólo se explora cada nodo 1 vez
		
		// Testear cada vecino de estos nodos...
		for(auto nodoVecino : nodoActual->vecinos_)
		{
			// ... y sólo si el vecino no ha sido visitado y no es un 
			// obstáculo se añade a la lista de nodos no testeados
			if(!nodoVecino->Get_Visitado() && !nodoVecino->Get_Obstaculo())
			{
				nodosNoTesteados.push_back(nodoVecino);
			}
			
			// Calcula la distancia potencial del nodo padre + baja posible
			float distanciaMasBaja = nodoActual->Get_Local() +
									 distancia(nodoActual, nodoVecino);
			
			// Si elegir la ruta a través de este nodo es una distancia
			// inferior a la que el vecino actualmente ha establecido,
			// actualizar nodoVecino para usarlo como origen de la ruta,
			// y establecer sus puntajes de distancia según sea necesario
			if(distanciaMasBaja < nodoVecino->Get_Local())
			{
				nodoVecino->Set_Padre(nodoActual);
				nodoVecino->Set_Distancia_Local(distanciaMasBaja);
				// La mejor longitud de ruta para el vecino que se está 
				// probando ha cambiado, por lo que actualiza la puntuación
				// del vecino. La heurística se usa como medida global del
				// algoritmo de ruta, por lo que sabe si está mejorando o
				// empeorando. En algún punto señala que el algoritmo se 
				// dará cuenta de que este camino es peor y lo abandonará,
				// e irá a buscar a lo largo de la siguiente mejor ruta.
				
				nodoVecino->Set_Distancia_Global(nodoVecino->Get_Local() 
					                     + heuristica(nodoVecino, nodoFinal));
			}
		} // FIN for(auto nodoVecino...)
	} // FIN while(!nodosNoTesteados.empty() &&...
	
	// Se añade el Nodo final a la ruta para que el NPC llegue a la meta
	rutaMapa.push_front(nodoFinal);
	// Seguir ruta de nodos padre del final al principio. El 1ero no tiene padre
	Nodo* aux = nodoFinal;
	while(aux->Get_Padre() != nullptr)
	{
		// Como se comprueban los nodos de final a principio se usa push_front
		rutaMapa.push_front(aux->Get_Padre());
		// El siguiente nodo será el padre del actual
		aux = aux->Get_Padre(); 
	}
}
int* Mapa::Adyacentes(int metaX, int metaY, int x, int y)
{
	int* punto = new int[2];
	punto[0] = -1;
	punto[1] = -1;
	// Lambda
	auto libre = [&](int i, int j)
	{
		if(!Get_Nodo(i, j)->Get_Obstaculo() && 
		   !Get_Nodo(i, j)->Get_Visitado())
			return true;
		else return false;		
	};
	//------------------------------
	// ARRIBA O ARRIBA-DERECHA 
	//------------------------------
	if((metaY < y && metaX == x) || (metaY < y && metaX > x))
	{
		Nodo*& aux1 = Get_Nodo(x, y - 1); // ARRIBA
		if(aux1 && libre(x, y - 1))
		{
			punto[0] = x;
			punto[1] = y - 1;
			Get_Nodo(x, y - 1)->Set_Visitado(true);
			nodosVisitados++;
			std::cout << " Jugador por encima voy hacia arriba\n";
		}
		else
		{
			Nodo*& aux2 = Get_Nodo(x + 1, y); // DERECHA
			if(aux2 && libre(x + 1, y))
			{
				punto[0] = x + 1;
				punto[1] = y;
				Get_Nodo(x + 1, y)->Set_Visitado(true);
				nodosVisitados++;
				std::cout << " Jugador por encima voy hacia la derecha\n";
			}
			else
			{
				Nodo*& aux3 = Get_Nodo(x - 1, y);
				if(aux3 && libre(x - 1, y))
				{
					punto[0] = x - 1;
					punto[1] = y;
					Get_Nodo(x - 1, y)->Set_Visitado(true);
					nodosVisitados++;
					std::cout << " Jugador por encima voy la izquierda\n";
				}
				else 
				{
					Nodo*& aux4 = Get_Nodo(x, y + 1);
					if(aux4 && libre(x, y + 1))
					{
						punto[0] = x;
						punto[1] = y + 1;
						Get_Nodo(x, y + 1)->Set_Visitado(true);
						nodosVisitados++;
						std::cout << " Jugador por encima voy hacia abajo\n";
					}
					else // No hay Nodos 
					{
						punto[0] = -2;
						punto[1] = -2;
					}
				}
			}
		}
	}
	//------------------------------
	// DERECHA O DERECHA-ABAJO 
	//------------------------------
	else if((metaX > x && metaY == y) || (metaX > x && metaY > y))
	{
		Nodo*& aux = Get_Nodo(x + 1, y); // DERECHA
		if(aux && libre(x + 1, y))
		{
			punto[0] = x + 1;
			punto[1] = y;
			Get_Nodo(x + 1, y)->Set_Visitado(true);
			nodosVisitados++;
			std::cout << " Jugador por encima voy a la derecha\n";
		}
		else 
		{
			Nodo*& aux2 = Get_Nodo(x, y + 1);
			if(aux2 && libre(x, y + 1))
			{
				punto[0] = x;
				punto[1] = y + 1;
				Get_Nodo(x, y + 1)->Set_Visitado(true);
				nodosVisitados++;
				std::cout << " Jugador por encima voy hacia abajo\n";
			}
			else
			{
				Nodo*& aux3 = Get_Nodo(x - 1, y);
				if(aux3 && libre(x - 1, y))
				{
					punto[0] = x - 1;
					punto[1] = y;
					Get_Nodo(x - 1, y)->Set_Visitado(true);
					nodosVisitados++;
					std::cout << " Jugador por encima voy hacia la izquierda\n";
				}
				else
				{
					Nodo*& aux4 = Get_Nodo(x, y - 1);
					if(aux4 && libre(x, y - 1))
					{
						punto[0] = x;
						punto[1] = y - 1;
						Get_Nodo(x, y - 1)->Set_Visitado(true);
						nodosVisitados++;
						std::cout << " Jugador por encima voy hacia arriba\n";
					}
					else // No hay Nodos 
					{
						punto[0] = -2;
						punto[1] = -2;
					}
				}
			}
		}
	}
	//------------------------------
	// ABAJO O IZQUIERDA-ABAJO
	//------------------------------
	else if((metaY > y && metaX == x) || (metaY > y && metaX < x))
	{
		Nodo*& aux = Get_Nodo(x, y + 1); // ABAJO
		if(aux && libre(x, y + 1)) 
		{
			punto[0] = x;
			punto[1] = y + 1;
			Get_Nodo(x, y + 1)->Set_Visitado(true);
			nodosVisitados++;
			std::cout << " Jugador por encima voy hacia abajo\n";
		}
		else
		{
			Nodo*& aux2 = Get_Nodo(x, y - 1); // IZQUIERDA
			if(aux2 && libre(x - 1, y))
			{
				punto[0] = x - 1;
				punto[1] = y;
				Get_Nodo(x - 1, y)->Set_Visitado(true);
				nodosVisitados++;
				std::cout << " Jugador por encima voy hacia la izquierda\n";
			}
			else
			{
				Nodo*& aux3 = Get_Nodo(x + 1, y); // DERECHA
				if(aux3 && libre(x + 1, y))
				{
					punto[0] = x + 1;
					punto[1] = y;
					Get_Nodo(x + 1, y)->Set_Visitado(true);
					nodosVisitados++;
					std::cout << " Jugador por encima voy hacia la derecha\n";
				}
				else 
				{
					Nodo*& aux4 = Get_Nodo(x, y - 1); // ARRIBA
					if(aux4 && libre(x, y - 1))
					{
						punto[0] = x;
						punto[1] = y - 1;
						Get_Nodo(x, y - 1)->Set_Visitado(true);
						nodosVisitados++;
						std::cout << " Jugador por encima voy hacia arriba\n";
					}
					else // No hay Nodos 
					{
						punto[0] = -2;
						punto[1] = -2;
					}
				}
			}
		}
	}
	//------------------------------
	// IZQUIERDA O IZQUIERDA-ARRIBA
	//------------------------------
	else if((metaX < x && metaY == y) || (metaX < x && metaY < y))
	{
		Nodo*& aux = Get_Nodo(x - 1, y); // IZQUIERDA
		if(aux && libre(x - 1, y))
		{
			punto[0] = x - 1;
			punto[1] = y;
			Get_Nodo(x - 1, y)->Set_Visitado(true);
			nodosVisitados++;
			std::cout << " Jugador por encima voy hacia la izquierda\n";
		}
		else 
		{
			Nodo*& aux2 = Get_Nodo(x, y - 1); // ARRIBA
			if(aux2 && libre(x, y - 1))
			{
				punto[0] = x;
				punto[1] = y - 1;
				Get_Nodo(x, y - 1)->Set_Visitado(true);
				nodosVisitados++;
				std::cout << " Jugador por encima voy hacia arriba\n";
			}
			else 
			{
				Nodo*& aux3 = Get_Nodo(x + 1, y); // DERECHA
				if(aux3 && libre(x + 1, y))
				{
					punto[0] = x + 1;
					punto[1] = y;
					Get_Nodo(x + 1, y)->Set_Visitado(true);
					nodosVisitados++;
					std::cout << " Jugador por encima voy hacia la derecha\n";
				}
				else
				{
					Nodo*& aux4 = Get_Nodo(x, y + 1); // ABAJO
					if(aux4 && libre(x, y + 1))
					{
						punto[0] = x;
						punto[1] = y + 1;
						Get_Nodo(x, y + 1)->Set_Visitado(true);
						nodosVisitados++;
						std::cout << " Jugador por encima voy hacia abajo\n";
					}
					else // No hay Nodos 
					{
						punto[0] = -2;
						punto[1] = -2;
					}
				}
			}
		}
	}
	return punto;
}

bool Mapa::Buscar_Atajo(int npcX, int npcY, int jugX, int jugY)
{
	// Se recuperan los portales del vector 'portales'
	Nodo*& prtAux1 = Get_Nodo(portales.at(0).first, portales.at(0).second);
	Nodo*& prtAux2 = Get_Nodo(portales.at(1).first, portales.at(1).second);
	Nodo*& auxNPC  = Get_Nodo(npcX, npcY);
	Nodo*& auxJug  = Get_Nodo(jugX, jugY);
	// Se calcula la distancia al portal + cercano
	auto distancias = [](Nodo* a, Nodo* b, Nodo* c, std::string s)
	{
		// Nodos : a = NPC o jugador, b = portal 1, c = portal 2
		auto distancia1 = sqrt(pow(a->Get_X() - b->Get_X(), 2)
							   + pow(a->Get_Y() - b->Get_Y(), 2));
		
		auto distancia2 = sqrt(pow(a->Get_X() - c->Get_X(), 2)
							   + pow(a->Get_Y() - c->Get_Y(), 2));
		if(s == "NPC_y_portal+cercano" || s == "Jugador_y_portal+cercano")
		{	
			if(distancia1 < distancia2)
				return distancia1;
			else return distancia2;
		}
		else if(s == "NPC_Jugador")
		{
			return sqrt(pow(a->Get_X() - b->Get_X(), 2)
						+ pow(a->Get_Y() - b->Get_Y(), 2));
		}
	};
	
	// Si la distancia entre el NPC y su portal + cercano + la distancia 
	// entre el jugador y el suyo es < que la distancia entre el NPC y el jugador,
	// el NPC usará el portal 
	if(( distancias(auxNPC, prtAux1, prtAux2, "NPC_y_portal+cercano")
		+ distancias(auxJug, prtAux1, prtAux2, "Jugador_y_portal+cercano"))
		< distancias(auxNPC, auxJug, prtAux1, "NPC_Jugador"))
	{
		return true;
	}
	else return false;
}

void Mapa::Reset_Visitadas()
{
	for (int i = 0; i < ANCHO; i++)
	{
		for(int j = 0; j < ALTO; j++)
		{
			if(Get_Nodo(i, j)->Get_Visitado())
				Get_Nodo(i, j)->Set_Visitado(false);
		}
	}	
}

void Mapa::Usar_Portal(int npcX, int npcY)
{
	// Nodo que apunta al portal + cercano
	auto portalMasCercano = [](Nodo* NPC, Nodo* portal1, Nodo* portal2)
	{
		// distancia1 entre NPC y portal 1
		int distancia1 = sqrt(pow(NPC->Get_X() - portal1->Get_X(), 2)
							  + pow(NPC->Get_Y() - portal1->Get_Y(), 2));
			
		// distancia2 entre NPC y portal 2
		int distancia2 = sqrt(pow(NPC->Get_X() - portal2->Get_X(), 2)
							  + pow(NPC->Get_Y() - portal2->Get_Y(), 2));
		
		Nodo*& aux = portal1;
		
		if(distancia2 < distancia1)
			aux = portal2;
		
		return aux;
	};
	
	Nodo*& portalCercano = Get_Nodo(1, 1);
	Nodo*& prtAux1 = Get_Nodo(portales.at(0).first, portales.at(0).second);
	Nodo*& prtAux2 = Get_Nodo(portales.at(1).first, portales.at(1).second);
	Nodo*& auxNPC  = Get_Nodo(npcX, npcY);
	// Igualarlo a 'portalMasCercano'
	portalCercano = portalMasCercano(auxNPC, prtAux1, prtAux2);
	// Usar 
	A_Star(auxNPC->Get_X(), auxNPC->Get_Y(), 
		  portalCercano->Get_X(), portalCercano->Get_Y());	
}

/*
	Lista Personajes -> K > L > M > N > O
	Lista bombas -> A > G > K > P > O

	Eventos > K-Caminar, B-Explotar, K-Morir

	Personaje: 
		Eventos:
			> Caminar
			> Atacar
			> Comer 
			> Morir
			> Lanzar hechizo


	Ciclo - Caminando por el prado
		Límite : 25 ms //Lo + q podemos tardar en procesar todo hasta q se dibuje el siguiente frame
		Consume:  5 ms //Lo que tarda en procesarlo todo

	Ciclo - Caminando por un campo de batalla con bombas tiros y Kim Jong Un luchando en el cielo contra Trump
		Límite  : 25 ms //Lo más que podemos tardar en procesar todo hasta que se dibuje el siguiente frame
		Consume : 37 ms //Lo que tarda en procesarlo todo
	
	Solución - Multithreading
		> Hilo 1 - Dibuja la pantalla
		> Hilo 2 - Procesa eventos
		> Hilo 3 - Elimina objetos no útiles
		> Hilo 4 - Controla los spawn de los npc 


	Paso 1 
		Disparo
	Paso 2
		Comprobar colisión disparo
		Repetir
	Paso 3
		La colisión se produce, lanzo un evento de colisión con p1 desde p2
	Paso 4
		Proceso colisiones


[ ][ ][ ][ ][ ][ ][ ][ ]
[ ][ ][+][+][+][ ][ ][ ]
[ ][+][ ][ ][ ][+][ ][ ]
[ ][+][ ][M][ ][+][ ][ ]
[ ][+][ ][ ][P][+][ ][ ]
[ ][ ][+][+][+][P][ ][ ]
[ ][ ][ ][G][ ][ ][O][ ]
[ ][ ][ ][ ][ ][ ][ ][ ]


*/


////****** FUNCIONES PARA CARGAR DATOS DE UN FICHERO DE TEXTO ******////
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



ListaCoordenadas => Aprox 100 coordenadas que representan una coordenada de zona y una de Nodo cada una
ListaEntidades => 1.000.000 Entidades (NPC, Jugadores, Árboles, etc)
ListaRepresentable => Aquí se generan una lista de entre X e Y elementos



*/
