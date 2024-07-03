#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include "gui.h" 
#include "game-logic.h"

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

            if (game->board[i][j] == 0) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 100 + game->board[i][j] * 10, 100 + game->board[i][j] * 5, 100 + game->board[i][j] * 2, 255);
            }
            SDL_RenderFillRect(renderer, &cell);

            if (game->board[i][j] != 0) {
                char text[5];
                sprintf(text, "%d", game->board[i][j]);
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
    scanf("%d", &game.size);

    init_board(&game);
    add_random_tile(&game);
    add_random_tile(&game);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game.size * 100, game.size * 100, SDL_WINDOW_SHOWN);
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
    while (!quit && !check_game_over(&game)) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        move_tiles(&game, 'w');
                        add_random_tile(&game);
                        break;
                    case SDLK_DOWN:
                        move_tiles(&game, 's');
                        add_random_tile(&game);
                        break;
                    case SDLK_LEFT:
                        move_tiles(&game, 'a');
                        add_random_tile(&game);
                        break;
                    case SDLK_RIGHT:
                        move_tiles(&game, 'd');
                        add_random_tile(&game);
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
