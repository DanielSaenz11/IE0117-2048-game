// gui.c

#include "gui.h"
#include "game-logic.h"
#include <SDL2/SDL.h>

// Tamaño de cada casilla del juego
#define TILE_SIZE 100

// Colores para las casillas (ejemplo)
#define COLOR_BACKGROUND {34, 49, 63, 255} // Azul oscuro
#define COLOR_TILE {149, 165, 166, 255}     // Plata
#define COLOR_TEXT {236, 240, 241, 255}    // Blanco

// Función para dibujar un rectángulo en el renderer
static void dibujarRectangulo(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color color) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void renderizarTablero(Game *game) {
    // Limpiar el renderer con un color de fondo
    SDL_SetRenderDrawColor(renderer, COLOR_BACKGROUND.r, COLOR_BACKGROUND.g, COLOR_BACKGROUND.b, COLOR_BACKGROUND.a);
    SDL_RenderClear(renderer);

    // Dibujar las casillas del tablero
    for (int i = 0; i < game->tamanoTablero; ++i) {
        for (int j = 0; j < game->tamanoTablero; ++j) {
            int valor = game->tablero[i][j];

            // Calcular la posición de la casilla en la ventana
            int x = j * TILE_SIZE;
            int y = i * TILE_SIZE;

            // Dibujar el rectángulo de la casilla con un color según su valor (ejemplo)
            SDL_Color color = COLOR_TILE;
            if (valor > 0) {
                dibujarRectangulo(renderer, x, y, TILE_SIZE, TILE_SIZE, color);

                // Dibujar el número en el centro de la casilla (ejemplo)
                SDL_Color textColor = COLOR_TEXT;
                SDL_Surface *surface = NULL;
                SDL_Texture *texture = NULL;

                char texto[16];
                snprintf(texto, sizeof(texto), "%d", valor);

                // Crear una superficie con el texto
                surface = TTF_RenderText_Solid(font, texto, textColor);

                // Crear una textura a partir de la superficie
                texture = SDL_CreateTextureFromSurface(renderer, surface);

                // Dibujar la textura centrada en la casilla
                SDL_Rect destRect = {x + TILE_SIZE / 2 - surface->w / 2, y + TILE_SIZE / 2 - surface->h / 2, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, NULL, &destRect);

                // Liberar la superficie y la textura
                SDL_FreeSurface(surface);
                SDL_DestroyTexture(texture);
            }
        }
    }

    // Actualizar la pantalla (renderizar)
    SDL_RenderPresent(renderer);
}
