#include <stdio.h>
#include <stdlib.h>

typedef struct Game {
    int **tablero; // Doble puntero para tener un array 2D
    int puntuacion;
    int tamanoTablero;
} Game;

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

void init_board(Game* game) {

    if (game == NULL) {
        printf("Error: Direccion de game indefinida\n");
        return;
    }

    game->tablero = (int **)malloc(game->tamanoTablero * sizeof(int *));

    if (game->tablero == NULL) {
        printf("Error: No se pudo reservar memoria correctamente\n");
        return;
    }


    for (int i = 0; i < game->tamanoTablero; i++) {
        game->tablero[i] = (int *)malloc(game->tamanoTablero * sizeof(int));

        if (game->tablero[i] == NULL) {
            printf("Error: No se pudo reservar memoria correctamente\n");
            return;
        }

        for (int j = 0; j < game->tamanoTablero; j++) {
            game->tablero[i][j] = 0;
        }
    }

    game->puntuacion = 0;
}

// Funcion temporal para la terminal
void printTablero(Game* game) {
    printf("Puntuacion: %d\n\n", game->puntuacion);
    
    for (int i = 0; i < game->tamanoTablero; i++) {
        printf("| ");

        for (int j = 0; j < game->tamanoTablero; j++) {
            printf("%d | ", game->tablero[i][j]);
        }

        printf("\n");
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

    
    printf("%d\n", checkSize(&game));

    // init_board(&game);

    // printTablero(&game);

    // freeTablero(&game);
    
    return 0;
}