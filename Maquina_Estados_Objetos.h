#ifndef MAQUINA_ESTADOS_OBJETOS_H
#define MAQUINA_ESTADOS_OBJETOS_H

#include<cassert>
#include<string>
#include"Estado.h"

class Mensaje;

template<class entidad>
class Maquina_Estados_Objetos
{
private:
	// Puntero a la entidad a la que pertenece esta instancia
	entidad* entidad_;
	Estado<entidad>* estadoActual_;
	// Este estado se llama cada vez que se actualiza la Maquina_Estados_Objetos
	Estado<entidad>* estadoGlobal_;
	Estado<entidad>* estadoAnterior_;
	
protected:
public:
	Maquina_Estados_Objetos(entidad* e):entidad_(e), estadoActual_(NULL), 
	estadoGlobal_(NULL), estadoAnterior_(NULL){}
	
	virtual ~Maquina_Estados_Objetos(){}
	
	// ===================================================================================
	// GETTERS
	// ===================================================================================
	Estado<entidad>* Get_Estado_Actual()const  { return estadoActual_; }
	Estado<entidad>* Get_Estado_Anterior()const{ return estadoAnterior_; }
	Estado<entidad>* Get_Estado_Global()const  { return estadoGlobal_ ;}
	
	// ===================================================================================
	// SETTERS
	// ===================================================================================
	void Set_Estado_Actual(Estado<entidad>*	e)  { estadoActual_ = e;    }
	void Set_Estado_Anterior(Estado<entidad>* e){ estadoAnterior_  = e; }
	void Set_Estado_Global(Estado<entidad>* e)  { estadoGlobal_ = e;    }
	
	// ===================================================================================
	// MÉTODOS
	// ===================================================================================
	void Actualiza()const
	{
		// Si hay un estado global lo ejecuta, sino no hace nada
		if(estadoGlobal_)
			estadoGlobal_->Realiza(entidad_);
		
		// Si hay un estado actual lo ejecuta, sino no hace nada
		if(estadoActual_)
			estadoActual_->Realiza(entidad_);
		
	}
	void Cambia_Estado(Estado<entidad>* estadoNuevo)
	{
		assert(estadoNuevo && "ERROR : Maquina_Estados_Objetos trata de cambiar a un estado NULL.\n");
		
		// Guarda estado actual;
		estadoAnterior_ = estadoActual_;
		
		// Llama al método 'salir' del estado actual
		estadoActual_->Salir(entidad_);
		
		// Cambia al estado nuevo
		estadoActual_ = estadoNuevo;
		
		// Llama a al método 'entrar' del nuevo estado
		estadoActual_->Entrar(entidad_);
	}
	bool Gestiona_Mensaje(const Mensaje& msg)const
	{
		// 1º comprueba si el estadoActual_ es válido y puede gestionar el msg
		if(estadoActual_ && estadoActual_->Transmite_Mensaje(entidad_, msg))
			return true;
		// Si no, si hay un estado global implementado, manda el mensaje a ese estado
		if(estadoGlobal_ && estadoGlobal_->Transmite_Mensaje(entidad_, msg))
			return true;
		
		return false;
	}
	void Vuelve_Estado_Anterior()
	{
		Cambia_Estado(estadoAnterior_);
	}
};

#endif

