#include "../include/game-logic.h"
#include "../include/movement.h"
#include "../include/gui.h"
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

int main() {
    srand(time(NULL));

    Game game;
    printf("Enter board size: ");
    scanf("%d", &game.tamanoTablero);

    if (!init_board(&game)) {  // Validación adicional para init_board
        printf("Failed to initialize the board.\n");
        return 1;
    }
    addCasillaRandom(&game);  // Añadir las primeras dos casillas aleatorias
    addCasillaRandom(&game);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
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

    int quit = 0;
    SDL_Event e;
    while (!quit && !checkPerder(&game)) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        moverCasillas(&game, 'w');
                        addCasillaRandom(&game);
                        break;
                    case SDLK_DOWN:
                        moverCasillas(&game, 's');
                        addCasillaRandom(&game);
                        break;
                    case SDLK_LEFT:
                        moverCasillas(&game, 'a');
                        addCasillaRandom(&game);
                        break;
                    case SDLK_RIGHT:
                        moverCasillas(&game, 'd');
                        addCasillaRandom(&game);
                        break;
                }
            }
        }
        render_board(&game, renderer);
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    freeTablero(&game);

    return 0;
}
