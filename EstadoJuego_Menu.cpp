#include "EstadoJuego_Menu.h"
#include "EstadoJuego_Jugar.h"
#include "Juego.h"

const std::string EstadoJuego_Menu::menu_ID = "MENU";

// =======================================================================================
// GETTERS
// =======================================================================================
std::string EstadoJuego_Menu::Get_ID() const{ return menu_ID; }
EstadoJuego_Menu* EstadoJuego_Menu::Get_Instancia()
{
	static EstadoJuego_Menu instancia;
	return &instancia;
}

// =======================================================================================
// MÉTODOS
// =======================================================================================
bool EstadoJuego_Menu::Entra(){ return true; }
void EstadoJuego_Menu::Realiza()
{
	gotoxy(30 ,6);
	char menu[13][43] = 
	{
	"                       ----------------   ",
	"                      < MENU BOMBERMAN >  ",
	"                       ----------------   ",
	"                        *  /    		   ",
	"                      __|_/   			   ",
	"                     (==) )               ",  
	" 1- Juego Nuevo       |== |     		   ",
	" 2- Cargar Juego     /---- | 			   ",
	" 3- Guardar Juego   o)Me (o))  		   ",
	" 4- Salir            |_____|  			   ",
	"                     /__/__|   		   ",  
	"                    (==(OOOO)  		   ",
	"  							    		   ",
	};
	for(int i = 0; i < 13; i++)
	{
		for(int j = 0; j < 43; j++)
		{
			std::cout << menu[i][j];
		}
		gotoxy(30, i + 6);
	}
	std::cout << " OPCION : ";
	char opcion = ' ';
	std::cin >>  opcion;
	switch(opcion)
	{
	case '1':
	{
		Juego::Get_Instancia()->Cambia_Estado(EstadoJuego_Jugar::Get_Instancia());
		Juego::Get_Instancia()->Actualiza_Estado();
	}	
	break;
	case '2':
	{
		std::cout << " En construccion...\n";
	}
	break;
	case '3':
	{
		std::cout << " En construccion...\n";
	}
	break;
	case '4':
	{
		//Juego::Get_Instancia()->EstadoJuego_GameOver::Get_Instancia();
	}
	break;
	default:
	{
		std::cout << " Opcion Incorrecta\n";
	}
	break;
	}
}
bool EstadoJuego_Menu::Sale(){ return true; };
