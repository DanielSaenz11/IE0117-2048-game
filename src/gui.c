#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include "../include/gui.h" 
#include "../include/game-logic.h"
#include "../include/movement.h"
#include <SDL2/SDL_ttf.h>


// Funcion para renderizar el tablero con SDL y SDL_ttf
void render_tablero(Game *game, SDL_Renderer *renderer) {

    // Tamano para cada una de las celdas en pixeles
    int cell_size = 100;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Cargar la fuente para el tablero
    TTF_Font *font = TTF_OpenFont("include/NightPumpkind-1GpGv.ttf", 24);  // Ruta y tamano de la fuente 
    if (font == NULL) {
        printf("Error al cargar la fuente del programa: %s\n", TTF_GetError());
    }
    
    SDL_Color textColor = {255, 255, 255};  // Color blanco para el texto

    // Iterar sobre el tablero para renderizar cada celda
    for (int i = 0; i < game->tamanoTablero; i++) {
        for (int j = 0; j < game->tamanoTablero; j++) {
            SDL_Rect cell;
            cell.x = j * cell_size;
            cell.y = i * cell_size;
            cell.w = cell_size - 5;
            cell.h = cell_size - 5;

            // Configurar color y renderizar rectangulo de la celda
            if (game->tablero[i][j] == 0) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  // Color para celdas vacias
            } else {
                SDL_SetRenderDrawColor(renderer, 100 + game->tablero[i][j] * 10, 100 + game->tablero[i][j] * 5, 100 + game->tablero[i][j] * 2, 255);  // Color dependiendo del valor en la celda
            }
            SDL_RenderFillRect(renderer, &cell);

            // Renderizar texto si la celda no esta vacia
            if (game->tablero[i][j] != 0) {
                char text[5];
                sprintf(text, "%d", game->tablero[i][j]); // Agregar valor de la casilla

                // Renderizar texto
                SDL_Surface *surface = TTF_RenderText_Solid(font, text, textColor);
                if (surface == NULL) {
                    printf("Error al renderizar superficie el texto. SDL_ttf Error: %s\n", TTF_GetError());
                    continue;
                }

                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture == NULL) {
                    printf("Error al crear textura de superficie. SDL Error: %s\n", SDL_GetError());
                    SDL_FreeSurface(surface);
                    continue;
                }

                // Configurar posicion del texto dentro de la celda
                SDL_Rect textRect;
                textRect.x = cell.x + (cell_size - surface->w) / 2;
                textRect.y = cell.y + (cell_size - surface->h) / 2;
                textRect.w = surface->w;
                textRect.h = surface->h;

                // Renderizar texto en la pantalla
                SDL_RenderCopy(renderer, texture, NULL, &textRect);

                // Liberar superficie y textura
                SDL_FreeSurface(surface);
                SDL_DestroyTexture(texture);
            }
        }
    }

    // Cerrar la fuente despues de su uso
    TTF_CloseFont(font);

    // Actualizar la pantalla
    SDL_RenderPresent(renderer);
}
