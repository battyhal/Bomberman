#include"Atacar.h"
#include"NPC.h"
#include"Patrullar.h"

NPC::NPC():Objeto(){}

NPC::NPC(int _ataque, int _defensa, int _energia, std::string _nombre,
char _tag, std::string _tono, int _vidas, int _x, int _y, int _puntos, 
std::string _equipo):
Objeto(_ataque, _defensa, _energia, _nombre, _tag, _tono, _vidas, _x, _y)
{
	fsmEstados_ = new Maquina_Estados_Objetos<NPC>(this);
	fsmEstados_->Set_Estado_Actual(Patrullar::Instancia());
	equipo_.push_back(_equipo);
}
 
NPC::~NPC() { delete fsmEstados_; }

// ===================================================================================
// GETTERS
// ===================================================================================
Maquina_Estados_Objetos<NPC>* NPC::Get_Maquina_Estados()const { return fsmEstados_; }

// ===================================================================================
// MÉTODOS
// ===================================================================================
void NPC::Actualiza_Estado()
{
	energia_++;
	fsmEstados_->Actualiza();
}

bool NPC::Gestiona_Mensaje(const Mensaje& msg)
{
	return fsmEstados_->Gestiona_Mensaje(msg);
}
