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

// Función para renderizar el juego en la ventana
void renderizarTablero(Game* game, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color de fondo blanco
    SDL_RenderClear(renderer); // Limpiar la pantalla

    // Calcula el tamaño de cada celda basado en el tamaño de la ventana y el tablero
    int cellSize = WINDOW_WIDTH / game->tamanoTablero;

    // Itera sobre el tablero y dibuja cada celda
    for (int i = 0; i < game->tamanoTablero; ++i) {
        for (int j = 0; j < game->tamanoTablero; ++j) {
            // Calcula las coordenadas de la celda en la ventana
            SDL_Rect cellRect;
            cellRect.x = j * cellSize;
            cellRect.y = i * cellSize;
            cellRect.w = cellSize;
            cellRect.h = cellSize;

            // Dibuja el fondo de la celda
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Color de fondo de la celda
            SDL_RenderFillRect(renderer, &cellRect);

            // Dibuja el contenido de la celda (números u otros elementos del juego)
            if (game->tablero[i][j] != 0) {
                // Convierte el número a cadena
                char cellText[5];
                snprintf(cellText, sizeof(cellText), "%d", game->tablero[i][j]);

                // Crea una superficie de texto
                SDL_Color textColor = { 0, 0, 0, 255 }; // Color del texto (negro)
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, cellText, textColor);
                if (textSurface != NULL) {
                    // Crea una textura desde la superficie
                    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                    if (textTexture != NULL) {
                        // Dibuja la textura en la celda
                        SDL_RenderCopy(renderer, textTexture, NULL, &cellRect);
                        SDL_DestroyTexture(textTexture); // Libera la textura después de usarla
                    }
                    SDL_FreeSurface(textSurface); // Libera la superficie después de usarla
                }
            }
        }
    }

    // Actualiza la ventana con los cambios realizados
    SDL_RenderPresent(renderer);
}

// Resto del código de gui.c...
