#include "../include/game-logic.h"
#include "../include/movement.h"
#include <stdio.h>

void moverCasillas(Game* game, char direccion) {
    int casillasMovidas = 0;


    switch (direccion)
    {
    case 'u':
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
        break;

    case 'd':
        // j < game->tamanoTablero-1: para evitar salir del rango pues se commpara con el siguiente
        for (int i=0; i < game->tamanoTablero-1; i++) {

            for (int j=0; j < game->tamanoTablero; j++) {
                
                // No es una casilla vacia
                if (game->tablero[i][j] != 0) {
                    int filaObjetivo = i;

                    while ((filaObjetivo >= 0) && (game->tablero[filaObjetivo+1][j] == 0)) {
                        game->tablero[filaObjetivo+1][j] = game->tablero[filaObjetivo][j];
                        game->tablero[filaObjetivo][j] = 0;
                        filaObjetivo--;
                        casillasMovidas++;
                    }
                }
            }
        }
        break;

    case 'l':
        for (int i=0; i < game->tamanoTablero; i++) {

            for (int j=0; j < game->tamanoTablero; j++) {
                
                // No es una casilla vacia
                if (game->tablero[i][j] != 0) {
                    int columnaObjetivo = j;

                    while ((columnaObjetivo > 0) && (game->tablero[i][columnaObjetivo-1] == 0)) {
                        game->tablero[i][columnaObjetivo-1] = game->tablero[i][columnaObjetivo];
                        game->tablero[i][columnaObjetivo] = 0;
                        columnaObjetivo--;
                        casillasMovidas++;
                    }
                }
            }
        }
        break;

    case 'r':
        for (int i=0; i < game->tamanoTablero; i++) {

            for (int j=0; j < game->tamanoTablero-1; j++) {
                
                // No es una casilla vacia
                if (game->tablero[i][j] != 0) {
                    int columnaObjetivo = j;

                    while ((columnaObjetivo >= 0) && (game->tablero[i][columnaObjetivo+1] == 0)) {
                        game->tablero[i][columnaObjetivo+1] = game->tablero[i][columnaObjetivo];
                        game->tablero[i][columnaObjetivo] = 0;
                        columnaObjetivo--;
                        casillasMovidas++;
                    }
                }
            }
        }
        break;

    
    default:
        printf("Direccion invalida\n");
        break;
    }

    

    // if (casillasMovidas) {
    //     fusionarCasillas(game, direccion);
    //     moverCasillas(game, direccion);
    // }

}


void fusionarCasillas(Game* game, char direccion) {
    for (int i=0; i < game->tamanoTablero - 1; i++) {

        for (int j=0; j < game->tamanoTablero; j++) {
            
            // No es una casilla vacia
            if ((game->tablero[i][j] != 0) && (game->tablero[i][j] == game->tablero[i+1][j])) {
                
                game->tablero[i][j] *= 2;
                game->tablero[i+1][j] = 0;

                actualizarPuntuacion(game, game->tablero[i][j]);
            }
        }
    }
}
