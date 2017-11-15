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
// M�TODOS
// ---------------------------------------------------------------
int  Objeto::Cuenta_Atras() { return 0; }
void Objeto::Mover(int i, Mapa& mapa, int _x, int _y)
{
	switch(i)
	{
	case 1: // ARRIBA 
	{
		// Si casilla no est� ocupada
		if(mapa.Get_Contenido_Casilla(x, y - 1) == ' ')
		{
			y--; 
		}
	}
	break;
	case 2: // ABAJO
	{
		// Si casilla no est� ocupada
		if(mapa.Get_Contenido_Casilla(x, y + 1) == ' ')
		{
			y++; 
		}
	}
	break;
	case 3: // IZQUIERDA
	{
		// Si casilla no est� ocupada
		if(mapa.Get_Contenido_Casilla(x - 1, y) == ' ')
		{
			x--; 
		}
	}
	break;
	case 4: // DERECHA 
	{
		// Si casilla no est� ocupada
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
		
		// Teorema de Pit�goras 
		float campo_vision = sqrt(pow(x - _x, 2) + pow(y - _y, 2));
		
		// Si el campo de visi�n es menor o igual a 3 el NPC persigue al Objeto
		if(campo_vision <= 3)
		{
			if(y > _y)
			{
				// Objeto est� a la izquierda
				if(x > _x)
				{
					if(aleatorio <= 50)
					{
						Mover(1, mapa, _x, _y); // Arriba
					}
					else Mover(3, mapa, _x, _y); // Izquierda
				}
				// Objeto est� hacia la derecha
				else if(x < _x)
				{
					if(aleatorio <= 50)
					{
						Mover(1, mapa, _x, _y); // Arriba
					}
					else Mover(4, mapa, _x, _y); // Derecha
					
				}
				// Objeto est� en la misma columna
				else 
				{
					Mover(1, mapa, _x, _y); // Arriba
				}
			}
			else if(y < _y)
			{
				// Objeto est� a la izquierda
				if(x > _x)
				{				
					if(aleatorio <= 50)
					{
						Mover(2, mapa, _x, _y); // Abajo
					}
					else Mover(3,mapa, _x, _y); // Izquierda
				}
				// Objeto est� hacia la derecha
				else if(x < _x)
				{
					if(aleatorio <= 50)
					{
						Mover(2, mapa, _x, _y); // Abajo
					}
					else Mover(4, mapa, _x, _y); // Derecha
				}
				// Objeto est� en la misma columna
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
		// Y si el campo de visi�n es mayor que 3 el NPC se mueve aleatoriamente
		else Mover(5, mapa, _x, _y);
	}
	break;
	} // Fin switch
}

/*

Ejemplo 1. El enemigo no tiene obst�culos hacia el jugador

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

	La l�gica del enemigo es: 
	Si est� en mi horizontal solo me desplazo a los lados
	Si est� en mi vertical solo me desplazo hacia abajo o arriba
	Si est� en diagonal bajo y luego me desplazo hacia la derecha o izquierda segun toque
	*Para hacer esta debemos calcular cual casilla de destino est� m�s cerca 
	
	PROBLEMA: Si tiene un obst�culo en la posici�n m�s cercana siguiente no se mover�

Ejemplo 2. El enemigo tiene obst�culos sencillos

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

	La l�gica del enemigo es:
	Si est� en mi horizontal solo me desplazo a los lados
	Si est� en mi vertical solo me desplazo hacia abajo o arriba
	Si est� en diagonal bajo y luego me desplazo hacia la derecha o izquierda segun toque
	*Para hacer esta debemos calcular cual casilla de destino est� m�s cerca 
	*Si no puede desplazarse a la m�s cercana se va a la otra
	
	PROBLEMA: Si tiene un obst�culo complejo se puede quedar atrapado

Ejemplo 3. El enemigo tiene obst�culos sencillos

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

	La l�gica del enemigo es:
	Si est� en mi horizontal solo me desplazo a los lados
	Si est� en mi vertical solo me desplazo hacia abajo o arriba
	Si est� en diagonal bajo y luego me desplazo hacia la derecha o izquierda segun toque
	*Para hacer esta debemos calcular cual casilla de destino est� m�s cerca 
	*Si no puede desplazarse a la m�s cercana se va a la otra

	PROBLEMA: Si tiene un obst�culo complejo se puede quedar atrapado

Ejemplo 4. El enemigo tiene obst�culos complejos

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

	Vamos a cotejar todas las posiciones de destino v�lidas, para cada posici�n, haremos lo mismo
	y as� sucesivamente hasta que alguna rama toque con el jugador o acabemos con todas las casillas
	disponibles.

	Para optimizar esto habr� que tener en cuenta alguna condici�n que nos permita cribar cu�les son
	las posiciones �ptimas para utilizar. Adem�s, esto lo podemos hacer cuando se encuentre con
	obst�culos o siempre. 

	Tenemos que tener en cuenta que sabemos d�nde est� el jugador siempre. 

	Se crear�a una estructura o clase que represente la casilla y el estado en el que se encuentre
	es decir, si ha sido visitada previamente o no. Vamos a dar preferencia siempre a casillas no
	visitadas. As� cribaremos por cada ramificaci�n y no caminaremos sobre nuestros pasos.

	Vamos a tener que utilizar funciones recursivas para poder hacer esto. El objetivo es que una 
	funci�n recursiva haga llamadas sucesivas a s� misma hasta que completemos un �rbol de opciones.
	Tendremos que obtener de este �rbol el camino soluci�n que es el que nos lleva al jugador. Si
	hay varios caminos directamente cogeremos el que menos saltos tenga.

	Para saber las casillas que llevamos pisadas ser�a recomendable crear un vector que nos indique
	las que hemos visitado ya. As� nos evitaremos volver sobre nuestros pasos y adem�s obtendremos
	una manera r�pida de comprobar el estado de las casillas sin necesidad de recorrer el �rbol 
	hacia atr�s.

	Una opci�n para ver cu�ndo finalizar una rama es partir de que no vemos m�s all� de esa rama.

	Si por ejemplo el NPC est� en 0:0 y una rama lo lleva hasta 0:7 y su visi�n es de 5, la rama 
	esta acabar� como mucho en 0:5, si no hay soluci�n v�lida en 0:5, es decir, si no hay jugador
	en 0:5, no hay posibilidad de llegar a �l en esta rama, por lo cual la descartaremos. La 
	descartamos al tener ya todas las ramas, pero en cuanto a la recursividad esto ser�a un caso
	base. Hemos llegado m�s all� de la visi�n que tenemos, este nodo no se a�ade y por lo tanto
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
		6 [ ][ ][�][�][!][ ][ ][ ][ ][ ]
		7 [ ][�][�][ ][ ][ ][ ][ ][ ][ ]
		8 [�][�][ ][ ][ ][ ][ ][ ][ ][ ]
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
				- No genero m�s rutas
		3.- Si no tengo ruta generada y no veo al jugador
			- Patrullo aleatoriamente
			o
			- Me quedo quieto que se est� c�modo


	A -> B 
			-> C  -> F   
			-> D           -> H
	  -> E  -> D  -> O 

	B 64% <-- % adicional o negativo en base a la cantidad feromona
	E 36% <--

	A > B > D > O > H > O > D > B > A
*/
