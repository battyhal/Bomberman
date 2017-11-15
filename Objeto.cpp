#include "Objeto.h"

Objeto::Objeto() : ataque(0), defensa(0), energia(0), nombre(" "), tag(' '), vidas(0), x(0), y(0) {}
Objeto::Objeto(int _ataque, int _defensa, int _energia, std::string _nombre, char _tag, 
			   int _vidas, int _x, int _y) : ataque(_ataque), defensa(_defensa), energia(_energia),
			   nombre(_nombre), tag(_tag), vidas(_vidas), x(_x), y(_y) {}
Objeto::~Objeto() {}

// ---------------------------------------------------------------
// GETTERS 
// ---------------------------------------------------------------
int  Objeto::Get_Ataque()        { return ataque; }
int  Objeto::Get_Defensa()       { return defensa; }
int  Objeto::Get_Energia() 	     { return energia; }
std::string Objeto::Get_Nombre() { return nombre; }
char Objeto::Get_Tag() 	         { return tag; }
int  Objeto::Get_Vidas()         { return vidas; }
int  Objeto::Get_X() 	         { return x; }
int  Objeto::Get_Y() 	         { return y; }

// ---------------------------------------------------------------
// SETTERS
// ---------------------------------------------------------------
void Objeto::Set_Ataque(int i)	{ ataque = i; }
void Objeto::Set_Defensa(int i)	{ defensa = i; }
void Objeto::Set_Energia(int i) { energia -= i; }
void Objeto::Set_Tag(char c)    { tag = c; }
void Objeto::Set_Vidas(int i)   { vidas += i; } 
void Objeto::Set_X(int i) 		{ x = i; }
void Objeto::Set_Y(int i)       { y = i; }

// ---------------------------------------------------------------
// MÉTODOS
// ---------------------------------------------------------------
int  Objeto::Cuenta_Atras() { return 0; }
void Objeto::Mover(int i, Mapa& mapa, int _x, int _y)
{
	switch(i)
	{
	case 1: // ARRIBA 
	{
		// Si casilla no está ocupada
		if(mapa.Get_Contenido_Casilla(x, y - 1) == ' ')
		{
			y--; 
		}
	}
	break;
	case 2: // ABAJO
	{
		// Si casilla no está ocupada
		if(mapa.Get_Contenido_Casilla(x, y + 1) == ' ')
		{
			y++; 
		}
	}
	break;
	case 3: // IZQUIERDA
	{
		// Si casilla no está ocupada
		if(mapa.Get_Contenido_Casilla(x - 1, y) == ' ')
		{
			x--; 
		}
	}
	break;
	case 4: // DERECHA 
	{
		// Si casilla no está ocupada
		if(mapa.Get_Contenido_Casilla(x + 1, y) == ' ')
		{
			x++; 
		}
	}
	break;
	case 5: // ALEATORIO
	{
		int max = 4;
		int min = 1;
		int aleatorio = rand() % (max - min) + min;
		Mover(aleatorio, mapa, _x, _y);
	}
	break;
	case 6: // PERSEGUIR
	{
		int max = 100;
		int min = 0;
		int aleatorio = rand() % (max - min) + min;
		
		// Teorema de Pitágoras 
		float campo_vision = sqrt(pow(x - _x, 2) + pow(y - _y, 2));
		
		// Si el campo de visión es menor o igual a 3 el NPC persigue al Objeto
		if(campo_vision <= 3)
		{
			if(y > _y)
			{
				// Objeto está a la izquierda
				if(x > _x)
				{
					if(aleatorio <= 50)
					{
						Mover(1, mapa, _x, _y); // Arriba
					}
					else Mover(3, mapa, _x, _y); // Izquierda
				}
				// Objeto está hacia la derecha
				else if(x < _x)
				{
					if(aleatorio <= 50)
					{
						Mover(1, mapa, _x, _y); // Arriba
					}
					else Mover(4, mapa, _x, _y); // Derecha
					
				}
				// Objeto está en la misma columna
				else 
				{
					Mover(1, mapa, _x, _y); // Arriba
				}
			}
			else if(y < _y)
			{
				// Objeto está a la izquierda
				if(x > _x)
				{				
					if(aleatorio <= 50)
					{
						Mover(2, mapa, _x, _y); // Abajo
					}
					else Mover(3,mapa, _x, _y); // Izquierda
				}
				// Objeto está hacia la derecha
				else if(x < _x)
				{
					if(aleatorio <= 50)
					{
						Mover(2, mapa, _x, _y); // Abajo
					}
					else Mover(4, mapa, _x, _y); // Derecha
				}
				// Objeto está en la misma columna
				else 
				{
					Mover(2, mapa, _x, _y); // Abajo
				}
			}
			else if(y == _y)
			{
				if(x > _x)
				{
					Mover(3, mapa, _x, _y); // Izquierda
				}
				else if(x < _x)
				{
					Mover(4,mapa, _x, _y); // Derecha
				}
			}
		} // Fin if(campo_vision)
		// Y si el campo de visión es mayor que 3 el NPC se mueve aleatoriamente
		else Mover(5, mapa, _x, _y);
	}
	break;
	} // Fin switch
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
	Si está en mi vertical solo me desplazo hacia abajo o arriba
	Si está en diagonal bajo y luego me desplazo hacia la derecha o izquierda segun toque
	*Para hacer esta debemos calcular cual casilla de destino está más cerca 
	
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
	Si está en mi vertical solo me desplazo hacia abajo o arriba
	Si está en diagonal bajo y luego me desplazo hacia la derecha o izquierda segun toque
	*Para hacer esta debemos calcular cual casilla de destino está más cerca 
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
	Si está en mi vertical solo me desplazo hacia abajo o arriba
	Si está en diagonal bajo y luego me desplazo hacia la derecha o izquierda segun toque
	*Para hacer esta debemos calcular cual casilla de destino está más cerca 
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
	y así sucesivamente hasta que alguna rama toque con el jugador o acabemos con todas las casillas
	disponibles.

	Para optimizar esto habrá que tener en cuenta alguna condición que nos permita cribar cuáles son
	las posiciones óptimas para utilizar. Además, esto lo podemos hacer cuando se encuentre con
	obstáculos o siempre. 

	Tenemos que tener en cuenta que sabemos dónde está el jugador siempre. 

	Se crearía una estructura o clase que represente la casilla y el estado en el que se encuentre
	es decir, si ha sido visitada previamente o no. Vamos a dar preferencia siempre a casillas no
	visitadas. Así cribaremos por cada ramificación y no caminaremos sobre nuestros pasos.

	Vamos a tener que utilizar funciones recursivas para poder hacer esto. El objetivo es que una 
	función recursiva haga llamadas sucesivas a sí misma hasta que completemos un árbol de opciones.
	Tendremos que obtener de este árbol el camino solución que es el que nos lleva al jugador. Si
	hay varios caminos directamente cogeremos el que menos saltos tenga.

	Para saber las casillas que llevamos pisadas sería recomendable crear un vector que nos indique
	las que hemos visitado ya. Así nos evitaremos volver sobre nuestros pasos y además obtendremos
	una manera rápida de comprobar el estado de las casillas sin necesidad de recorrer el árbol 
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
		7 [ ][·][·][ ][ ][ ][ ][ ][ ][ ]
		8 [·][·][ ][ ][ ][ ][ ][ ][ ][ ]
		9 [J][ ][ ][ ][ ][ ][ ][ ][ ][ ]


		1.- Algoritmo para generar rutas 
		2.- Ruta generada en memoria
			2.1.- Si veo al jugador
				- Genero una ruta por cada cambio de casilla del jugador 
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
