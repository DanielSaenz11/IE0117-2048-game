#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/window.h"
#include "../include/gui.h"
#include "../include/game-logic.h"
#include "../include/movement.h"
#define TICK_INTERVAL 100


// Declaración de la función renderizarTablero
void renderizarTablero(Game* game, SDL_Renderer* renderer);

int main() {
    // Estructuras para la ventana y el juego
    Window window;
    Game game;

    // Inicialización de SDL y creación de ventana
    if (initSDL(&window) != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Crear ventana para seleccionar tamaño del tablero
    int tamanoTablero = 0;
    do {
        if (tamanoTablero < 3 || tamanoTablero > 5) {
            printf("Ingresa el tamaño del tablero (entre 3 y 5): ");
            scanf("%d", &tamanoTablero);
            if (tamanoTablero < 3 || tamanoTablero > 5) {
                printf("Tamaño inválido. Intenta de nuevo.\n");
            }
        }
    } while (tamanoTablero < 3 || tamanoTablero > 5);

    // Inicialización del juego
    srand(time(NULL));
    game.tamanoTablero = tamanoTablero;
    if (!init_board(&game)) {
        fprintf(stderr, "Error al inicializar el juego.\n");
        cleanupWindow(&window);
        return EXIT_FAILURE;
    }

    // Bucle principal del juego
    SDL_Event event;
    char direccion = ' ';
    int quit = 0;
    Uint32 next_game_tick = SDL_GetTicks();

    while (!quit && !(checkPerder(&game))) {
        // Manejar eventos de SDL
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1; // Salir al cerrar la ventana
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_l:
                        direccion = 'l'; // Tecla 'l' para izquierda
                        break;
                    case SDLK_r:
                        direccion = 'r'; // Tecla 'r' para derecha
                        break;
                    case SDLK_u:
                        direccion = 'u'; // Tecla 'u' para arriba
                        break;
                    case SDLK_d:
                        direccion = 'd'; // Tecla 'd' para abajo
                        break;
                    case SDLK_q:
                        quit = 1; // Tecla 'q' para salir del juego
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

        // Controlar la tasa de fotogramas
        Uint32 now = SDL_GetTicks();
        Uint32 waitTime = next_game_tick > now ? next_game_tick - now : 0;
        SDL_Delay(waitTime);
        next_game_tick = SDL_GetTicks() + TICK_INTERVAL;
    }

    // Esperar antes de salir
    SDL_Delay(1000);

    // Limpiar y salir
    freeTablero(&game);
    cleanupWindow(&window);

    return EXIT_SUCCESS;
}

