#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "gui.h"
#include "game-logic.h"

// Función para renderizar el tablero con SDL y SDL_ttf
void render_board(Game *game, SDL_Renderer *renderer) {
    int cell_size = 100;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Cargar la fuente
    TTF_Font *font = TTF_OpenFont("include/NightPumpkind-1GpGv.ttf", 24);
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return;
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
                if (!surface) {
                    printf("Failed to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
                    continue;  // Continuar con la siguiente iteración si hay un error
                }

                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (!texture) {
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

// Función para mostrar la ventana de selección de tamaño del tablero
void show_board_size_selection(SDL_Renderer *renderer, int *selected_size) {
    SDL_Event event;
    int quit = 0;

    // Crear una ventana para la selección de tamaño del tablero
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = 400;
    rect.h = 300;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    // Renderizar texto e interactuar con el usuario para seleccionar el tamaño del tablero
    // Aquí se pueden agregar botones, menús desplegables, etc.

    // Ejemplo: Mostrar opciones de tamaño
    TTF_Font *font = TTF_OpenFont("include/NightPumpkind-1GpGv.ttf", 24);
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Color textColor = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Select board size:", textColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = {rect.x + 20, rect.y + 20, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    // Mostrar opciones de tamaño (ejemplo)
    // Ejemplo: Botón para tamaño 3x3
    SDL_Surface *surface_3x3 = TTF_RenderText_Solid(font, "3x3", textColor);
    SDL_Texture *texture_3x3 = SDL_CreateTextureFromSurface(renderer, surface_3x3);
    SDL_Rect rect_3x3 = {rect.x + 50, rect.y + 100, surface_3x3->w, surface_3x3->h};
    SDL_RenderCopy(renderer, texture_3x3, NULL, &rect_3x3);

    // Ejemplo: Botón para tamaño 4x4
    SDL_Surface *surface_4x4 = TTF_RenderText_Solid(font, "4x4", textColor);
    SDL_Texture *texture_4x4 = SDL_CreateTextureFromSurface(renderer, surface_4x4);
    SDL_Rect rect_4x4 = {rect.x + 50, rect.y + 150, surface_4x4->w, surface_4x4->h};
    SDL_RenderCopy(renderer, texture_4x4, NULL, &rect_4x4);

    // Ejemplo: Botón para tamaño 5x5
    SDL_Surface *surface_5x5 = TTF_RenderText_Solid(font, "5x5", textColor);
    SDL_Texture *texture_5x5 = SDL_CreateTextureFromSurface(renderer, surface_5x5);
    SDL_Rect rect_5x5 = {rect.x + 50, rect.y + 200, surface_5x5->w, surface_5x5->h};
    SDL_RenderCopy(renderer, texture_5x5, NULL, &rect_5x5);

    // Actualizar la pantalla
    SDL_RenderPresent(renderer);

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                *selected_size = -1;  // Salir sin seleccionar tamaño
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // Ejemplo: Detectar clic en el botón 3x3
                if (x >= rect_3x3.x && x < rect_3x3.x + rect_3x3.w && y >= rect_3x3.y && y < rect_3x3.y + rect_3x3.h) {
                    *selected_size = 3;  // Asignar tamaño seleccionado
                    quit = 1;  // Salir del bucle
                }
                // Ejemplo: Detectar clic en el botón 4x4
                else if (x >= rect_4x4.x && x < rect_4x4.x + rect_4x4.w && y >= rect_4x4.y && y < rect_4x4.y + rect_4x4.h) {
                    *selected_size = 4;  // Asignar tamaño seleccionado
                    quit = 1;  // Salir del bucle
                }
                // Ejemplo: Detectar clic en el botón 5x5
                else if (x >= rect_5x5.x && x < rect_5x5.x + rect_5x5.w && y >= rect_5x5.y && y < rect_5x5.y + rect_5x5.h) {
                    *selected_size = 5;  // Asignar tamaño seleccionado
                    quit = 1;  // Salir del bucle
                }
            }
        }
    }

    // Liberar recursos
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface_3x3);
    SDL_FreeSurface(surface_4x4);
    SDL_FreeSurface(surface_5x5);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture_3x3);
    SDL_DestroyTexture(texture_4x4
