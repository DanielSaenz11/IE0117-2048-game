#include "game-logic.h"
#include "movement.h"
#include "gui.h"
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main() {
    srand(time(NULL)); // Generacion de numeros aleatorios

    char direccion; // Manejar la direccion de movimiento

    Game game; // Estructura para almacenar las variables del juego

    printf("Utilice las flechas para realizar los movimientos y ESC para salir\n");
    
    game.tamanoTablero =  checkSize(); // Validar entrada del usuario
    
    // Reservar memoria dinamica para el tablero
    if (init_board(&game) < 0) {
        printf("Error al inicializar el tablero.\n");
        exit(EXIT_FAILURE);
    }
    
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "No se pudo inicializar SDL. SDL Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Inicializar SDL_ttf
    if (TTF_Init() < 0) {
        fprintf(stderr, "No se pudo inicializar SDL_ttf. SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
    // Iniciar ventana
    SDL_Window *window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game.tamanoTablero * 100, game.tamanoTablero * 100 + 50, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "No se pudo crear la ventana. SDL Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Iniciar render
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "No se pudo inicializar el renderer. SDL Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Añadir las primeras dos casillas aleatorias en el tablero
    addCasillaRandom(&game);
    addCasillaRandom(&game);

    int quit = 0; // En caso de que se presione alguna tecla para salir
    SDL_Event evento;
    ErrorCode resultado_movimiento;
    ErrorCode resultadoCasillaRandom;
    ErrorCode resultado_fusion;

    while (!quit && checkPerder(&game) == ERROR_NONE && checkVictoria(&game) == ERROR_NONE) {

        while (SDL_PollEvent(&evento) != 0) {

            if (evento.type == SDL_QUIT) {
                quit = 1;
            }

            else if (evento.type == SDL_KEYDOWN) {

                switch (evento.key.keysym.sym) {

                    case SDLK_UP:
                    case 'u':
                        direccion = 'u';

                        resultado_movimiento = moverCasillas(&game, direccion);
                        if (resultado_movimiento < 0) {
                            quit = 1;
                            break;
                        }

                        resultadoCasillaRandom = addCasillaRandom(&game);
                        if (resultadoCasillaRandom < 0) {
                            quit = 1;
                            break;
                        }

                        resultado_fusion = fusionarCasillas(&game, direccion);
                        if (resultado_fusion < 0) {
                            quit = 1;
                            break;
                        }

                        break;

                    case SDLK_DOWN:
                    case 'd':
                        direccion = 'd';

                        resultado_movimiento = moverCasillas(&game, direccion);
                        if (resultado_movimiento < 0) {
                            quit = 1;
                            break;
                        }

                        resultadoCasillaRandom = addCasillaRandom(&game);
                        if (resultadoCasillaRandom < 0) {
                            quit = 1;
                            break;
                        }

                        resultado_fusion = fusionarCasillas(&game, direccion);
                        if (resultado_fusion < 0) {
                            quit = 1;
                            break;
                        }

                        break;

                    case SDLK_LEFT:
                    case 'l':
                        direccion = 'l';

                        resultado_movimiento = moverCasillas(&game, direccion);
                        if (resultado_movimiento < 0) {
                            quit = 1;
                            break;
                        }

                        resultadoCasillaRandom = addCasillaRandom(&game);
                        if (resultadoCasillaRandom < 0) {
                            quit = 1;
                            break;
                        }

                        resultado_fusion = fusionarCasillas(&game, direccion);
                        if (resultado_fusion < 0) {
                            quit = 1;
                            break;
                        }

                        break;

                    case SDLK_RIGHT:
                    case 'r':
                        direccion = 'r';

                        resultado_movimiento = moverCasillas(&game, direccion);
                        if (resultado_movimiento < 0) {
                            quit = 1;
                            break;
                        }

                        resultadoCasillaRandom = addCasillaRandom(&game);
                        if (resultadoCasillaRandom < 0) {
                            quit = 1;
                            break;
                        }

                        resultado_fusion = fusionarCasillas(&game, direccion);
                        if (resultado_fusion < 0) {
                            quit = 1;
                            break;
                        }

                        break;
                    
                    // Para salir del programa
                    case SDLK_ESCAPE:
                    case 'q':
                        quit = 1;
                        break;
                
                    default:
                        break;
                }
            }

            // Renderizar el tablero en cada iteración
            ErrorCode resultado_render = render_tablero(&game, renderer);
            if (resultado_render != ERROR_NONE) {
                quit = 1;
                break;
            }
        }
    }
        
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    
    
    if (checkPerder(&game)) {
        printf("Perdiste :(\n");
    }

    else if (checkVictoria(&game)) {
        printf("Ganaste! Felicidades :)\n");
    }

    else {
        printf("Vuelve pronto\n");
    }

    printf("Puntuacion obtenida: %d\n", game.puntuacion);

    freeTablero(&game); // Liberar memoria dinamica

    exit(EXIT_SUCCESS);
}
