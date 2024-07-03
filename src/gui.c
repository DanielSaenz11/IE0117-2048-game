#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include "gui.h" 
#include "game-logic.h"
#include "movement.h"

// Funcion para el render

void render_board(Game *game, SDL_Renderer *renderer) {
    int cell_size = 100;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < game->tamanoTablero; i++) {
        for (int j = 0; j < game->tamanoTablero; j++) {
            SDL_Rect cell;
            cell.x = j * cell_size;
            cell.y = i * cell_size;
            cell.w = cell_size - 5;
            cell.h = cell_size - 5;

            if (game->tablero[i][j] == 0) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 100 + game->tablero[i][j] * 10, 100 + game->tablero[i][j] * 5, 100 + game->tablero[i][j] * 2, 255);
            }
            SDL_RenderFillRect(renderer, &cell);

            if (game->tablero[i][j] != 0) {
                char text[5];
                sprintf(text, "%d", game->tablero[i][j]);
                // Aquí puedes añadir código para renderizar texto usando SDL_ttf o alguna otra biblioteca
            }
        }
    }

    SDL_RenderPresent(renderer);
}

// Main del programa

int main() {
    srand(time(NULL));

    Game game;
    printf("Enter board size: ");
    scanf("%d", &game.tamanoTablero);

    if (!init_board(&game)) {  // Validación adicional para init_board
        printf("Failed to initialize the board.\n");
        return 1;
    }
    addCasillaRandom(&game);  // Cambio: add_random_tile -> addCasillaRandom
    addCasillaRandom(&game);  // Cambio: add_random_tile -> addCasillaRandom


    
    
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
                        addCasillasRandom(&game);
                        break;
                    case SDLK_DOWN:
                        moverCsilla(&game, 's');
                        addCasillaRandom(&game);
                        break;
                    case SDLK_LEFT:
                        moverCasilla(&game, 'a');
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

    free_board(&game);
    return 0;
}
