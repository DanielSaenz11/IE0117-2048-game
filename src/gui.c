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

void renderizarTablero(Game* game, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Calcula el tamaño de cada celda basado en el tamaño de la ventana y el tablero
    int cellSize = WINDOW_WIDTH / game->tamanoTablero;

    // Si el tamaño del tablero no está dentro del rango válido, mostrar mensaje inicial
    if (game->tamanoTablero < 3 || game->tamanoTablero > 5) {
        TTF_Font* initialFont = TTF_OpenFont("path/to/font.ttf", 24); // Carga otra fuente para el mensaje inicial
        if (!initialFont) {
            printf("Error al cargar la fuente para el mensaje inicial: %s\n", TTF_GetError());
            return;
        }

        SDL_Color initialTextColor = { 255, 255, 255, 255 }; // Texto blanco
        char initialText[] = "Ingrese tamaño del tablero (3-5):"; // Mensaje inicial
        SDL_Surface* initialSurface = TTF_RenderText_Solid(initialFont, initialText, initialTextColor);
        if (initialSurface != NULL) {
            SDL_Texture* initialTexture = SDL_CreateTextureFromSurface(renderer, initialSurface);
            if (initialTexture != NULL) {
                int textW = 0, textH = 0;
                SDL_QueryTexture(initialTexture, NULL, NULL, &textW, &textH);
                SDL_Rect initialRect = { (WINDOW_WIDTH - textW) / 2, (WINDOW_HEIGHT - textH) / 2, textW, textH };

                // Renderiza el texto inicial
                SDL_RenderCopy(renderer, initialTexture, NULL, &initialRect);
                SDL_DestroyTexture(initialTexture);
            }
            SDL_FreeSurface(initialSurface);
        }
        TTF_CloseFont(initialFont);
    } else {
        // Itera sobre el tablero y dibuja cada celda con números negros si el tamaño del tablero es válido
        for (int i = 0; i < game->tamanoTablero; ++i) {
            for (int j = 0; j < game->tamanoTablero; ++j) {
                SDL_Rect cellRect;
                cellRect.x = j * cellSize;
                cellRect.y = i * cellSize;
                cellRect.w = cellSize;
                cellRect.h = cellSize;

                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Color de fondo de la celda
                SDL_RenderFillRect(renderer, &cellRect);

                if (game->tablero[i][j] != 0) {
                    SDL_Color textColor = { 0, 0, 0, 255 }; // Color del texto (negro)
                    char cellText[5];
                    snprintf(cellText, sizeof(cellText), "%d", game->tablero[i][j]);

                    SDL_Surface* textSurface = TTF_RenderText_Solid(font, cellText, textColor);
                    if (textSurface != NULL) {
                        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                        if (textTexture != NULL) {
                            int textW = 0, textH = 0;
                            SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
                            SDL_Rect textRect = {
                                cellRect.x + (cellRect.w - textW) / 2,
                                cellRect.y + (cellRect.h - textH) / 2,
                                textW,
                                textH
                            };
                            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                            SDL_DestroyTexture(textTexture);
                        }
                        SDL_FreeSurface(textSurface);
                    }
                }
            }
        }
    }

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
