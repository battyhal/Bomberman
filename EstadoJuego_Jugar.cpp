#include "EstadoJuego_Jugar.h"
#include "EstadoJuego_Pausa.h"
#include "Juego.h"

const std::string EstadoJuego_Jugar::jugar_ID = "JUGAR";
// ===============================================================
// GETTERS
// ===============================================================
std::string EstadoJuego_Jugar::Get_ID() const{ return jugar_ID; }
EstadoJuego_Jugar* EstadoJuego_Jugar::Get_Instancia()
{
	static EstadoJuego_Jugar instancia;
	return &instancia;
}

// ===============================================================
// MÉTODOS
// ===============================================================
bool EstadoJuego_Jugar::Entra(){ return true; }
void EstadoJuego_Jugar::Realiza()
{
	rlutil::cls();
	Juego::Get_Instancia()->Crea_Objetos();
	while(!Juego::Get_Instancia()->Get_Salir())
	{
		Juego::Get_Instancia()->Jugar();
	}
}
bool EstadoJuego_Jugar::Sale(){ return true; };
