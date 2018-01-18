#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
//#include <windows.h>
//#include "Auxiliar.h"
//#include "Constantes.h"
#include "Juego.h"
//#include "Nodo.h"
//#include "Mapa.h"
//#include "Objeto.h"
//#include "Personaje.h"
//#include "Atacar.h"
//#include "Estado.h"
//#include "Patrullar.h"

int main (int argc, char *argv[]) {

	srand(time(NULL));
	//std::random_device r;
	rlutil::hidecursor();
	ElJuego::Get_Instancia()->Actualiza_Estado();
	
	/*rol.Crear_Objetos();
	rol.Actualizar_Estado();
	while(!rol.Get_Salir())
	{
		rol.Jugar();
	}
	rlutil::showcursor();*/

	return 0;
}


