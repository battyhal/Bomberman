#ifndef ESTADOJUEGO_JUGAR_H
#define ESTADOJUEGO_JUGAR_H

#include"EstadoJuego.h"

class EstadoJuego_Jugar : public EstadoJuego
{
private:
	EstadoJuego_Jugar(){}
	EstadoJuego_Jugar(const EstadoJuego_Jugar&);
	EstadoJuego_Jugar&operator=(const EstadoJuego_Jugar&);
	static const std::string jugar_ID;
protected:
public:
	// ===============================================================
	// GETTERS
	// ===============================================================
	virtual std::string Get_ID() const;
	static EstadoJuego_Jugar* Get_Instancia();
	
	// ===============================================================
	// MÉTODOS
	// ===============================================================
	virtual bool Entra();
	virtual void Realiza();
	virtual bool Sale();
	
};

#endif

