#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include "gui.h" 
#include "game-logic.h"
#include "movement.h"
#include <SDL2/SDL_ttf.h>

// Función para el render

void render_board(Game *game, SDL_Renderer *renderer) {
    int cell_size = 100;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Cargar la fuente y configurar el color del texto
    TTF_Font *font = TTF_OpenFont("path_to_your_font.ttf", 24);  // Ajusta la ruta y tamaño de la fuente
    SDL_Color textColor = {0, 0, 0, 255};  // Color del texto: negro

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

                // Renderizar texto
                SDL_Surface *surface = TTF_RenderText_Solid(font, text, textColor);
                if (surface == NULL) {
                    printf("Failed to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
                    continue;
                }

                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture == NULL) {
                    printf("Failed to create texture from surface! SDL Error: %s\n", SDL_GetError());
                    SDL_FreeSurface(surface);
                    continue;
                }

                // Configurar posición del texto dentro de la celda
                SDL_Rect textRect;
                textRect.x = cell.x + cell_size / 2 - surface->w / 2;
                textRect.y = cell.y + cell_size / 2 - surface->h / 2;
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
