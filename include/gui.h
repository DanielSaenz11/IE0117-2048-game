#ifndef GUI_H
#define GUI_H

#include <stdbool.h>  // Incluir para usar el tipo de dato bool y las constantes true/false
#include "../include/gui.h"
#include "../include/window.h"
#include <SDL2/SDL.h>

int initSDLAndWindow(Window* window);
void renderizarTablero(Game* game, SDL_Renderer* renderer);
void manejarEventos(Game* game);
int createBoardSizeWindow(Window* window, int* boardSize);

#endif // GUI_H
