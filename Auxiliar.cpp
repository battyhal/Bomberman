#include "Auxiliar.h"

Auxiliar::Auxiliar():lista_objetos_auxiliar(0), mapa_auxiliar(nullptr) {}
Auxiliar::~Auxiliar() {}
// ---------------------------------------------------------------
// GETTERS 
// ---------------------------------------------------------------

// ---------------------------------------------------------------
// SETTERS
// ---------------------------------------------------------------

// ---------------------------------------------------------------
// MÉTODOS
// ---------------------------------------------------------------
void Auxiliar::Dibujar_Mapa()
{
	// Dibujar contenido matriz fija
	gotoxy(20, 3);
	for(int j = 0; j < ANCHO; j++)
	{
		for(int k = 0; k < ALTO; k++)
		{
			bool dibujado = false;
			for(auto it = lista_objetos_auxiliar.begin(); !dibujado && it != lista_objetos_auxiliar.end(); it++)
			{
				if((*it)->Get_X() == k && (*it)->Get_Y() == j)
				{
					// Si hay una bomba dibuja siempre la bomba 
					if((*it)->Get_Nombre() == "Bomba")
						std::cout << '@';
					else std::cout << (*it)->Get_Tag();
					dibujado = true;
				}
			}
			if(!dibujado)
			{
				std::cout << mapa_auxiliar[j * ALTO + k].Get_Contenido();						
			}
		}
		gotoxy(20, j + 4);
	}		
}

