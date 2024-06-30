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
    Uint32 next_game_tick = SDL_GetTicks();
    char direccion = ' ';
    int quit = 0;

    while (!quit && !(checkPerder(&game))) {
    // Manejar eventos de SDL
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = 1; // Establecer la condición para salir
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                // Manejar otras teclas según tu lógica de juego
                case SDLK_UP:
                    direccion = 'u';
                    break;
                // Otros casos...
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
        SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
        SDL_RenderClear(window.renderer);
        renderizarTablero(&game, window.renderer);
        SDL_RenderPresent(window.renderer);
    }

    // Esperar para mantener una tasa de fotogramas estable
    Uint32 now = SDL_GetTicks();
    if (next_game_tick <= now) {
        next_game_tick = now + TICK_INTERVAL;
    } else {
        SDL_Delay(next_game_tick - now);
    }
}

// Esperar antes de salir
SDL_Delay(1000); // Espera adicional antes de cerrar la ventana

// Limpiar y salir
freeTablero(&game);
cleanupWindow(&window);

return EXIT_SUCCESS;
}
