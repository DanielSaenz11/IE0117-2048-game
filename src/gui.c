#include "../include/gui.h"
#include "../include/game-logic.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Tamaño de cada casilla del juego
#define TILE_SIZE 100

// Definir colores como constantes SDL_Color
const SDL_Color COLOR_BACKGROUND = {34, 49, 63, 255}; // Azul oscuro
const SDL_Color COLOR_TILE = {149, 165, 166, 255};    // Plata
const SDL_Color COLOR_TEXT = {236, 240, 241, 255};    // Blanco

SDL_Window *ventana = NULL;
SDL_Renderer *renderer = NULL;

// Función para dibujar un rectángulo en el renderer
static void dibujarRectangulo(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color color) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    ventana = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TILE_SIZE * 4, TILE_SIZE * 4, SDL_WINDOW_SHOWN);
    if (!ventana) {
        fprintf(stderr, "Error al crear la ventana: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(ventana);
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
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

            // Dibujar el rectángulo de la casilla con un color según su valor
            dibujarRectangulo(renderer, x, y, TILE_SIZE, TILE_SIZE, COLOR_TILE);

            if (valor > 0) {
                // Dibujar el número en el centro de la casilla
                SDL_Color textColor = COLOR_TEXT;
                SDL_Surface *surface = NULL;
                SDL_Texture *texture = NULL;

                char texto[16];
                snprintf(texto, sizeof(texto), "%d", valor);

                // Crear una superficie con el texto (requiere SDL_ttf)
                TTF_Font *font = TTF_OpenFont("ruta/a/tu/fuente.ttf", 24); // Ajusta la ruta y tamaño de la fuente
                if (!font) {
                    fprintf(stderr, "Error al cargar la fuente: %s\n", TTF_GetError());
                    return; // Manejar el error adecuadamente según tu aplicación
                }

                surface = TTF_RenderText_Solid(font, texto, textColor);
                if (!surface) {
                    fprintf(stderr, "Error al crear la superficie de texto: %s\n", TTF_GetError());
                    TTF_CloseFont(font);
                    return;
                }

                // Crear una textura a partir de la superficie
                texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (!texture) {
                    fprintf(stderr, "Error al crear la textura del texto: %s\n", SDL_GetError());
                    SDL_FreeSurface(surface);
                    TTF_CloseFont(font);
                    return;
                }

                // Dibujar la textura centrada en la casilla
                SDL_Rect destRect = {x + TILE_SIZE / 2 - surface->w / 2, y + TILE_SIZE / 2 - surface->h / 2, surface->w, surface->h};
                SDL_RenderCopy(renderer, texture, NULL, &destRect);

                // Liberar la superficie y la textura
                SDL_FreeSurface(surface);
                SDL_DestroyTexture(texture);

                // Cerrar la fuente
                TTF_CloseFont(font);
            }
        }
    }

    // Actualizar la pantalla (renderizar)
    SDL_RenderPresent(renderer);
}
