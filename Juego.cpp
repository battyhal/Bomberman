#include "EstadoJuego_Menu.h"
#include "EstadoJuego_Presentacion.h"
#include "EstadoJuego_Pausa.h"
#include "EstadoJuego_GameOver.h"
#include "Juego.h"

Juego::Juego():bomba_(NULL), Bomberman_(NULL),
estadoActual_(Presentacion::Get_Instancia()), mapa_(Mapa::Instancia()),
maquinaEstados_(new Maquina_Estados_Juego), salir_(false), turnos_(0)
{
	maquinaEstados_->Incluir_Estado(Presentacion::Get_Instancia());
}

Juego::Juego(std::string nivelTxt):bomba_(NULL), Bomberman_(NULL),
estadoActual_(Presentacion::Get_Instancia()), mapa_(Mapa::Instancia()),
maquinaEstados_(NULL), salir_(false), turnos_(0){}

Juego& Juego::operator=(const Juego& otro)
{
	if(this != &otro)
	{
		bomba_ = otro.bomba_;
		Bomberman_ = otro.Bomberman_;
		estadoActual_ = Presentacion::Get_Instancia();
		mapa_ = Mapa::Instancia();
		maquinaEstados_ = otro.maquinaEstados_;
		objetos_ = otro.objetos_;
		salir_ = otro.salir_;
		turnos_ = otro.turnos_;
	}
	return *this;
}

Juego::~Juego()
{
	Bomberman_ = NULL;
	delete Bomberman_;
	bomba_ = NULL;
	delete bomba_;
	estadoActual_ = NULL;
	delete estadoActual_;
	mapa_ = NULL;
	delete mapa_;
	maquinaEstados_ = NULL;
	delete maquinaEstados_;
}

// =======================================================================================
// GETTERS
// =======================================================================================
Juego* Juego::Get_Instancia()
{
	static Juego instancia;
	return& instancia;
}
Maquina_Estados_Juego* Juego::Get_Maquina_Estados(){ return maquinaEstados_; }
bool Juego::Get_Salir() const { return salir_; }
std::list<Objeto*> Juego::Get_Objetos() const { return objetos_; }

// =======================================================================================
// MÉTODOS
// =======================================================================================
void Juego::Actualiza()
{
	// Comprobar colisiones del jugador con Bombas y/o enemigos si hay + de 1 elemento
	if(objetos_.size() > 1)
	{
		for (auto Obj = objetos_.begin(); Obj != objetos_.end(); Obj++)
		{
			for (auto Obj2 = Obj; Obj2 != objetos_.end(); Obj2++)
			{
				//(*Obj)->Actualiza_Estado();
				//(*Obj2)->Actualiza_Estado();
				// Si hay 2 objetos en la misma posición
				if ((*Obj)->Get_X() == (*Obj2)->Get_X() && (*Obj)->Get_Y() == (*Obj2)->Get_Y())
				{
					// Si entra en un portal
					if ((*Obj)->Get_X() == mapa_->Get_Portales(0, 'x') &&
						(*Obj)->Get_Y() == mapa_->Get_Portales(0, 'y'))
					{
						// Aparece al lado del portal
						(*Obj)->Set_X(mapa_->Get_Portales(1, 'x') + 1);
						(*Obj)->Set_Y(mapa_->Get_Portales(1, 'y'));
					}
					else if ((*Obj)->Get_X() == mapa_->Get_Portales(1, 'x') &&
						(*Obj)->Get_Y() == mapa_->Get_Portales(1, 'y'))
					{
						// Aparece al lado del portal
						(*Obj)->Set_X(mapa_->Get_Portales(0, 'x') + 1);
						(*Obj)->Set_Y(mapa_->Get_Portales(0, 'y'));
					}

					// Si tienen el mismo nombre no se hace nada
					if ((*Obj)->Get_Nombre() == (*Obj2)->Get_Nombre())
						continue;
					// Si no : se le quita 1 vida al objeto que sea
					(*Obj)->Set_Vidas(-1);
					(*Obj2)->Set_Vidas(-1);
				}
				// Si los objetos no están vivos (menos Bomberman_) se borran
				if ((*Obj)->Get_Nombre() != "Bomberman_")
				{
					if ((*Obj)->Get_Vidas() == 0)
					{
						delete(*Obj);
						Obj = objetos_.erase(Obj);
						Bomberman_->Set_Puntos(10);
					}
					//else Obj++;
				}
				if ((*Obj2)->Get_Nombre() != "Bomberman_")
				{
					if ((*Obj2)->Get_Vidas() == 0)
					{
						delete(*Obj2);
						Obj2 = objetos_.erase(Obj2);
						Bomberman_->Set_Puntos(10);
					}
					//else Obj2++;
				}
			}
		}
	}
}

void Juego::Actualiza_Estado()
{
	maquinaEstados_->Actualizar();
}

void Juego::Cambia_Estado(EstadoJuego* nuevoEstado)
{
	maquinaEstados_->Cambiar_Estado(nuevoEstado);
}

void Juego::Elimina_Estado(EstadoJuego* estado)
{
	maquinaEstados_->Eliminar_Estado(estado);
}

void Juego::Incluye_Estado(EstadoJuego* estado)
{
	maquinaEstados_->Incluir_Estado(estado);
}

void Juego::Crea_Objetos()
{
	// Personaje Jugador
	Bomberman_ = new Personaje(10, 10, 50, "Bomberman", 'B', "blanco", 13,
							  3, 2, 0, "Bomba pequeña");
	objetos_.push_back(Bomberman_);

	// NPC´s
	NPC* orco1 = new NPC(12, 7, 60, "Orco", 'O', "marron", 1, 10, 11, 0, " ");
	objetos_.push_back(orco1);
	NPC* orco2 = new NPC(12, 7, 60, "Orco", 'O', "marron", 1, 12, 13, 0, " ");
	objetos_.push_back(orco2);
	NPC* orco3 = new NPC(12, 7, 60, "Orco", 'O', "marron", 1, 8, 10, 0, " ");
    objetos_.push_back(orco3);
	/*for(int i = 1; i < 3; i++)
	{
		switch(i)
		{
		case 1:
		{
			NPC* orco1 = new NPC(12, 7, 60, "Orco", 'O', "marron", 1, 16,
								 16, 0, " ");
			objetos.push_back(orco1);
		}
		break;
		case 2:
		{
			NPC* orco2 = new NPC(12, 7, 60, "Orco", 'O', "marron", 1, 10,
								 16, 0, " ");
			objetos.push_back(orco2);
		}
		break;
		}// Fin switch(i)
	}*/
}

void Juego::Fondo_Bomberman()
{
	gotoxy(10, 5);
	char fondo[][46] = {
	" ********************************************",
	" *                                          *",
	" * B    O    M    B    E    R    M    A   N *",
	" *                                          *",
	" ********************************************",
	};
	for(int j = 0; j < 5; j++)
	{
		for(int k = 0; k < 46; k++)
		{
			std::cout << fondo[j][k];
		}
		gotoxy(10, j + 6);
	}
}

void Juego::Game_Over()
{
	char gameOver[13][35] =
	{
	"     .--,       .--,            ",
	"    ( (  \\.---./  ) )          ",
	"     '.__/o   o\\__.'           ",
	"        {=  ^  =}               ",
	"         >  -  <                ",
	"        /       \\              ",
	"       //       \\\\            ",
	"      //|   .   |\\\\           ",
	"     \"'\\      /'\"_.-~^`'-.   ",
	"         \\  _ /--'         `   ",
	"       ___)( )(___              ",
	"      (((__) (__)))             ",
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
	auxiliar.listaObjetosAuxiliar_ = objetos_;
	auxiliar.mapaAuxiliar_ = mapa_->Get_Matriz();
	Fondo_Bomberman();
	Puntuacion();
	if(Bomberman_->Get_Vidas() == 0)
	{
		Cambia_Estado(EstadoJuego_GameOver::Get_Instancia());
		Actualiza_Estado();
		salir_ = true;
	}
	else
	{
		Mueve_Personaje();
		Mueve_NPC();
		Actualiza();
		auxiliar.Dibujar_Mapa();
		Sleep(150);
	}
}

void Juego::Mueve_NPC()
{
	for(auto Obj = objetos_.begin(); Obj != objetos_.end(); Obj++)
	{
		// No mover ni a Bomberman_ ni a las bombas
		if((*Obj)->Get_Tag() != '@' && (*Obj)->Get_Tag() != 'B')
		{
			// Perseguir al personaje
			(*Obj)->Busca_Caminos(Bomberman_->Get_X(), Bomberman_->Get_Y());
			if((*Obj)->Get_X() <= 0)
				(*Obj)->Set_X(2);
			if((*Obj)->Get_X() > mapa_->Get_Ancho_Mapa() - 2)
				(*Obj)->Set_X(mapa_->Get_Ancho_Mapa() - 3);
			if((*Obj)->Get_Y() <= 0)
				(*Obj)->Set_Y(2);
			if((*Obj)->Get_Y() > mapa_->Get_Alto_Mapa() - 2)
				(*Obj)->Set_Y(mapa_->Get_Alto_Mapa() - 3);
		}
	}
}

void Juego::Mueve_Personaje()
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
			Bomberman_->Mueve(1, Bomberman_->Get_X(), Bomberman_->Get_Y());
		}
		break;
		case rlutil::KEY_UP:
		{
			Bomberman_->Mueve(2, Bomberman_->Get_X(), Bomberman_->Get_Y());
		}
		break;
		case rlutil::KEY_RIGHT:
		{
			Bomberman_->Mueve(3, Bomberman_->Get_X(), Bomberman_->Get_Y());
		}
		break;
		case rlutil::KEY_LEFT:
		{
			Bomberman_->Mueve(4, Bomberman_->Get_X(), Bomberman_->Get_Y());
		}
		break;
		case rlutil::KEY_SPACE:
		{
			bomba_ = new Bomba(1, 0, 1, "Bomba", '@', "verde", 10,
							  Bomberman_->Get_X(), Bomberman_->Get_Y(), 1, 3);
			objetos_.push_back(bomba_);
		}
		break;
		case rlutil::KEY_ESCAPE:
		{
			salir_ = true;
		}
		break;
		case rlutil::KEY_DELETE:
		{
			Incluye_Estado(EstadoJuego_Pausa::Get_Instancia());
			Actualiza_Estado();
			system("pause");
		}
		break;
		default:
		{
			gotoxy(Bomberman_->Get_X(), Bomberman_->Get_Y());
			std::cout << " ERROR ";
		}
		break;
		} // Fin switch(tecla)
		turnos_++;
	}
}

void Juego::Puntuacion()
{
	gotoxy(10, 12);
	std::cout << "            ";
	gotoxy(10, 13);
	std::cout << " PUNTOS =  " << Bomberman_->Get_Puntos();
	gotoxy(10, 14);
	std::cout << " VIDAS  =  " << Bomberman_->Get_Vidas();
	gotoxy(10, 15);
	std::cout << " Turnos =  " << turnos_;
	gotoxy(10, 16);
	std::cout << "            ";
}

