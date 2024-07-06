// game-logic
#include "gui.h"
#include "game-logic.h"
#include "movement.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*
 * checkSize() verifica el que el input del usuario sea un entero
 * en el rango establecido
 * 
 * @return numero: Numero entero entre 3-5
*/
int checkSize() {
    int numero = 0;
    int esValido = 0;
    char c;

    while (!esValido) {
        printf("Ingrese el tamano del tablero en el que desea jugar [3-5]:\n");
        

        if (scanf("%d", &numero) == 1 && numero >= 3 && numero <=5) {
            esValido = 1;
        }

        else {
            printf("Entrada invalida. Ingrese un numero entero entre 3-5.\n\n");
        }

        // Limpiar buffer de entrada
        while ((c = getchar()) != '\n') {
        }

    }

    return numero;
}

char checkTecla() {
    int esValido = 0;
    char c;
    char direccion;

    while (!esValido) {
        printf("Direccion (u|d|l|r|q):\n");
        

        if (scanf("%c", &direccion) == 1) {
            if (direccion == 'u' || direccion == 'd' || direccion == 'r' || direccion == 'l' || direccion == 'q') {
                esValido = 1;
            }
        }

        else {
            printf("Entrada invalida. Ingrese los siguientes caracteres (u|d|l|r|q).\n\n");
        }

        // Limpiar buffer de entrada
        while ((c = getchar()) != '\n') {
        }

    }

    return direccion;
}

/*
 * init_board() reserva la memoria dinamica para el tablero
 * @param Game* game: Puntero al struct game
 * @return estadoReservacionMemoria (****** Pendiente *******)
*/
int init_board(Game* game) {

    if (game == NULL) {
        fprintf(stderr, "Error direccion de game indefinida: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    game->tablero = (int **)malloc(game->tamanoTablero * sizeof(int *));

    if (game->tablero == NULL) {
        fprintf(stderr, "Error al reservar memoria dinamica para las filas del tablero: %s\n", strerror(errno));
        return NULL_POINTER;
    }


    for (int i = 0; i < game->tamanoTablero; i++) {
        game->tablero[i] = (int *)malloc(game->tamanoTablero * sizeof(int));

        if (game->tablero[i] == NULL) {
            fprintf(stderr, "Error al reservar memeria dinamica para las filas del tablero: %s\n", strerror(errno));
            return NULL_POINTER;
        }

        for (int j = 0; j < game->tamanoTablero; j++) {
            game->tablero[i][j] = 0;
        }
    }

    game->puntuacion = 0;

    return ERROR_NONE;
}

/*
 * printTablero(Game* game) imprime el tablero en la terminal (DEBUGGING)
 * 
 * @param Game* game: Puntero al struct game
 */
int printTablero(Game* game) {
    if (game == NULL) {
        fprintf(stderr, "Error direccion de game indefinida: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    if (game->tablero == NULL) {
        fprintf(stderr, "Error tablero nulo: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    printf("Puntuacion: %d\n", game->puntuacion);
    
    for (int i = 0; i < game->tamanoTablero; i++) {
        printf("| ");

        for (int j = 0; j < game->tamanoTablero; j++) {
            printf("%d | ", game->tablero[i][j]);
        }

        printf("\n");
    }

    printf("\n");
    return ERROR_NONE;
}

/*
 * addCasillaRandom() anade una casilla nueva entre las casillas vacias
 * @param Game* game: Puntero al struct game
 */
int addCasillaRandom(Game* game) {
    if (game == NULL) {
        fprintf(stderr, "Error direccion de game indefinida: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    if (game->tablero == NULL) {
        fprintf(stderr, "Error tablero nulo: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    int casillasVacias = 0;

    // Recorrido para verificar existencia de casillas vacias
    for (int i = 0; i < game->tamanoTablero; i++) {

        for (int j = 0; j < game->tamanoTablero; j++) {

            if (game->tablero[i][j] == 0) {
                casillasVacias++;
            }
        }
    }

    if (casillasVacias == 0) {
        // Condicion de perder
        return 0;
    }

    /* Generar numero aleatorio para el rango de casillas vacias */ 
    int posicionCasilla = rand() % casillasVacias; // 0 - casillasVacias-1

    
    /* Seleccionar valor de nueva casilla */
    int valorCasilla = 2*(rand() % 2 + 1); // 2-4

    /* Agregar al tablero */
    for (int i = 0; i < game->tamanoTablero; i++) {

        for (int j = 0; j < game->tamanoTablero; j++) {

            if (game->tablero[i][j] == 0) {
                
                if (posicionCasilla == 0) {
                    game->tablero[i][j] = valorCasilla;
                    return ERROR_NONE;
                }

            posicionCasilla--;
            }
        }
    }
    return ERROR_NONE;
}

/*
 * checkPerder() verifica si no hay movimientos disponibles
 * 
 * @param Game* game: Puntero al struct game
 * @return 1: Perdio
 * @return 0: No ha perdido
 */
int checkPerder(Game* game) {
    if (game == NULL) {
        fprintf(stderr, "Error direccion de game indefinida: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    if (game->tablero == NULL) {
        fprintf(stderr, "Error tablero nulo: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    int casillasVacias = 0;

    for (int i = 0; i < game->tamanoTablero; i++) {

        for (int j = 0; j < game->tamanoTablero; j++) {

            if (game->tablero[i][j] == 0) {
                casillasVacias++;
            }
        }
    }

    if (casillasVacias == 0) {
        return 1;
    }

    return ERROR_NONE;
}

/*
 * checkVictoria() verifica si una casilla tiene el valor de 2048
 * 
 * @param Game* game: Puntero al struct game
 * @return int esGanador: 1 si es ganador | 0 si perdio
 */
int checkVictoria(Game* game) {
    if (game == NULL) {
        fprintf(stderr, "Error direccion de game indefinida: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    if (game->tablero == NULL) {
        fprintf(stderr, "Error tablero nulo: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    int esGanador = 0;

    for (int i = 0; i < game->tamanoTablero; i++) {

        for (int j = 0; j < game->tamanoTablero; j++) {

            if (game->tablero[i][j] == 2048) {
                esGanador = 1;
            }
        }
    }

    return esGanador;
}

/*
 * actualizarPuntuacion() cambia el valor de la variable puntuacion con el valor de fusion
 * 
 * @param1 Game* game: Puntero al struct game
 * @param2 int puntuacion: Valor de fusion para cambiar la puntuacion
 */
int actualizarPuntuacion(Game* game, int puntuacion) {
    if (game == NULL) {
        fprintf(stderr, "Error direccion de game indefinida: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    game->puntuacion += puntuacion;

    return ERROR_NONE;
}


/*
 * freeTablero() libera la memoria dinamica reservada para el tablero
 * 
 * @param1 Game* game: Puntero al struct game
 */
int freeTablero(Game* game) {
    if (game == NULL) {
        fprintf(stderr, "Error direccion de game indefinida: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    if (game->tablero == NULL) {
        fprintf(stderr, "Error tablero nulo: %s\n", strerror(errno));
        return NULL_POINTER;
    }

    for (int i = 0; i < game->tamanoTablero; i++) {
        free(game->tablero[i]);
    }

    free(game->tablero);

    return ERROR_NONE;
}
