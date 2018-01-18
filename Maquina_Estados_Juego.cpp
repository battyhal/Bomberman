#include "Maquina_Estados_Juego.h"

void Maquina_Estados_Juego::Actualizar()
{
	if(!estadosJuego_.empty())
	{
		estadosJuego_.back()->Realiza();
	}
}
void Maquina_Estados_Juego::Cambiar_Estado(EstadoJuego* estado)
{
	if(!estadosJuego_.empty())
	{
		if(estadosJuego_.back()->Get_ID() == estado->Get_ID())
		{
			return;
		}
		if(estadosJuego_.back()->Sale())
		{
			//delete estadosJuego_.back();
			estadosJuego_.pop_back();
		}
		estadosJuego_.push_back(estado);
		estadosJuego_.back()->Entra();
	}
}
void Maquina_Estados_Juego::Eliminar_Estado(EstadoJuego* estado)
{
	if(!estadosJuego_.empty())
	{
		if(estadosJuego_.back()->Sale())
		{
			delete estadosJuego_.back();
			estadosJuego_.pop_back();
		}
	}
}
void Maquina_Estados_Juego::Incluir_Estado(EstadoJuego* estado)
{
	estadosJuego_.push_back(estado);
	estadosJuego_.back()->Entra();
}

