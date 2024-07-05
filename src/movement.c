#include "../include/gui.h"
#include "../include/game-logic.h"
#include "../include/movement.h"
#include <stdio.h>


/*
 * moverCasillas() realiza el movimientos de las casillas en una direccion dada
 * 
 * @param1 Game* game: Puntero al struct game
 * @param2 char direccion: Direccion indicada de movimiento (u|d|r|l)
 * @return casillasMovidas: Numero de casillas movidas durante el llamado de la funcion
 */
int moverCasillas(Game* game, char direccion) {
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
        return -1;
    }

    return casillasMovidas;

}

/*
 * fusionarCasillas() se encarga de fusionar las casillas contiguas entre si en
 * la direccion indicada
 * 
 * @param1 Game* game: Puntero al struct game
 * @param2 char direccion: Direccion de fusion indicada
 */
void fusionarCasillas(Game* game, char direccion) {

    int filaInicio = 0, filaAvance = 0;
    int columnaInicio = 0, columnaAvance = 0;

    int filaLimite = game->tamanoTablero, columnaLimite = game->tamanoTablero;


    switch (direccion)
    {
    case 'u':
        filaAvance = 1;

        break;

    case 'd':
        filaInicio = game->tamanoTablero -1;
        filaAvance = -1;
        filaLimite = -1;

        break;

    case 'l':
        columnaAvance = 1;

        break;

    case 'r':
        columnaInicio = game->tamanoTablero -1;
        columnaAvance = -1;
        columnaLimite = -1;

        break;

    default:
        printf("Direccion invalida\n");
        return;
    }


    for (int i=filaInicio; i != filaLimite; i+=(filaAvance!=0 ? filaAvance : 1)) {

        for (int j=columnaInicio; j != columnaLimite; j+=(columnaAvance!=0 ? columnaAvance : 1)) {
            
            if ((i+filaAvance >= 0) && (i+filaAvance < game->tamanoTablero) && (j+columnaAvance >= 0) && (j+columnaAvance < game->tamanoTablero)) {

                // No es una casilla vacia
                if ((game->tablero[i][j] != 0) && (game->tablero[i][j] == game->tablero[i+filaAvance][j+columnaAvance])) {

                    game->tablero[i][j] *= 2;
                    game->tablero[i+filaAvance][j+columnaAvance] = 0;

                    actualizarPuntuacion(game, game->tablero[i][j]);

                    j += columnaAvance;

                }
            }
        }
    }
    
}
