#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Window;

int initSDL(Window* window);
void cleanupWindow(Window* window);

#endif /* WINDOW_H */
