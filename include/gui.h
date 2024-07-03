#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> // Ejemplo de inclusión adicional
#include "game-logic.h"

// Declaración de funciones específicas de la GUI
void render_board(Game *game, SDL_Renderer *renderer);

void show_board_size_selection(SDL_Renderer *renderer, int *selected_size) 

#endif /* GUI_H */

