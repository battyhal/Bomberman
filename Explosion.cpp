#include "Explosion.h"

Explosion* Explosion::Get_Instancia()
{
	static Explosion instancia;
	return& instancia;
}

void Explosion::Entra(Bomba*){ std::cout << " Entrando en Explosion"; }
void Explosion::Realiza(Bomba* b)
{
	std::cout << " BOMBA VA !\n";
}
void Explosion::Sale(Bomba*){ std::cout << " Saliendo de Explosion"; }

