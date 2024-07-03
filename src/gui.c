#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include "gui.h" 
#include "game-logic.h"
#include "movement.h"
#include <SDL2/SDL_ttf.h>

// Función para mostrar el mensaje inicial en la ventana
int show_initial_message(SDL_Renderer *renderer) {
    if (renderer == NULL) {
        printf("Renderer is NULL! Cannot render message.\n");
        return 0;
    }

    // Cargar la fuente
    TTF_Font *font = TTF_OpenFont("include/NightPumpkind-1GpGv.ttf", 24); // Ajustar la ruta y tamaño de la fuente según necesites
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    SDL_Color textColor = {255, 255, 255}; // Color blanco para el texto (puedes ajustar según necesites)
    char message[50];
    sprintf(message, "Enter board size (between 3 and 5): ");

    SDL_Surface *surface = TTF_RenderText_Solid(font, message, textColor);
    if (surface == NULL) {
        printf("Failed to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return 0;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("Failed to create texture from surface! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return 0;
    }

    SDL_Rect textRect;
    textRect.x = 10;
    textRect.y = 10;
    textRect.w = surface->w;
    textRect.h = surface->h;

    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);

    SDL_RenderPresent(renderer);

    return 1;
}

// Función para renderizar el tablero con SDL y SDL_ttf
void render_board(Game *game, SDL_Renderer *renderer) {
    int cell_size = 100;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Cargar la fuente

    TTF_Font *font = TTF_OpenFont("include/NightPumpkind-1GpGv.ttf", 24);  // Ajustar la ruta y tamaño de la fuente según necesites
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    
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
