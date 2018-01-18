#ifndef ESTADOJUEGO_PAUSA_H
#define ESTADOJUEGO_PAUSA_H

#include"EstadoJuego.h"

class Juego;

class EstadoJuego_Pausa : public EstadoJuego
{
private:
	EstadoJuego_Pausa(){}
	EstadoJuego_Pausa(const EstadoJuego_Pausa &);
	EstadoJuego_Pausa& operator=(const EstadoJuego_Pausa&);
	static const std::string pausa_ID;
protected:
public:
	// ===============================================================
	// GETTERS
	// ===============================================================
	virtual std::string Get_ID() const;
	static EstadoJuego_Pausa* Get_Instancia();
	
	// ===============================================================
	// MÉTODOS
	// ===============================================================
	virtual bool Entra();
	virtual void Realiza();
	virtual bool Sale();
	
};

#endif

