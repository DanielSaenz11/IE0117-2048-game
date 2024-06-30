#include "../include/window.h"
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TEXT_SIZE 30

int initSDL(Window* window) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }

    window->window = SDL_CreateWindow("Seleccionar Tamaño del Tablero",
                                      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                      WINDOW_WIDTH, WINDOW_HEIGHT,
                                      SDL_WINDOW_SHOWN);
    if (window->window == NULL) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window->window);
        SDL_Quit();
        return -1;
    }

    if (TTF_Init() < 0) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        SDL_DestroyRenderer(window->renderer);
        SDL_DestroyWindow(window->window);
        SDL_Quit();
        return -1;
    }

    return 0;
}

int createBoardSizeWindow(Window* window, int* boardSize) {
    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255); // Color de fondo blanco
    SDL_RenderClear(window->renderer);

    TTF_Font* font = TTF_OpenFont("path_to_your_font_file.ttf", TEXT_SIZE); // Cambiar por tu propia ruta y tamaño de fuente
    if (font == NULL) {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        return -1;
    }

    SDL_Color textColor = {0, 0, 0, 255}; // Color negro para el texto

    SDL_Rect textRect;
    textRect.x = 50;
    textRect.y = 50;
    textRect.w = 300;
    textRect.h = TEXT_SIZE + 10; // Altura del rectángulo de texto

    SDL_Surface* textSurface = NULL;
    SDL_Texture* textTexture = NULL;

    int inputDone = 0;
    SDL_Event event;
    char inputText[16] = ""; // Buffer para el texto de entrada
    SDL_StartTextInput(); // Habilitar la entrada de texto

    while (!inputDone) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                inputDone = 1;
                *boardSize = -1; // Marcar como tamaño inválido (salida forzada)
            } else if (event.type == SDL_TEXTINPUT) {
                strcat(inputText, event.text.text);
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    *boardSize = atoi(inputText); // Convertir entrada a entero
                    inputDone = 1; // Salir del bucle
                } else if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0) {
                    inputText[strlen(inputText) - 1] = '\0'; // Borrar último carácter
                }
            }
        }

        SDL_RenderClear(window->renderer);
        textSurface = TTF_RenderText_Solid(font, inputText, textColor); // Renderizar texto en superficie
        if (textSurface != NULL) {
            textTexture = SDL_CreateTextureFromSurface(window->renderer, textSurface); // Crear textura desde la superficie
            SDL_RenderCopy(window->renderer, textTexture, NULL, &textRect); // Renderizar textura en el renderizador
            SDL_FreeSurface(textSurface); // Liberar superficie
            SDL_DestroyTexture(textTexture); // Liberar textura
        }

        SDL_RenderPresent(window->renderer); // Mostrar renderizado en pantalla
    }

    SDL_StopTextInput(); // Deshabilitar la entrada de texto
    TTF_CloseFont(font); // Cerrar fuente TTF

    return 0;
}

void cleanupWindow(Window* window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    TTF_Quit();
    SDL_Quit();
}
