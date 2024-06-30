// game-logic.h

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "gui.h" // Incluir gui.h para la definición de Game si es necesario

typedef struct {
    // Definición de campos necesarios para la lógica del juego
    int tamanoTablero;
    // Otros campos según sea necesario
} Game;

int init_board(Game* game);
int checkPerder(Game* game);
int moverCasillas(Game* game, char direccion);
void fusionarCasillas(Game* game, char direccion);
void freeTablero(Game* game);

#endif /* GAME_LOGIC_H */
