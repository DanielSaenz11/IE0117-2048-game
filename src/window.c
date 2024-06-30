#include "../include/window.h"
#include <stdio.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int initSDL(Window* window) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }

    window->window = SDL_CreateWindow("Seleccionar Tamaño del Tablero",
                                      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                      WINDOW_WIDTH, WINDOW_HEIGHT,
                                      SDL_WINDOW_SHOWN);
    if (window->window == NULL) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window->window);
        SDL_Quit();
        return -1;
    }

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
    // Implementar la ventana de selección del tamaño del tablero aquí
    // Usar SDL_Renderer* renderer de window->renderer para renderizar elementos
    // Manejar eventos de SDL para la entrada del usuario y la validación del tamaño del tablero

    return 0;
}

void cleanupWindow(Window* window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    TTF_Quit();
    SDL_Quit();
}
