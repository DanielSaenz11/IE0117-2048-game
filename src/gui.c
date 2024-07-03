#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include "gui.h" 
#include "game-logic.h"
#include "movement.h"
#include <SDL2/SDL_ttf.h>


// Función para renderizar el tablero con SDL y SDL_ttf
void render_board(Game *game, SDL_Renderer *renderer) {
    int cell_size = 100;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Color textColor = {255, 255, 255};  // Color blanco para el texto (puedes ajustar según necesites)

    // Iterar sobre el tablero para renderizar cada celda
    for (int i = 0; i < game->tamanoTablero; i++) {
        for (int j = 0; j < game->tamanoTablero; j++) {
            SDL_Rect cell;
            cell.x = j * cell_size;
            cell.y = i * cell_size;
            cell.w = cell_size - 5;
            cell.h = cell_size - 5;

            // Configurar color y renderizar rectángulo de la celda
            if (game->tablero[i][j] == 0) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  // Color para celdas vacías
            } else {
                SDL_SetRenderDrawColor(renderer, 100 + game->tablero[i][j] * 10, 100 + game->tablero[i][j] * 5, 100 + game->tablero[i][j] * 2, 255);  // Color según el valor en la celda
            }
            SDL_RenderFillRect(renderer, &cell);

            // Renderizar texto si la celda no está vacía
            if (game->tablero[i][j] != 0) {
                char text[5];
                sprintf(text, "%d", game->tablero[i][j]);

                // Renderizar texto
                SDL_Surface *surface = TTF_RenderText_Solid(font, text, textColor);
                if (surface == NULL) {
                    printf("Failed to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
                    continue;  // Continuar con la siguiente iteración si hay un error
                }

                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture == NULL) {
                    printf("Failed to create texture from surface! SDL Error: %s\n", SDL_GetError());
                    SDL_FreeSurface(surface);
                    continue;  // Continuar con la siguiente iteración si hay un error
                }

                // Configurar posición del texto dentro de la celda
                SDL_Rect textRect;
                textRect.x = cell.x + (cell_size - surface->w) / 2;
                textRect.y = cell.y + (cell_size - surface->h) / 2;
                textRect.w = surface->w;
                textRect.h = surface->h;

                // Renderizar texto en la pantalla
                SDL_RenderCopy(renderer, texture, NULL, &textRect);

                // Liberar recursos
                SDL_FreeSurface(surface);
                SDL_DestroyTexture(texture);
            }
        }
    }

    // Cerrar la fuente después de su uso
    TTF_CloseFont(font);

    // Actualizar la pantalla
    SDL_RenderPresent(renderer);
}
