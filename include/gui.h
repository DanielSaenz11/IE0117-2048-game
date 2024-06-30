#ifndef GUI_H
#define GUI_H

#include <stdbool.h>  // Incluir para usar el tipo de dato bool y las constantes true/false
#include "../include/window.h"  // Incluye window.h, no gui.h
#include <SDL2/SDL.h>
#include "../include/game-logic.h"  // Incluye game-logic.h para definición de Game

// Declaraciones de funciones para la interfaz gráfica
int initSDLAndWindow(Window* window);
void renderizarTablero(Game* game, SDL_Renderer* renderer);
void manejarEventos(Game* game);
int createBoardSizeWindow(Window* window, int* boardSize);

#endif // GUI_H
