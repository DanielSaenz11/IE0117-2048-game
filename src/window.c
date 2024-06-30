#include "../include/window.h"
#include <stdio.h>

int initSDL(Window* window) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Crear ventana
    window->window = SDL_CreateWindow("Seleccionar Tamaño del Tablero",
                                      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                      WINDOW_WIDTH, WINDOW_HEIGHT,
                                      SDL_WINDOW_SHOWN);
    if (window->window == NULL) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Crear renderer
    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window->window);
        SDL_Quit();
        return -1;
    }

    // Inicializar SDL_ttf
    if (TTF_Init() < 0) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        SDL_DestroyRenderer(window->renderer);
        SDL_DestroyWindow(window->window);
        SDL_Quit();
        return -1;
    }

    return 0;
}

int createBoardSizeWindow(Window* window, int* boardSize) {
    // Aquí deberías implementar la lógica para la ventana de selección de tamaño del tablero
    // Utilizando SDL_Renderer* renderer de window->renderer para renderizar elementos gráficos
    // Manejando eventos de SDL para la entrada del usuario y validación del tamaño del tablero

    return 0;
}

void cleanupWindow(Window* window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    TTF_Quit();
    SDL_Quit();
}
