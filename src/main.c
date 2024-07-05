#include "../include/game-logic.h"
#include "../include/movement.h"
#include "../include/gui.h"
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main() {
    srand(time(NULL)); // Generacion de numeros aleatorios

    char direccion; // Manejar la direccion de movimiento

    Game game; // Estructura para almacenar las variables del juego
    
   game.tamanoTablero =  checkSize(); // Validar entrada del usuario
    
    // Reservar memoria dinamica para el tablero
    if (!init_board(&game)) {
        printf("Error al inicializar el tablero.\n");
        return 1;
    }
    
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("No se pudo inicializar SDL. SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    // Inicializar SDL_ttf
    if (TTF_Init() < 0) {
        printf("No se pudo inicializar SDL_ttf. SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }
    
    // Iniciar ventana
    SDL_Window *window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game.tamanoTablero * 100, game.tamanoTablero * 100 + 50, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("No se pudo crear la ventana. SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    // Iniciar render
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("No se pudo inicializar el renderer. SDL Error: %s\n", SDL_GetError());
        return 1;
    }
       
    // Añadir las primeras dos casillas aleatorias en el tablero
    addCasillaRandom(&game);
    addCasillaRandom(&game);

    int quit = 0; // En caso de que se presione alguna tecla para salir
    SDL_Event evento;

    while (!quit && !checkPerder(&game)) {

        while (SDL_PollEvent(&evento) != 0) {

            if (evento.type == SDL_QUIT) {
                quit = 1;
            } 
            else if (evento.type == SDL_KEYDOWN) {

                switch (evento.key.keysym.sym) {

                    case SDLK_UP:
                    case 'u':
                        direccion = 'u';
                        moverCasillas(&game, direccion);
                        addCasillaRandom(&game);
                        fusionarCasillas(&game, direccion);
                        break;

                    case SDLK_DOWN:
                    case 'd':
                        direccion = 'd';
                        moverCasillas(&game, direccion);
                        addCasillaRandom(&game);
                        fusionarCasillas(&game, direccion);
                        break;

                    case SDLK_LEFT:
                    case 'l':
                        direccion = 'l';
                        moverCasillas(&game, 'l');
                        addCasillaRandom(&game);
                        fusionarCasillas(&game, 'l');
                        break;

                    case SDLK_RIGHT:
                    case 'r':
                        direccion = 'r';
                        moverCasillas(&game, direccion);
                        addCasillaRandom(&game);
                        fusionarCasillas(&game, direccion);
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
            render_tablero(&game, renderer);
        }
    }
        

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    freeTablero(&game);
    TTF_Quit();
    return 0;
}
