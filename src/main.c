#include "../include/game-logic.h"
#include "../include/movement.h"
#include "../include/gui.h"
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main() {
    srand(time(NULL));

    char direccion;
    Game game;
    printf("Enter board size: ");
    scanf("%d", &game.tamanoTablero);
    
    if (!init_board(&game)) {  // Validación adicional para init_board
        printf("Failed to initialize the board.\n");
        return 1;
    }
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game.tamanoTablero * 100, game.tamanoTablero * 100, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
        // Llamar a la función de GUI para mostrar el mensaje inicial
    if (!show_initial_message(renderer)) {
        printf("Failed to render initial message!\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Pedir tamaño de tablero al usuario
    printf("Enter board size (between 3 and 5): ");
    scanf("%d", &game.tamanoTablero);
    while (game.tamanoTablero < 3 || game.tamanoTablero > 5) {
        printf("Invalid size! Please enter a size between 3 and 5: ");
        scanf("%d", &game.tamanoTablero);
    }

    if (!init_board(&game)) {  // Validación adicional para init_board
        printf("Failed to initialize the board.\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    addCasillaRandom(&game);  // Añadir las primeras dos casillas aleatorias
    addCasillaRandom(&game);

    int quit = 0;
    SDL_Event e;
    while (!quit && !checkPerder(&game)) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                    case 'u':
                        moverCasillas(&game, 'u');
                        addCasillaRandom(&game);
                        fusionarCasillas(&game, 'u');
                        break;
                    case SDLK_DOWN:
                    case 'd':
                        moverCasillas(&game, 'd');
                        addCasillaRandom(&game);
                        fusionarCasillas(&game, 'd');
                        break;
                    case SDLK_LEFT:
                    case 'l':
                        moverCasillas(&game, 'l');
                        addCasillaRandom(&game);
                        fusionarCasillas(&game, 'l');
                        break;
                    case SDLK_RIGHT:
                    case 'r':
                        moverCasillas(&game, 'r');
                        addCasillaRandom(&game);
                        fusionarCasillas(&game, 'r');
                        break;
                     case 'q':  // Agregar soporte para 'q'
                        quit = 1;
                         break;
                          break;
                    default:
                        break;
                }
            }


            // Renderizar el tablero en cada iteración
            render_board(&game, renderer);
        }
    }
        

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    freeTablero(&game);
    TTF_Quit();
    return 0;
}
