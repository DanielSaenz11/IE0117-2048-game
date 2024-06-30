// gui.c
#include "gui.h"
#include <SDL2/SDL.h>

void initSDL() {
    // Inicialización de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Creación de la ventana SDL
    ventana = SDL_CreateWindow("2048 Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (ventana == NULL) {
        fprintf(stderr, "Error al crear la ventana SDL: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Creación del renderer SDL
    renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        fprintf(stderr, "Error al crear el renderer SDL: %s\n", SDL_GetError());
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void renderizarTablero(Game *game) {
    // Implementación para renderizar el tablero usando SDL
    // Aquí deberías dibujar el estado actual del juego en la ventana SDL usando renderer
}

void manejarEventos(Game *game) {
    // Implementación para manejar eventos de SDL
    // Aquí deberías capturar eventos del teclado u otros eventos relevantes para el juego
}
