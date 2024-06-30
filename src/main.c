#include "../include/game-logic.h"
#include "../include/window.h"
#include "../include/gui.h"
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define TICK_INTERVAL 100

int main() {
    // Estructura para la ventana y renderer
    Window window;

    // Inicialización de SDL y creación de ventana para selección de tamaño
    if (initSDL(&window) != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Crear ventana para seleccionar tamaño del tablero
    int tamanoTablero = 0;
    if (createBoardSizeWindow(&window, &tamanoTablero) != 0) {
        fprintf(stderr, "Error al seleccionar el tamaño del tablero.\n");
        cleanupWindow(&window);
        return EXIT_FAILURE;
    }

    // Inicialización del juego
    srand(time(NULL));
    Game game;
    int game_running = 0;

    game.tamanoTablero = tamanoTablero;
    game_running = init_board(&game);

    if (!game_running) {
        cleanupWindow(&window);
        return EXIT_FAILURE;
    }

    // Bucle principal del juego
    SDL_Event event;
    char direccion = ' ';
    int quit = 0;

    while (!quit && !(checkPerder(&game))) {
        // Manejar eventos de SDL
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        direccion = 'u';
                        break;
                    case SDLK_DOWN:
                        direccion = 'd';
                        break;
                    case SDLK_LEFT:
                        direccion = 'l';
                        break;
                    case SDLK_RIGHT:
                        direccion = 'r';
                        break;
                    case SDLK_q:
                        quit = 1;
                        break;
                    default:
                        break;
                }
            }
        }

        if (direccion != ' ') {
            // Realizar movimiento y actualizaciones del juego
            moverCasillas(&game, direccion);
            fusionarCasillas(&game, direccion);
            moverCasillas(&game, direccion);

            // Reiniciar la dirección después de cada movimiento
            direccion = ' ';

            // Actualizar renderizado del tablero
            SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255); // Color de fondo blanco
            SDL_RenderClear(window.renderer);

            renderizarTablero(&game, window.renderer);  // Renderizar el tablero usando GUI

            SDL_RenderPresent(window.renderer);  // Mostrar el renderizado en pantalla
        }

        // Esperar para mantener una tasa de fotogramas estable (opcional)
        SDL_Delay(TICK_INTERVAL);
    }

    // Limpiar y salir
    freeTablero(&game);
    cleanupWindow(&window);

    return EXIT_SUCCESS;
}
