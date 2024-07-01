#include "../include/window.h"
#include "../include/gui.h"
#include "../include/game-logic.h"
#include "../include/movement.h"
#include <stdbool.h>
#include <SDL2/SDL_ttf.h> // Asegúrate de incluir SDL_ttf.h para manejar texto

// Variable global para el tamaño del tablero
extern int boardSize;

// Variable global para la fuente TTF
TTF_Font* font = NULL;

// Función para inicializar SDL, ventana y cargar recursos necesarios
int initSDLAndWindow(Window* window) {
    if (initSDL(window) != 0) {
        printf("Error al inicializar SDL y la ventana.\n");
        return -1;
    }

    // Inicializar SDL_ttf
    if (TTF_Init() == -1) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        return -1;
    }

    // Cargar la fuente TTF
    font = TTF_OpenFont("path/to/font.ttf", 24); // Asegúrate de tener una fuente en el directorio especificado
    if (!font) {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        return -1;
    }

    return 0;
}

// Función para renderizar el juego en la ventana
void renderizarTablero(Game* game, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // Ejemplo: Dibujar un texto estático en la ventana
    TTF_Font* font = TTF_OpenFont("path/to/your/font.ttf", 24); // Asegúrate de tener una fuente disponible
    SDL_Color textColor = {0, 0, 0, 255}; // Color del texto (negro)
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello, SDL!", textColor); // Texto estático
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Posición del texto en la ventana (centrado)
    int textW = textSurface->w;
    int textH = textSurface->h;
    SDL_Rect textRect = { (WINDOW_WIDTH - textW) / 2, (WINDOW_HEIGHT - textH) / 2, textW, textH };

    // Renderizar el texto en la ventana
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Liberar recursos
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);

    // Actualizar la ventana con los cambios realizados
    SDL_RenderPresent(renderer);
}

// Función para manejar eventos del juego
void manejarEventos(Game* game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game->quit = true;
                break;
            case SDL_KEYDOWN:
                // Manejar teclas según sea necesario
                break;
            default:
                break;
        }
    }
}

// Función principal para coordinar la ejecución del juego
int ejecutarJuego() {
    Window window;
    Game game;

    if (initSDLAndWindow(&window) != 0) {
        printf("Error al inicializar SDL y la ventana.\n");
        return -1;
    }

    // Bucle de selección de tamaño del tablero
    while (boardSize == 0) {
        manejarEventos(&game);

        if (createBoardSizeWindow(&window, &boardSize) != 0) {
            printf("Error al crear la ventana de selección del tamaño del tablero.\n");
            break;
        }
    }

    // Inicializar el juego
    game.tamanoTablero = boardSize;
    game.quit = false;
    game.puntuacion = 0;
    init_board(&game);

    // Bucle principal del juego
    while (!game.quit) {
        manejarEventos(&game);
        renderizarTablero(&game, window.renderer);
    }

    cleanupWindow(&window);
    TTF_CloseFont(font);
    TTF_Quit();
    return 0;
}
