#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

typedef struct {
    int **tablero;
    int tamanoTablero;
    int puntuacion;
    int quit; // Agregar un miembro para indicar si el juego debe finalizar
} Game;

int init_board(Game* game);
void printTablero(Game* game);
void addCasillaRandom(Game* game);
int checkPerder(Game* game);
void actualizarPuntuacion(Game* game, int puntuacion);
void freeTablero(Game* game);
int moverCasillas(Game* game, char direccion);
void fusionarCasillas(Game* game, char direccion);

#endif // GAME_LOGIC_H
