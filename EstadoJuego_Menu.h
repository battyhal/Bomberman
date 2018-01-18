#ifndef ESTADOJUEGO_MENU_H
#define ESTADOJUEGO_MENU_H

#include"EstadoJuego.h"

class Juego;

class EstadoJuego_Menu : public EstadoJuego
{
private:
	EstadoJuego_Menu(){}
	EstadoJuego_Menu(const EstadoJuego_Menu&);
	EstadoJuego_Menu& operator=(const EstadoJuego_Menu&);
	static const std::string menu_ID;
protected:
public:
	// ===============================================================
	// GETTERS
	// ===============================================================
	virtual std::string Get_ID() const;
	static EstadoJuego_Menu* Get_Instancia();
	
	// ===============================================================
	// MÉTODOS
	// ===============================================================
	virtual bool Entra();
	virtual void Realiza();
	virtual bool Sale();
	
};

typedef EstadoJuego_Menu Menu;

#endif

