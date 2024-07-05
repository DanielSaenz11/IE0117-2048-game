#ifndef GUI_H
#define GUI_H

// Inclusion de librerias de SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game-logic.h"

/*
 * render_tablero() se encarga de renderizar el tablero para mostrar en la ventana
 * los movimientos y acciones del usuario
 * 
 * @param1 Game* game: Puntero al struct que almacena las propiedades del juego
 * @param2 SDL_Renderer* renderer: Puntero al renderer propio de SDL
 */
void render_tablero(Game *game, SDL_Renderer *renderer);


#endif /* GUI_H */

