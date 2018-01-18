#include "Auxiliar.h"

Auxiliar::Auxiliar():listaObjetosAuxiliar_(0), mapaAuxiliar_(nullptr){}
Auxiliar::Auxiliar(std::list<Objeto*>& l, Mapa& m)
:listaObjetosAuxiliar_(l), mapaAuxiliar_(m.Get_Matriz()){}
Auxiliar::~Auxiliar(){}

// =======================================================================
// MÉTODOS
// =======================================================================
void Auxiliar::Dibujar_Mapa()
{
	// Dibujar contenido matriz fija
	gotoxy(25, 10);
	for(int j = 0; j < ANCHO; j++)
	{
		rlutil::resetColor();
		//std::cout << " " << j << " ";
		for(int k = 0; k < ALTO; k++)
		{
			bool dibujado = false;
			//std::cout << k;
			for(auto it = listaObjetosAuxiliar_.begin(); !dibujado && 
				it != listaObjetosAuxiliar_.end(); it++)
			{
				if((*it)->Get_X() == k && (*it)->Get_Y() == j)
				{
                    int tono = (*it)->Get_Tono();
                    switch(tono)
                    {
                    case 1: // Marrón
                    {
                        rlutil::setColor(rlutil::BROWN);
                    }
                    break;
                    case 2: // Verde
                    {
                        rlutil::setColor(rlutil::GREEN);
                    }
                    break;
                    case 3: // Blanco
                    {
                        rlutil::setColor(rlutil::WHITE);
                    }
                    break;
                    }
                    std::cout << (*it)->Get_Tag();
                    dibujado = true;
				}
			}
			if(!dibujado)
			{
				char cont = mapaAuxiliar_[j * ALTO + k]->Get_Contenido();
				switch(cont)
				{
                case Adobe:
                {
                    rlutil::setColor(rlutil::GREY);
                }
                break;
				}
                std::cout << mapaAuxiliar_[j * ALTO + k]->Get_Contenido();
			}
		}
		gotoxy(25, j + 11);
	}
}

