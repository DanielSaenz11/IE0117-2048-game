#ifndef GUI_H
#define GUI_H
#include <SDL.h>
#include <SDL_render.h>


#include "game-logic.h" // Incluye los encabezados necesarios

void renderizarTablero(Game* game, SDL_Renderer* renderer);

#endif // GUI_H
