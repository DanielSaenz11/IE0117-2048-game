#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>
#include "game.h"  // Incluye el archivo donde está definida la estructura Game

// Función para renderizar el tablero
void render_board(Game *game, SDL_Renderer *renderer);

#endif /* GUI_H */
