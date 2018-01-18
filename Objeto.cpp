#include "Objeto.h"

Objeto::Objeto():ataque_(0), defensa_(0), energia_(0),nombre_(" "), tag_(' '),
tono_(" "), vidas_(0), x_(0), y_(0){}
Objeto::Objeto(int a, int d, int e, std::string n, char t, std::string to, 
int v, int x, int y):ataque_(a), defensa_(d), energia_(e), nombre_(n),
tag_(t), tono_(to), vidas_(v), x_(x), y_(y){}
Objeto::~Objeto(){}

// ======================================================================================
// GETTERS
// ======================================================================================
int  Objeto::Get_Ataque()       { return ataque_;  }
int  Objeto::Get_Defensa()      { return defensa_; }
int  Objeto::Get_Energia() 	    { return energia_; }
std::string Objeto::Get_Nombre(){ return nombre_;  }
char Objeto::Get_Tag() 	        { return tag_;     }
int  Objeto::Get_Tono()
{
    if(tono_ == "marron")
        return 1;
    else if(tono_ == "verde")
        return 2;
    else return 3;
}
int  Objeto::Get_Vidas(){ return vidas_; }
int  Objeto::Get_X() 	{ return x_;     }
int  Objeto::Get_Y() 	{ return y_;     }

// ======================================================================================
// SETTERS
// ======================================================================================
void Objeto::Set_Ataque(int i) { ataque_  = i; }
void Objeto::Set_Defensa(int i){ defensa_ = i; }
void Objeto::Set_Energia(int i){ energia_ = i; }
void Objeto::Set_Tag(char c)   { tag_ = c;     }
void Objeto::Set_Tono(char c)  { tono_ = c;    }
void Objeto::Set_Vidas(int i)  { vidas_ += i;  }
void Objeto::Set_X(int i) 	   { x_ = i;       }
void Objeto::Set_Y(int i)      { y_ = i;       }

// ======================================================================================
// MÉTODOS
// ======================================================================================
void Objeto::Mueve(int i, int x, int y)
{
	switch(i)
	{
	case 1: // ABAJO
	{
		if(y_ + 1 < ALTO - 1)
		{
			Nodo*& aux = Mapa::Instancia()->Get_Nodo(x, y + 1);
			if(aux != NULL)
			{
				if(aux->Get_Obstaculo() == false)
					y_++;
			}
		}
	}
	break;
	case 2: // ARRIBA
	{
		if(y_ - 1 > 0)
		{
			Nodo*& aux = Mapa::Instancia()->Get_Nodo(x, y - 1);
			if(aux != NULL)
			{
				if(aux->Get_Obstaculo() == false)
					y_--;
			}
		}
	}
	break;
	case 3: // DERECHA
	{
		if(x_ + 1 < ANCHO - 1)
		{
			Nodo*& aux = Mapa::Instancia()->Get_Nodo(x + 1, y);
			if(aux != NULL)
			{
				if(aux->Get_Obstaculo() == false)
					x_++;
			}
		}
	}
	break;
	case 4: // IZQUIERDA
	{
		if(x_ - 1 > 0)
		{
			Nodo*& aux = Mapa::Instancia()->Get_Nodo(x - 1, y);
			if(aux != NULL)
			{
				if(aux->Get_Obstaculo() == false)
					x_--;
			}
		}
	}
	break;
	case 5: // ALEATORIO
	{
		int max = 4;
		int min = 1;
		int aleatorio = rand() % (max - min) + min;
		Mueve(aleatorio, x, y);
	}
	break;
	case 6: // BACKTRACKING 
	{
		
	}
	break;
	case 7: // PERSEGUIR
	{
		int max = 100;
		int min = 0;
		int aleatorio = rand() % (max - min) + min;
		
		// Teorema de Pitágoras
		float campoVision = sqrt(pow(x_ - x, 2) + pow(y_ - y, 2));
		
		// Si el campo de visión es menor o igual a 3 el NPC persigue al Objeto
		if(campoVision <= 7)
		{
			if(y_ > y)
			{
				// Objeto está a la izquierda
				if(x_ > x)
				{
					if(aleatorio <= 50)
					{
						Mueve(2, x, y); // Arriba
					}
					else Mueve(4, x, y); // Izquierda
				}
				// Objeto está hacia la derecha
				else if(x_ < x)
				{
					if(aleatorio <= 50)
					{
						Mueve(2, x, y); // Arriba
					}
					else Mueve(3, x, y); // Derecha
				}
				// Objeto está en la misma columna
				else
				{
					Mueve(2, x, y); // Arriba
				}
			}
			else if(y_ < y)
			{
				// Objeto está a la izquierda
				if(x_ > x)
				{
					if(aleatorio <= 50)
					{
						Mueve(1, x, y); // Abajo
					}
					else Mueve(4, x, y); // Izquierda
				}
				// Objeto está hacia la derecha
				else if(x_ < x)
				{
					if(aleatorio <= 50)
					{
						Mueve(1, x, y); // Abajo
					}
					else Mueve(3, x, y); // Derecha
				}
				// Objeto está en la misma columna
				else
				{
					Mueve(1, x, y); // Abajo
				}
			}
			else if(y_ == y)
			{
				if(x_ > x)
				{
					Mueve(4, x, y); // Izquierda
				}
				else if(x_ < x)
				{
					Mueve(3, x, y); // Derecha
				}
			}
		} // Fin if(campo_vision)
		// Y si el campo de visión es mayor que 3 el NPC se mueve aleatoriamente
		else Mueve(5, x, y);
	}
	break;
	case 8: // PATRULLAR
	{
		if(y_ + 1 < ALTO - 1) // ABAJO
		{
			Nodo*& aux = Mapa::Instancia()->Get_Nodo(x, y + 1);
			if(aux)
			{
			if(!aux->Get_Obstaculo())
				y_++;
				
			}
			else if(y_ - 1 > 0) // ARRIBA
			{
				Nodo*& aux = Mapa::Instancia()->Get_Nodo(x, y - 1); 
				if(!aux->Get_Obstaculo())
					y_--;	
				else if(x_ + 1 < ANCHO - 1) // DERECHA
				{
					Nodo*& aux = Mapa::Instancia()->Get_Nodo(x + 1, y); 
					if(!aux->Get_Obstaculo())
						x_++;	
					else if(x_ - 1 > 0) // IZQUIERDA
					{
						Nodo*& izquierda = Mapa::Instancia()->Get_Nodo(x_ - 1, y_);
						if(!izquierda->Get_Obstaculo())
							x_--;
					}
				}
			}
		}
	}
	break;
	} // Fin switch
}

void Objeto::Mueve_Por_Ruta()
{
	if(ruta_.size() != 0)
	{
		while(x_ == ruta_.front()->Get_X() && y_ == ruta_.front()->Get_Y())
		{
			ruta_.pop_front();	
		}
		if(!ruta_.front()->Get_Obstaculo())
		{
			x_ = ruta_.front()->Get_X();
			y_ = ruta_.front()->Get_Y();
		}
	}
}

////////////////
//-Pathfinding
///////////////
void Objeto::Busca_Caminos(int jugadorX, int jugadorY)
{
	// Se vacía la ruta para recalcularla en cada llamada
	ruta_.clear();
	
	// Si hay atajo
	if(Mapa::Instancia()->Buscar_Atajo(x_, y_, jugadorX, jugadorY))
	{
		// Se elige aleatorimente si se usa o no 
		int max = 4;
		int min = 1;
		int aleatorio = rand() % (max - min) + min;
		if(aleatorio == 1)
			Mapa::Instancia()->A_Star(x_, y_, jugadorX, jugadorY);
		else Mapa::Instancia()->Usar_Portal(x_, y_);
	}
	else Mapa::Instancia()->A_Star(x_, y_, jugadorX, jugadorY);	
	ruta_ = Mapa::Instancia()->Get_Ruta_Mapa();
	Mueve_Por_Ruta();
}
void Objeto::Backtracking(int metaX, int metaY)
{
	int nodosVisitados = 0;
	int pasos = 0;
	struct punto { int x; int y; };
	punto temp;
	temp.x = -1;
	temp.y = -1;
	std::vector<punto> puntos;
	// Mientras x_ e y_ sean distintas de metaX y metaY buscar Nodos
	//while((x_ != metaX && y_ != metaY) || (mapa.Get_Nodos_Visitadas() 
		  //< mapa.Get_Ancho_Mapa() * mapa.Get_Alto_Mapa()))
	{
		// Resetear Nodos visitadas 
		Mapa::Instancia()->Reset_Visitadas();
		
		if(puntos.size() == 0)
		{
			// Hay 8 movimientos dependiendo de donde se encuentre el jugador :
			// -Encima o encima-derecha : intentará encima, derecha, izquierda, abajo
			// -Derecha o debajo-derecha : intentará derecha, abajo, izquierda, arriba
			// -Debajo o debajo-izquierda : intentará abajo, izquierda, derecha, arriba
			// -Izquierda o izquierda-encima : intentará izquierda, arriba, derecha, abajo
			
			int* auxiliar = new int[2];
			auxiliar = Mapa::Instancia()->Adyacentes(metaX, metaY, x_, y_);
			// Si auxiliar tiene valores -1 y -1 quiere decir que no hay 
			// Nodos a las que moverse. Si los valores son -2 y -2 es 
			// que está fuera de los límites. El resto de valores indica
			// que se ha encontrado una Nodo. 
			if(auxiliar[0] == -1 || auxiliar[0] == -2)
				Mueve(7, metaX, metaY); // NO HAY NodoS LIBRES
			else
			{
				x_ = auxiliar[0];
				y_ = auxiliar[1];
				temp.x = auxiliar[0];
				temp.y = auxiliar[1];
				puntos.push_back(temp);
				pasos++;
				std::cout << " Llevo " << pasos << " pasos\n";
				std::cout << " Estoy en " << x_ << ", " << y_ << "\n";
			}
		} // FIN if(puntos.size() == 0)
		else // Si hay 'puntos' se sigue buscando desde el último incluido
		{
			punto ultimo;
			ultimo.x = puntos.at(puntos.size()-1).x;
			ultimo.y = puntos.at(puntos.size()-1).y;
			int* auxiliar2 = new int[2];
			auxiliar2 = Mapa::Instancia()->Adyacentes(metaX, metaY, ultimo.x, ultimo.y);
			// Si auxiliar2 tiene valores -1 y -1 quiere decir que no hay 
			// Nodos a las que moverse. Si los valores son -2 y -2 es 
			// que está fuera de los límites. El resto de valores indica
			// que se ha encontrado una Nodo. 
			if(auxiliar2[0] == -1 || auxiliar2[0] == -2)
			{
				// Como no se han encontrado Nodos libres adyacentes
				// al último punto, se borra y se hace backtracking
				puntos.pop_back();
			}
			else
			{
				x_ = auxiliar2[0];
				y_ = auxiliar2[1];
				ultimo.x = auxiliar2[0];
				ultimo.y = auxiliar2[1];
				puntos.push_back(ultimo);
				pasos++;
				std::cout << " Llevo " << pasos << " pasos\n";
				std::cout << " Estoy en " << x_ << ", " << y_ << "\n";
			}
		}
	}// FIN while(x_ != ....)
}

///////////
//-Varios
//////////
void Objeto::Ver_Ruta()
{
	auto contador = 0;
	std::cout << " Ruta contiene " << ruta_.size() << " elementos\n"; 
	for(auto it : ruta_)
	{
		std::cout << " Nodo[" << contador << "].x = " << (*it).Get_X();
		std::cout << "\t";
		std::cout << " Nodo[" << contador << "].y = " << (*it).Get_Y();
		std::cout << "\n";
		contador++;
	}
}
/*
Ejemplo 1. El enemigo no tiene obstáculos hacia el jugador

	0  1  2  3  4  5  6  7  8  9
 0 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 1 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 2 [ ][ ][v][ ][ ][ ][ ][ ][ ][ ]
 3 [ ][ ][>][v][ ][ ][ ][ ][ ][ ]
 4 [ ][ ][ ][>][v][ ][ ][ ][ ][ ]
 5 [ ][ ][ ][ ][J][ ][ ][ ][ ][ ]
 6 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 7 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 8 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 9 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]

	La lógica del enemigo es:
	Si está en mi horizontal solo me desplazo a los lados
	Si está en mi vertical solo me desplazo hacia abajo_ o arriba
	Si está en diagonal bajo y luego me desplazo hacia la derecha o izquierda segun toque
	*Para hacer esta debemos calcular cual Nodo de destino está más cerca

	PROBLEMA: Si tiene un obstáculo en la posición más cercana siguiente no se moverá

Ejemplo 2. El enemigo tiene obstáculos sencillos

	0  1  2  3  4  5  6  7  8  9
 0 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 1 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 2 [ ][ ][v][ ][ ][ ][ ][ ][ ][ ]
 3 [ ][ ][>][>][V][ ][ ][ ][ ][ ]
 4 [ ][ ][ ][+][V][ ][ ][ ][ ][ ]
 5 [ ][ ][ ][ ][J][ ][ ][ ][ ][ ]
 6 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 7 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 8 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 9 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]

	La lógica del enemigo es:
	Si está en mi horizontal solo me desplazo a los lados
	Si está en mi vertical solo me desplazo hacia abajo_ o arriba
	Si está en diagonal bajo y luego me desplazo hacia la derecha o izquierda segun toque
	*Para hacer esta debemos calcular cual Nodo de destino está más cerca
	*Si no puede desplazarse a la más cercana se va a la otra

	PROBLEMA: Si tiene un obstáculo complejo se puede quedar atrapado

Ejemplo 3. El enemigo tiene obstáculos sencillos

	0  1  2  3  4  5  6  7  8  9
 0 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 1 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 2 [ ][ ][v][ ][ ][ ][ ][ ][ ][ ]
 3 [ ][ ][>][>][>][v][ ][ ][ ][ ]
 4 [ ][ ][ ][+][+][v][ ][ ][ ][ ]
 5 [ ][ ][ ][ ][J][<][ ][ ][ ][ ]
 6 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 7 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 8 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
 9 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]

	La lógica del enemigo es:
	Si está en mi horizontal solo me desplazo a los lados
	Si está en mi vertical solo me desplazo hacia abajo_ o arriba
	Si está en diagonal bajo y luego me desplazo hacia la derecha o izquierda segun toque
	*Para hacer esta debemos calcular cual Nodo de destino está más cerca
	*Si no puede desplazarse a la más cercana se va a la otra

	PROBLEMA: Si tiene un obstáculo complejo se puede quedar atrapado

Ejemplo 4. El enemigo tiene obstáculos complejos

	0  1  2  3  4  5  6  7  8  9
 0 [5][4][3][4][5][6][7][ ][ ][ ]
 1 [4][3][2][3][4][5][6][7][ ][ ]
 2 [3][2][1][2][3][4][5][6][7][ ]
 3 [4][3][2][3][4][+][6][7][ ][ ]
 4 [5][4][3][+][+][+][7][ ][ ][ ]
 5 [6][5][4][5][J][ ][ ][ ][ ][ ]
 6 [7][6][5][6][7][ ][ ][ ][ ][ ]
 7 [ ][7][6][7][ ][ ][ ][ ][ ][ ]
 8 [ ][ ][7][ ][ ][ ][ ][ ][ ][ ]
 9 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]

	Vamos a cotejar todas las posiciones de destino válidas, para cada posición, haremos lo mismo
	y así sucesivamente hasta que alguna rama toque con el jugador o acabemos con todas las Nodos
	disponibles.

	Para optimizar esto habrá que tener en cuenta alguna condición que nos permita cribar cuáles son
	las posiciones óptimas para utilizar. Además, esto lo podemos hacer cuando se encuentre con
	obstáculos o siempre.

	Tenemos que tener en cuenta que sabemos dónde está el jugador siempre.

	Se crearía una estructura o clase que represente la Nodo y el estado en el que se encuentre
	es decir, si ha sido visitada previamente o no. Vamos a dar preferencia siempre a Nodos no
	visitadas. Así cribaremos por cada ramificación y no caminaremos sobre nuestros pasos.

	Vamos a tener que utilizar funciones recursivas para poder hacer esto. El objetivo es que una
	función recursiva haga llamadas sucesivas a sí misma hasta que completemos un árbol de opciones.
	Tendremos que obtener de este árbol el camino solución que es el que nos lleva al jugador. Si
	hay varios caminos directamente cogeremos el que menos saltos tenga.

	Para saber las Nodos que llevamos pisadas sería recomendable crear un vector que nos indique
	las que hemos visitado ya. Así nos evitaremos volver sobre nuestros pasos y además obtendremos
	una manera rápida de comprobar el estado de las Nodos sin necesidad de recorrer el árbol
	hacia atrás.

	Una opción para ver cuándo finalizar una rama es partir de que no vemos más allá de esa rama.

	Si por ejemplo el NPC está en 0:0 y una rama lo lleva hasta 0:7 y su visión es de 5, la rama
	esta acabará como mucho en 0:5, si no hay solución válida en 0:5, es decir, si no hay jugador
	en 0:5, no hay posibilidad de llegar a él en esta rama, por lo cual la descartaremos. La
	descartamos al tener ya todas las ramas, pero en cuanto a la recursividad esto sería un caso
	base. Hemos llegado más allá de la visión que tenemos, este nodo no se añade y por lo tanto
	salimos de esta llamada recursiva.


	2:2
		1:2
			1:1
			0:2
			1:3
		2:1
			1:1
			2:0
			3:1
		2:3
			1:3
			2:4
			3:3
		3:2
			3:1
			3:3
			4:2
				4:1
				5:2
					5:1
					5:3
						5:4 [JUGADOR]
						6:3
					6:2
						6:3
						6:4
							5:4 [JUGADOR]


		   0  1  2  3  4  5  6  7  8  9
		0 [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
		1 [ ][N][ ][ ][ ][ ][ ][ ][ ][ ]
		2 [ ][>][v][ ][ ][ ][ ][ ][ ][ ]
		3 [ ][ ][>][>][>][>][>][>][v][ ]
		4 [+][+][+][+][+][+][+][+][v][ ]
		5 [ ][ ][ ][ ][v][<][<][<][<][ ]
		6 [ ][ ][·][·][!][ ][ ][ ][ ][ ]
		7 [ ][·][·][ ][·][·][x][ ][ ][ ]
		8 [·][·][ ][ ][x][I][x][ ][ ][ ]
		9 [J][ ][ ][ ][ ][ ][ ][ ][ ][ ]


		1.- Algoritmo para generar rutas
		2.- Ruta generada en memoria
			2.1.- Si veo al jugador
				- Genero una ruta por cada cambio de Nodo del jugador
				o
				- Genero una ruta en cada paso que doy
			2.2.- Si no veo al jugador
				- Mantengo la ultima ruta guardada en memoria
				y
				- No genero más rutas
		3.- Si no tengo ruta generada y no veo al jugador
			- Patrullo aleatoriamente
			o
			- Me quedo quieto que se está cómodo


	A -> B
			-> C  -> F
			-> D           -> H
	  -> E  -> D  -> O

	B 64% <-- % adicional o negativo en base a la cantidad feromona
	E 36% <--

	A > B > D > O > H > O > D > B > A
*/
