#include "Juego.h"

Juego::Juego():bomba(NULL), Bomberman(NULL), mapa(Mapa()), salir(false), turnos(0)
{
	//mapa.Dibujar_Marco();
}

Juego::Juego(std::string nivelTxt):bomba(NULL), Bomberman(NULL), mapa(Mapa(nivelTxt)), 
									 salir(false), turnos(0) {}

Juego& Juego::operator=(const Juego& otro)
{
	if(this != &otro)
	{
		bomba = otro.bomba;
		Bomberman = otro.Bomberman;
		mapa = otro.mapa;
		objetos = otro.objetos;
		salir = otro.salir;
		turnos = otro.turnos;
	}
	return *this;
}

Juego::~Juego() 
{
	Bomberman = NULL;
	delete Bomberman;
	bomba = NULL;
	delete bomba;
}

// ---------------------------------------------------------------
// GETTERS
// ---------------------------------------------------------------
bool Juego::Get_Salir() const { return salir; }
std::list<Objeto*> Juego::Get_Objetos() const { return objetos; }

// ---------------------------------------------------------------
// MÉTODOS
// ---------------------------------------------------------------
void Juego::Actualizar()
{
	// Si hay una bomba se comprueba el tiempo de vida
	/*if(bomba)
	{
		bomba->Cuenta_Atras();
	}*/
	// Comprobar colisiones del jugador con Bombas y/o enemigos
	for(auto Obj = objetos.begin(); Obj != objetos.end(); Obj++)
	{
		for(auto Obj2 = Obj; Obj2 != objetos.end(); Obj2++)
		{			
			// Si hay 2 objetos en la misma posición
			if((*Obj)->Get_X() == (*Obj2)->Get_X() && (*Obj)->Get_Y() == (*Obj2)->Get_Y())
			{
				// Si tienen el mismo nombre no se hace nada
				if((*Obj)->Get_Nombre() == (*Obj2)->Get_Nombre())
					continue;
				// Si no : se le quita 1 vida al objeto que sea
				(*Obj)->Set_Vidas(-1);
				(*Obj2)->Set_Vidas(-1);
			}
			// Comprobar si los objetos están vivos (menos Bomberman) y si no lo están borrarlos
			if((*Obj)->Get_Nombre() != "Bomberman")
			{
				if((*Obj)->Get_Vidas() == 0)
				{
					delete(*Obj);
					Obj = objetos.erase(Obj);
					Bomberman->Set_Puntos(10);
				}
			}
			if((*Obj2)->Get_Nombre() != "Bomberman")
			{
				if((*Obj2)->Get_Vidas() == 0)
				{
					delete(*Obj2);
					Obj2 = objetos.erase(Obj2);
					Bomberman->Set_Puntos(10);
				}
			}
		}
	}	
}

void Juego::Crear_Objetos()
{
	// Personaje Jugador
	Bomberman = new Personaje(10, 10, 50, "Bomberman", 'B', 13, 2, 3, 0, "Bomba pequeña");
	objetos.push_back(Bomberman);
	
	// NPC´s
	for(int i = 1; i < 3; i++)
	{
		switch(i)
		{
		case 1:
		{
			NPC* orco1 = new NPC(12, 7, 60, "Orco", 'O', 1, 6, 6, 0, " ");
			objetos.push_back(orco1);
		}
		break;
		case 2:
		{
			NPC* orco2 = new NPC(12, 7, 60, "Orco", 'O', 1, 10, 10, 0, " ");
			objetos.push_back(orco2);
		}
		break;
		}// Fin switch(i)
	}
}

void Juego::Game_Over()
{
	char gameOver[13][35] = {
			"     .--,       .--,         ",
			"    ( (  \\.---./  ) )        ",
			"     '.__/o   o\\__.'         ",
			"        {=  ^  =}            ",
			"         >  -  <             ",
			"        /       \\            ",
			"       //       \\\\           ",
			"      //|   .   |\\\\          ",
			"      \"'\\       /'\"_.-~^`'-. ",
			"         \\  _  /--'         `",
			"       ___)( )(___           ",
			"      (((__) (__)))          ",
	};
	for(int j = 0; j < 13; j++)
	{
		for(int k = 0; k < 35; k++)
		{
			std::cout << gameOver[j][k];
		}
		std::cout << "\n";
	}
}

void Juego::Jugar()
{
	Auxiliar auxiliar;
	auxiliar.lista_objetos_auxiliar = objetos;
	auxiliar.mapa_auxiliar = mapa.Get_Matriz_Fija();
	rlutil::hidecursor();
	Puntuacion();
	if(Bomberman->Get_Vidas() == 0)
	{
		mapa.Dibujar_Jugador_Muerto();
		salir = true;
	}
	else
	{
		Mover_Personaje();
		Mover_NPC();
		Actualizar();
		auxiliar.Dibujar_Mapa();
		
		Sleep(150);
	}
}

void Juego::Mover_NPC()
{
	// Se empieza por el objeto[1] porque el objeto[0] es el jugador
	for(auto Obj = objetos.begin(); Obj != objetos.end(); Obj++)
	{	
		// Comprobar que el objeto no es una bomba
		if((*Obj)->Get_Tag() != '@' && (*Obj)->Get_Tag() != 'B')
		{
			(*Obj)->Mover(6, mapa, Bomberman->Get_X(), Bomberman->Get_Y()); 
				
			if((*Obj)->Get_X() <= 0)
				(*Obj)->Set_X(2);
			if((*Obj)->Get_X() > mapa.Get_Ancho_Mapa() - 1)
				(*Obj)->Set_X(mapa.Get_Ancho_Mapa() - 2);
			if((*Obj)->Get_Y() <= 0)
				(*Obj)->Set_Y(2);
			if((*Obj)->Get_Y() > mapa.Get_Alto_Mapa() - 1)
				(*Obj)->Set_Y(mapa.Get_Alto_Mapa() - 2);
		}
	}
}

void Juego::Mover_Personaje()
{
	/*Funciones::Goto_XY(47 , 4);
	std::cout << "** MOVER **\n ";
	std::cout << "ARRIBA    : CURSOR ARRIBA\n ";
	std::cout << "ABAJO     : CURSOR ABAJO\n ";
	std::cout << "IZQUIERDA : CURSOR IZQUIERDA\n ";
	std::cout << "DERECHA   : CURSOR DERECHA\n ";*/
	char tecla = ' ';
	if(kbhit())
	{
		tecla = rlutil::getkey();
		switch(tecla)
		{
		case rlutil::KEY_DOWN:
		{
			// Comprobar si la casilla a la que queremos ir está dentro del mapa
			if(Bomberman->Get_Y() + 1 < mapa.Get_Alto_Mapa())
			{
				// Mover personaje
				Bomberman->Mover(2, mapa, 0, 0);
				
				// PARA HACER : PROCEDIMIENTO SI EN LA CASILLA A LA QUE SE MUEVE HAY UN NPC
			}
		}
		break;
		case rlutil::KEY_UP:
		{
			// Comprobar si la casilla a la que queremos ir está dentro del mapa
			if(Bomberman->Get_Y() - 1 >= 0)
			{
				// Mover personaje
				Bomberman->Mover(1, mapa, 0, 0);
				
				// PARA HACER : PROCEDIMIENTO SI EN LA CASILLA A LA QUE SE MUEVE HAY UN NPC
			}
		}
		break;
		case rlutil::KEY_LEFT:
		{
			// Comprobar si la casilla a la que queremos ir está dentro del mapa
			if(Bomberman->Get_X() - 1 >= 0)
			{			
				// Mover personaje
				Bomberman->Mover(3, mapa, 0, 0);
				
				// PARA HACER : PROCEDIMIENTO SI EN LA CASILLA A LA QUE SE MUEVE HAY UN NPC
			}
		}
		break;
		case rlutil::KEY_RIGHT:
		{
			// Comprobar si la casilla a la que queremos ir está dentro del mapa
			if(Bomberman->Get_X() + 1 < mapa.Get_Ancho_Mapa())
			{
				// Mover personaje
				Bomberman->Mover(4, mapa, 0, 0);
				// PARA HACER : PROCEDIMIENTO SI EN LA CASILLA A LA QUE SE MUEVE HAY UN NPC
			}
		}
		break;
		case rlutil::KEY_SPACE:
		{
			bomba = new Bomba(1, 0, 1, "Bomba", '@', 10, Bomberman->Get_X(),
							  Bomberman->Get_Y(), 1, 3);
			objetos.push_back(bomba); 
		}
		break;
		case rlutil::KEY_ESCAPE:
		{
			salir = true;
		}
		break;
		default:
		{
			gotoxy(Bomberman->Get_X(), Bomberman->Get_Y());
			std::cout << " ERROR ";
		}
		break;
		} // Fin switch(tecla)
		//Mover_NPC();
		
		turnos++;
	}
}

void Juego::Presentacion()
{
	char mouse_pic[13][35] = {
	"     .--,       .--,         ",
	"    ( (  \\.---./  ) )        ",
	"     '.__/o   o\\__.'         ",
	"        {=  ^  =}            ",
	"         >  -  <             ",
	"        /       \\            ",
	"       //       \\\\           ",
	"      //|   .   |\\\\          ",
	"      \"'\\       /'\"_.-~^`'-. ",
	"         \\  _  /--'         `",
	"       ___)( )(___           ",
	"      (((__) (__)))          ",
	};
	for(int j = 0; j < 13; j++)
	{
		for(int k = 0; k < 35; k++)
		{
			std::cout << mouse_pic[j][k];
		}
		std::cout << "\n";
	}
}

void Juego::Puntuacion()
{
	gotoxy(7, 4);
	std::cout << "PUNTOS = " << Bomberman->Get_Puntos();
	gotoxy(7, 5);
	std::cout << "VIDAS  = " << Bomberman->Get_Vidas();
	gotoxy(7, 6);
	std::cout << "Turnos = " << turnos;
}

