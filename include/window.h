#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Window;

// Definir el tamaño del texto
#define TEXT_SIZE 30
int createBoardSizeWindow(Window* window, int* boardSize);
int initSDL(Window* window);
void cleanupWindow(Window* window);

#endif /* WINDOW_H */
