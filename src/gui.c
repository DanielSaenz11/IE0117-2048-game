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
