#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> // Ejemplo de inclusión adicional
#include "game-logic.h"

// Declaración de funciones específicas de la GUI
void render_board(Game *game, SDL_Renderer *renderer);

//Funcion para Game Over
void render_game_over(SDL_Renderer);

#endif /* GUI_H */

