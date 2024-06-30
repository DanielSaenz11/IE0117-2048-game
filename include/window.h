// window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

extern SDL_Window* ventana;
extern SDL_Renderer* renderer;

int initSDL();
void closeSDL();

#endif // WINDOW_H
