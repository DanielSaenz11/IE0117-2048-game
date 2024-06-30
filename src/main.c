// main.c

#include "../include/game-logic.h"
#include "../include/movement.h"
#include "../include/gui.h"
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define TICK_INTERVAL 100

int main() {
    // Inicialización de SDL y creación de ventana
    if (initSDL() != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Inicialización del juego
    srand(time(NULL));
    Game game;
    int game_running = 0;

    game.tamanoTablero = checkSize();
    game_running = init_board(&game);

    if (!game_running) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
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
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color de fondo blanco
            SDL_RenderClear(renderer);

            renderizarTablero(&game);  // Llamar a la función para renderizar el tablero

            SDL_RenderPresent(renderer);  // Mostrar el renderizado en pantalla
        }

        // Esperar para mantener una tasa de fotogramas estable (opcional)
        Uint32 now = SDL_GetTicks();
        if (next_game_tick <= now) {
            next_game_tick = now + TICK_INTERVAL;
        } else {
            SDL_Delay(next_game_tick - now);
        }
    }

    // Liberar recursos y salir
    freeTablero(&game);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return EXIT_SUCCESS;
}
