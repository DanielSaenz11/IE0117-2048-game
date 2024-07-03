#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> // Ejemplo de inclusión adicional
#include "game-logic.h"

// Declaración de funciones específicas de la GUI
void render_board(Game *game, SDL_Renderer *renderer);

int show_initial_message(SDL_Renderer *renderer)

#endif /* GUI_H */

