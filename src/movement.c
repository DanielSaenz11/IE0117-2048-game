#include "../include/game-logic.h"
#include "../include/movement.h"

void moverCasillas(Game* game, char* direccion) {
    int casillasMovidas = 0;

    for (int i=0; i < game->tamanoTablero; i++) {

        for (int j=0; j < game->tamanoTablero; j++) {
            
            // No es una casilla vacia
            if (game->tablero[i][j] != 0) {
                int filaObjetivo = i;

                while ((filaObjetivo > 0) && (game->tablero[filaObjetivo-1][j] == 0)) {
                    game->tablero[filaObjetivo-1][j] = game->tablero[filaObjetivo][j];
                    game->tablero[filaObjetivo][j] = 0;
                    filaObjetivo--;
                    casillasMovidas++;
                }
            }
        }
    }
}


void fusionarCasillas(Game* game, char direccion) {

}
