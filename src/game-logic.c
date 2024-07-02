// game-logic
#include "../include/gui.h"
#include "../include/game-logic.h"
#include "../include/movement.h"

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
        printf("Ingrese el tamano del tablero en el que desea jugar:\n");
        

        if (scanf("%d", &numero) == 1) {
            if (numero >= 3 && numero <=5) {
                esValido = 1;
            }
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
        return 0;
    }

    game->tablero = (int **)malloc(game->tamanoTablero * sizeof(int *));

    if (game->tablero == NULL) {
        printf("Error: No se pudo reservar memoria correctamente\n");
        return 0;
    }


    for (int i = 0; i < game->tamanoTablero; i++) {
        game->tablero[i] = (int *)malloc(game->tamanoTablero * sizeof(int));

        if (game->tablero[i] == NULL) {
            printf("Error: No se pudo reservar memoria correctamente\n");
            return 0;
        }

        for (int j = 0; j < game->tamanoTablero; j++) {
            game->tablero[i][j] = 0;
        }
    }

    game->puntuacion = 0;

    return 1;
}

/*
 * printTablero(Game* game) imprime el tablero en la terminal (DEBUGGING)
 * 
 * @param Game* game: Puntero al struct game
 */
void printTablero(Game* game) {
    if (game == NULL) {
        printf("Error: Direccion de game indefinida\n");
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

}

/*
 * addCasillaRandom() anade una casilla nueva entre las casillas vacias
 * @param Game* game: Puntero al struct game
 */
void addCasillaRandom(Game* game) {
    if (game == NULL) {
        printf("Error: Direccion de game indefinida\n");
        return;
    }

    if (game->tablero == NULL) {
        printf("Error: No se pudo reservar memoria correctamente\n");
        return;
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
        return;
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
                    return;
                }

            posicionCasilla--;
            }
        }
    }
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
        printf("Error: Direccion de game indefinida\n");
        return -1;
    }

    if (game->tablero == NULL) {
        printf("Error: No se pudo reservar memoria correctamente\n");
        return -1;
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

    return 0;
}

/*
 * actualizarPuntuacion() cambia el valor de la variable puntuacion con el valor de fusion
 * 
 * @param1 Game* game: Puntero al struct game
 * @param2 int puntuacion: Valor de fusion para cambiar la puntuacion
 */
void actualizarPuntuacion(Game* game, int puntuacion) {
    game->puntuacion += puntuacion;
}


/*
 * freeTablero() libera la memoria dinamica reservada para el tablero
 * 
 * @param1 Game* game: Puntero al struct game
 */
void freeTablero(Game* game) {
    if (game == NULL) {
        printf("Error: Direccion de game indefinida\n");
        return;
    }

    for (int i = 0; i < game->tamanoTablero; i++) {
        free(game->tablero[i]);
    }

    free(game->tablero);
}
