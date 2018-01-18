#include "EstadoJuego_Pausa.h"

const std::string EstadoJuego_Pausa::pausa_ID = "PAUSA";
// ===============================================================
// GETTERS
// ===============================================================
std::string EstadoJuego_Pausa::Get_ID() const{ return pausa_ID; }
EstadoJuego_Pausa* EstadoJuego_Pausa::Get_Instancia()
{
	static EstadoJuego_Pausa instancia;
	return &instancia;
}

// ===============================================================
// MÉTODOS
// ===============================================================
bool EstadoJuego_Pausa::Entra(){ return true; }
void EstadoJuego_Pausa::Realiza()
{
	gotoxy(25 ,11);
	std::cout << "*********************";
	gotoxy(25 ,12);
	std::cout << "*                   *";
	gotoxy(25 ,13);
	std::cout << "*      PAUSA        *";
	gotoxy(25 ,14);
	std::cout << "*                   *";
	gotoxy(25 ,15);
	std::cout << "*********************";
	gotoxy(25 ,16);
}
bool EstadoJuego_Pausa::Sale(){ return true; }
