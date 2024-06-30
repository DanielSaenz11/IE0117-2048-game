#ifndef GUI_H
#define GUI_H

#include "window.h"
#include "game-logic.h"

int initSDLAndWindow(Window* window);
void renderizarTablero(Game* game, SDL_Renderer* renderer);
void manejarEventos(Game* game);
int createBoardSizeWindow(Window* window, int* boardSize);

#endif // GUI_H
