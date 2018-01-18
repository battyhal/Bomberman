#ifndef ESTADOJUEGO_GAMEOVER_H
#define ESTADOJUEGO_GAMEOVER_H

#include"EstadoJuego.h"

class EstadoJuego_GameOver : public EstadoJuego
{
private:
	EstadoJuego_GameOver(){}
	EstadoJuego_GameOver(const EstadoJuego_GameOver &arg){}
	~EstadoJuego_GameOver(){}
	static const std::string gameOver_ID;
protected:
public:
	// ===============================================================
	// GETTERS
	// ===============================================================
	virtual std::string Get_ID() const;
	static EstadoJuego_GameOver* Get_Instancia();
	
	// ===============================================================
	// MÉTODOS
	// ===============================================================
	virtual bool Entra();
	virtual void Realiza();
	virtual bool Sale();
};

#endif

