#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

// Definir las dimensiones de la ventana
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Estructura para manejar la ventana SDL
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Window;

// Función para inicializar SDL y crear la ventana
int initSDL(Window* window);

// Función para crear la ventana de selección de tamaño del tablero
int createBoardSizeWindow(Window* window, int* boardSize);

// Función para limpiar recursos de la ventana
void cleanupWindow(Window* window);

void renderizarTablero(Game* game, SDL_Renderer* renderer);
void manejarEventos(Game* game);

#endif /* WINDOW_H */
