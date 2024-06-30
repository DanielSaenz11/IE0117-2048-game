// gui.h

#ifndef GUI_H
#define GUI_H

#include "game-logic.h" // Asegúrate de incluir el archivo de encabezado adecuado para `Game`

typedef struct {
    bool quit; // Campo para indicar si el juego debe salir
    // Otros campos necesarios para el estado del juego
} Game;

void renderizarTablero(Game* game, SDL_Renderer* renderer);
void manejarEventos(Game* game);
int createBoardSizeWindow(Window* window, int* boardSize);

#endif /* GUI_H */
