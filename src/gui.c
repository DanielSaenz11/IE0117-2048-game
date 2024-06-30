// gui.c
#include "../include/gui.h"
#include "../include/window.h"
#include <stdio.h>
#include <stdbool.h>

// Variable global para el tamaño del tablero
extern int boardSize;

// Función para inicializar SDL, ventana y cargar recursos necesarios
int initSDLAndWindow(Window* window) {
    if (initSDL(window) != 0) {
        printf("Error al inicializar SDL y la ventana.\n");
        return -1;
    }

    return 0;
}

// Función para renderizar el juego en la ventana
void renderizarTablero(Game* game, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Implementa aquí la lógica para renderizar el juego según el estado actual del juego en `game`
    // Por ejemplo:
    // SDL_Rect rect;
    // rect.x = 0;
    // rect.y = 0;
    // rect.w = 100;
    // rect.h = 100;
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

// Función para manejar eventos del juego
void manejarEventos(Game* game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game->quit = true;
                break;
            case SDL_KEYDOWN:
                // Manejar teclas según sea necesario
                break;
            default:
                break;
        }
    }
}

// Función principal para coordinar la ejecución del juego
int ejecutarJuego() {
    Window window;
    Game game;

    if (initSDLAndWindow(&window) != 0) {
        printf("Error al inicializar SDL y la ventana.\n");
        return -1;
    }

    // Bucle de selección de tamaño del tablero
    while (boardSize == 0) {
        manejarEventos(&game);

        if (createBoardSizeWindow(&window, &boardSize) != 0) {
            printf("Error al crear la ventana de selección del tamaño del tablero.\n");
            break;
        }
    }

    // Bucle principal del juego
    while (!game.quit) {
        manejarEventos(&game);
        renderizarTablero(&game, window.renderer);
    }

    cleanupWindow(&window);
    return 0;
}
