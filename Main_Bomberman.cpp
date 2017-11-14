#include <ctime>
#include <fstream>
#include <iostream>
#include <windows.h>
#include "Constantes.h"
#include "Juego.h"

using namespace std;

int main (int argc, char *argv[]) {
	
	srand(time(NULL));
	std::random_device r;
	Juego rol;//("Columnas.txt");
	rol.Crear_Objetos();
	
	while(!rol.Get_Salir())
	{
		rol.Jugar();
	}
	rlutil::showcursor();
	
	return 0;
}


