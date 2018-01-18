#ifndef NPC_H
#define NPC_H

#include <cassert>
#include <iostream>
#include <vector>
#include "Maquina_Estados_Objetos.h"
#include "Objeto.h"

class NPC : public Objeto 
{
private:
		std::vector<std::string> equipo_;
		Maquina_Estados_Objetos<NPC>* fsmEstados_;

protected:
public:
		NPC();
		NPC(int, int, int, std::string, char, std::string, int, int, int, int, std::string);
		~NPC();
	
	// ===================================================================================
	// GETTERS
	// ===================================================================================
		Maquina_Estados_Objetos<NPC>* Get_Maquina_Estados()const;
	
	// ===================================================================================
	// MÉTODOS
	// ===================================================================================
		virtual void Actualiza_Estado(); 
		virtual bool Gestiona_Mensaje(const Mensaje&);
		
};

#endif

