#ifndef GAME_LOGIC_H

#define GAME_LOGIC_H

typedef struct Game {
    int **tablero; // Doble puntero para tener un array 2D
    int puntuacion;
    int tamanoTablero;
} Game;

int checkSize();

char checkTecla();

int init_board(Game* game);

void printTablero(Game* game); // Terminal debugging

void addCasillaRandom(Game* game);

int checkPerder(Game* game);

void actualizarPuntuacion(Game* game, int puntuacion);

void freeTablero(Game* game);

/ Declaraciones adicionales para las funciones en game-logic.c
void moverCasillas(Game* game, char direccion);
void fusionarCasillas(Game* game, char direccion);

#endif /* GAME_LOGIC_H */
