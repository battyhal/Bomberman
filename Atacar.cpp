#include"Atacar.h"
#include"NPC.h"
#include"Patrullar.h""

Atacar* Atacar::Instancia()
{
	static Atacar instancia;
	return &instancia;
}

void Atacar::Entra(NPC* npc){ std::cout << "\n Entrando a atacar;"; }
void Atacar::Realiza(NPC* npc)
{
	npc->Set_Y(5);
	if(npc->Get_Y() > 10)
		npc->Actualiza_Estado();
}
void Atacar::Sale(NPC* npc){ std::cout << "\n Saliendo de atacar\n"; }
