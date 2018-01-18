#include"Atacar.h"
#include"NPC.h"
#include"Patrullar.h"

Patrullar* Patrullar::Instancia()
{
	static Patrullar instancia;
	return &instancia;
}

void Patrullar::Entra(NPC* npc){ std::cout << "\n Entrando a patrullar;"; }
void Patrullar::Realiza(NPC* npc)
{
	npc->Set_X(5);
	if(npc->Get_X() > 10)
		npc->Actualiza_Estado();
}
void Patrullar::Sale(NPC* npc){ std::cout << "\n Saliendo de patrullar\n"; }
