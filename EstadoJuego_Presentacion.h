#ifndef ESTADOJUEGO_PRESENTACION_H
#define ESTADOJUEGO_PRESENTACION_H

#include"EstadoJuego.h"

class Juego;

class EstadoJuego_Presentacion : public EstadoJuego
{
private:
	EstadoJuego_Presentacion(){}
	EstadoJuego_Presentacion(const EstadoJuego_Presentacion&);
	EstadoJuego_Presentacion&operator=(const EstadoJuego_Presentacion&);
	static const std::string presentacion_ID;
protected:
public:
	// ===============================================================
	// GETTERS
	// ===============================================================
	virtual std::string Get_ID() const;
	static EstadoJuego_Presentacion* Get_Instancia();
	
	// ===============================================================
	// MÉTODOS
	// ===============================================================
	virtual bool Entra();
	virtual void Realiza();
	virtual bool Sale();
	
};

typedef EstadoJuego_Presentacion Presentacion;

#endif

