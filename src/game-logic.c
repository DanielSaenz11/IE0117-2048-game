#include "../include/game-logic.h"

#include <stdio.h>
#include <stdlib.h>


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
            printf("Entrada invalida. Ingrese un numero entero entre 3-5.\n");
        }

        // Limpiar buffer de entrada
        while ((c = getchar()) != '\n' && c != EOF) {
        }

    }

    return numero;
}

int init_board(Game* game) {

    if (game == NULL) {
        printf("Error: Direccion de game indefinida\n");
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

// Funcion temporal para la terminal
void printTablero(Game* game) {
    if (game == NULL) {
        printf("Error: Direccion de game indefinida\n");
    }

    printf("Puntuacion: %d\n\n", game->puntuacion);
    
    for (int i = 0; i < game->tamanoTablero; i++) {
        printf("| ");

        for (int j = 0; j < game->tamanoTablero; j++) {
            printf("%d | ", game->tablero[i][j]);
        }

        printf("\n");
    }

}

void addCasillaRandom(Game* game) {
    if (game == NULL) {
        printf("Error: Direccion de game indefinida\n");
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

    printf("%d\n", casillasVacias);

    if (casillasVacias == 0) {
        // Condicion de perder
        return;
    }



}


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

int main() {
    Game game;
    int game_running = 0;

    checkSize(&game);

    game_running = init_board(&game);

    if (!game_running) {      
        return 1;
    }
    

    addCasillaRandom(&game);

    // init_board(&game);

    // printTablero(&game);

    // freeTablero(&game);
    
    return 0;
}