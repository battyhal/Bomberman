#include "EstadoJuego_GameOver.h"

const std::string EstadoJuego_GameOver::gameOver_ID = "GAME_OVER";

// ======================================================================================
// GETTERS
// ======================================================================================
std::string EstadoJuego_GameOver::Get_ID()const{ return gameOver_ID; }
EstadoJuego_GameOver* EstadoJuego_GameOver::Get_Instancia()
{
	static EstadoJuego_GameOver instancia;
	return& instancia;
}

// ======================================================================================
// MÉTODOS
// ======================================================================================
bool EstadoJuego_GameOver::Entra(){ return true; }
void EstadoJuego_GameOver::Realiza()
{	
	char muerto[9][48] = {
		"                                               ",
		" *     *  *   *  ******  *****  *******  ***** ",
		" * * * *  *   *  *       *   *     *     *   * ",
		" *  *  *  *   *  *       *   *     *     *   * ",
		" *     *  *   *  ***     * **      *     *   * ",
		" *     *  *   *  *       *  *      *     *   * ",
		" *     *   ***   ******  *   *     *     ***** ",
		"                                               ",
	};
	for(int j = 0; j < 9; j++)
	{
		for(int k = 0; k < 48; k++)
		{
			std::cout << muerto[j][k];
		}
		std::cout << "\n";
	}
}

bool EstadoJuego_GameOver::Sale(){ return true; }

