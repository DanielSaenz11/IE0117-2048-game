#include "../include/window.h"
#include "../include/gui.h"
#include "../include/game-logic.h"
#include "../include/movement.h"
#include <stdbool.h>
#include <SDL2/SDL_ttf.h> // Asegúrate de incluir SDL2_ttf para el manejo de fuentes

// Variable global para el tamaño del tablero
extern int boardSize;

// Variable global para la fuente
TTF_Font* font = NULL;

// Función para inicializar SDL, ventana y cargar recursos necesarios
int initSDLAndWindow(Window* window) {
    if (initSDL(window) != 0) {
        printf("Error al inicializar SDL y la ventana.\n");
        return -1;
    }

    // Inicializar SDL_ttf para cargar fuentes
    if (TTF_Init() != 0) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        return -1;
    }

    // Cargar la fuente desde un archivo TTF
    font = TTF_OpenFont("path_to_your_font.ttf", 28); // Reemplaza con la ruta a tu archivo de fuente y el tamaño deseado
    if (font == NULL) {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        return -1;
    }

    return 0;
}

#include "gui.h"  // Incluir las cabeceras necesarias según la estructura de tu proyecto
#include <SDL2/SDL_ttf.h>

// Función para renderizar el tablero del juego en la ventana
void renderizarTablero(Game* game, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Establecer color de fondo blanco
    SDL_RenderClear(renderer); // Limpiar pantalla

    // Calcular tamaño de cada celda
    int cellSize = WINDOW_WIDTH / game->tamanoTablero;

    // Iterar sobre el tablero y dibujar cada celda
    for (int i = 0; i < game->tamanoTablero; ++i) {
        for (int j = 0; j < game->tamanoTablero; ++j) {
            // Calcular coordenadas de la celda en la ventana
            SDL_Rect cellRect;
            cellRect.x = j * cellSize;
            cellRect.y = i * cellSize;
            cellRect.w = cellSize;
            cellRect.h = cellSize;

            // Dibujar el fondo de la celda
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Color de fondo de la celda
            SDL_RenderFillRect(renderer, &cellRect);

            // Dibujar el contenido de la celda (números u otros elementos del juego)
            if (game->tablero[i][j] != 0) {
                // Convertir el número a cadena de texto
                char cellText[5];
                snprintf(cellText, sizeof(cellText), "%d", game->tablero[i][j]);

                // Crear superficie de texto
                SDL_Color textColor = {0, 0, 0, 255}; // Color negro para el texto
                TTF_Font* font = TTF_OpenFont("path_to_your_font.ttf", TEXT_SIZE); // Cambiar por tu ruta y tamaño de fuente
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, cellText, textColor);
                if (textSurface != NULL) {
                    // Crear textura desde la superficie
                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                    if (textTexture != NULL) {
                        // Dibujar la textura en la celda
                        SDL_RenderCopy(renderer, textTexture, NULL, &cellRect);
                        SDL_DestroyTexture(textTexture); // Liberar textura después de usarla
                    }
                    SDL_FreeSurface(textSurface); // Liberar superficie después de usarla
                }
                TTF_CloseFont(font); // Cerrar la fuente TTF
            }
        }
    }

    SDL_RenderPresent(renderer); // Actualizar ventana con los cambios realizados
}

// Resto del código de gui.c...
