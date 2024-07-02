#ifndef GAME_LOGIC_H

#define GAME_LOGIC_H

typedef struct Game {
    int **tablero; // Doble puntero para tener un array 2D
    int puntuacion;
    int tamanoTablero;
} Game;

int checkSize();

int init_board(Game* game);

void printTablero(Game* game);

void addCasillaRandom(Game* game);
int checkPerder(Game* game);
void freeTablero(Game* game);

#endif /* GAME_LOGIC_H */ 

