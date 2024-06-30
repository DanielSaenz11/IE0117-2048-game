// main.c

#include "../include/game-logic.h"
#include "../include/movement.h"
#include "../include/gui.h"
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

int main() {
    // Inicialización de SDL y creación de ventana para pedir tamaño del tablero
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *ventanaInicial = SDL_CreateWindow("2048 - Tamaño del Tablero",
                                                  SDL_WINDOWPOS_CENTERED,
                                                  SDL_WINDOWPOS_CENTERED,
                                                  400, 200, 0);

    if (!ventanaInicial) {
        fprintf(stderr, "Error al crear la ventana inicial: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer *rendererInicial = SDL_CreateRenderer(ventanaInicial, -1, SDL_RENDERER_ACCELERATED);
    if (!rendererInicial) {
        fprintf(stderr, "Error al crear el renderer inicial: %s\n", SDL_GetError());
        SDL_DestroyWindow(ventanaInicial);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_bool ventanaAbierta = SDL_TRUE;
    SDL_Event event;
    int tamanoTablero = 0;

    while (ventanaAbierta) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    ventanaAbierta = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_3:
                            tamanoTablero = 3;
                            ventanaAbierta = SDL_FALSE;
                            break;
                        case SDLK_4:
                            tamanoTablero = 4;
                            ventanaAbierta = SDL_FALSE;
                            break;
                        case SDLK_5:
                            tamanoTablero = 5;
                            ventanaAbierta = SDL_FALSE;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(rendererInicial, 255, 255, 255, 255);
        SDL_RenderClear(rendererInicial);

        // Dibujar texto en la ventana inicial
        // Puedes usar SDL_ttf para manejar fuentes si necesitas texto más complejo

        SDL_RenderPresent(rendererInicial);
    }

    SDL_DestroyRenderer(rendererInicial);
    SDL_DestroyWindow(ventanaInicial);

    // Iniciar el juego con el tamaño seleccionado
    if (tamanoTablero >= 3 && tamanoTablero <= 5) {
        // Inicialización del juego con el tamaño seleccionado
        srand(time(NULL));
        Game game;
        int game_running = 0;

        game.tamanoTablero = tamanoTablero;
        game_running = init_board(&game);

        if (!game_running) {
            SDL_Quit();
            return EXIT_FAILURE;
        }

        // Crear ventana y renderer para el juego
        SDL_Window *ventana = SDL_CreateWindow("2048",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              game.tamanoTablero * TILE_SIZE,
                                              game.tamanoTablero * TILE_SIZE, 0);

        if (!ventana) {
            fprintf(stderr, "Error al crear la ventana: %s\n", SDL_GetError());
            SDL_Quit();
            return EXIT_FAILURE;
        }

        SDL_Renderer *renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            fprintf(stderr, "Error al crear el renderer: %s\n", SDL_GetError());
            SDL_DestroyWindow(ventana);
            SDL_Quit();
            return EXIT_FAILURE;
        }

        // Bucle principal del juego (adaptado de tu código existente)
        // Aquí continuarías con el bucle principal y renderizado del juego

        // Liberar recursos y salir al cerrar el juego
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return EXIT_SUCCESS;
    } else {
        // El usuario cerró la ventana inicial sin seleccionar tamaño válido
        SDL_Quit();
        return EXIT_SUCCESS;
    }
}
