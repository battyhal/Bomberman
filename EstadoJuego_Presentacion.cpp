#include "EstadoJuego_Menu.h"
#include "EstadoJuego_Presentacion.h"
#include "Juego.h"

const std::string EstadoJuego_Presentacion::presentacion_ID = "PRESENTACION";
// =======================================================================================
// GETTERS
// =======================================================================================
std::string EstadoJuego_Presentacion::Get_ID() const{ return presentacion_ID; }
EstadoJuego_Presentacion* EstadoJuego_Presentacion::Get_Instancia()
{
	static EstadoJuego_Presentacion instancia;
	return &instancia;
}

// =======================================================================================
// MÉTODOS
// =======================================================================================
bool EstadoJuego_Presentacion::Entra(){ return true; }
void EstadoJuego_Presentacion::Realiza()
{	
	gotoxy(50, 8);
	std::cout << " Ik PRESENTA.....\n ";
	char bomberman[9][81] = 
	{
	"                                                                                ",
	"######   #######  #     #  ######   #######  ######   #     #     #     #     # ",
	"#     #  #     #  ##   ##  #     #  #        #     #  ##   ##    # #    ##    # ",
	"#     #  #     #  # # # #  #     #  #        #     #  # # # #   #   #   # #   # ",
	"######   #     #  #  #  #  ######   #####    ######   #  #  #  #     #  #  #  # ",
	"#     #  #     #  #     #  #     #  #        #   #    #     #  #######  #   # # ",
	"#     #  #     #  #     #  #     #  #        #    #   #     #  #     #  #    ## ",
	"######   #######  #     #  ######   #######  #     #  #     #  #     #  #     # ",
	"                                                                                ",	
	};
	int max = 15;
	int min = 0;
	int aleatorio = 0;
	bool salir = false;
	char tecla = ' ';
	gotoxy(20, 10);
	while(!salir)
	{
		rlutil::resetColor();
		if(kbhit())
		{
			tecla = rlutil::getkey();
			switch(tecla)
			{
			case rlutil::KEY_SPACE:
				salir = true;
			break;
			}
		}
		for(int j = 0; j < 9; j++)
		{
			aleatorio = rand() % (max - min) + min;
			if(aleatorio == 11)	
				rlutil::setColor(rlutil::LIGHTRED);
			else if(aleatorio == 12)	
				rlutil::setColor(rlutil::LIGHTMAGENTA);
			else if(aleatorio == 13)	
				rlutil::setColor(rlutil::YELLOW);
			else if(aleatorio == 14)	
				rlutil::setColor(rlutil::WHITE);
			for(int k = 0; k < 81; k++)
			{
				aleatorio = rand() % (max - min) + min + 1;
				if(aleatorio == 0)		
					rlutil::setColor(rlutil::BLUE);
				else if(aleatorio == 1)		 
					rlutil::setColor(rlutil::GREEN);
				else if(aleatorio == 2)			
					rlutil::setColor(rlutil::CYAN);
				else if(aleatorio == 3)			
					rlutil::setColor(rlutil::RED);
				else if(aleatorio == 4)			
					rlutil::setColor(rlutil::MAGENTA);
				else if(aleatorio == 5)			
					rlutil::setColor(rlutil::BROWN);
				else if(aleatorio == 6)			
					rlutil::setColor(rlutil::GREY);
				else if(aleatorio == 7)			
					rlutil::setColor(rlutil::DARKGREY);
				else if(aleatorio == 8)	
					rlutil::setColor(rlutil::LIGHTBLUE);
				else if(aleatorio == 9)	
					rlutil::setColor(rlutil::LIGHTGREEN);
				else if(aleatorio == 10)	
					rlutil::setColor(rlutil::LIGHTCYAN);
				else if(aleatorio == 11)	
					rlutil::setColor(rlutil::LIGHTRED);
				else if(aleatorio == 12)	
					rlutil::setColor(rlutil::LIGHTMAGENTA);
				else if(aleatorio == 13)	
					rlutil::setColor(rlutil::YELLOW);
				else if(aleatorio == 14)	
					rlutil::setColor(rlutil::WHITE);
				std::cout << bomberman[j][k];
			}
			rlutil::msleep(25);
			gotoxy(20, j + 11);
		}
		gotoxy(70, 20);
		std::cout << " Presiona ESPACIO para continuar...";
	}
	rlutil::cls();
	Sale();
	Juego::Get_Instancia()->Cambia_Estado(EstadoJuego_Menu::Get_Instancia());
	Juego::Get_Instancia()->Actualiza_Estado();	
}
	
bool EstadoJuego_Presentacion::Sale(){ return true; }

