#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define BOARD_SIZE_MIN 3
#define BOARD_SIZE_MAX 5
#define CELL_SIZE 100

typedef struct {
    int **tablero; // Doble puntero para tener un array 2D
    int puntuacion;
    int tamanoTablero;
} Game;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, BOARD_SIZE_MIN * CELL_SIZE, BOARD_SIZE_MIN * CELL_SIZE, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void render_board(Game *game, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    int cell_size = CELL_SIZE;

    for (int i = 0; i < game->tamanoTablero; i++) {
        for (int j = 0; j < game->tamanoTablero; j++) {
            SDL_Rect cell;
            cell.x = j * cell_size;
            cell.y = i * cell_size;
            cell.w = cell_size - 5;
            cell.h = cell_size - 5;

            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderFillRect(renderer, &cell);

            if (game->tablero[i][j] != 0) {
                // Colorear la celda según el valor en el tablero
                SDL_Color color;
                color.r = 100 + game->tablero[i][j] * 10;
                color.g = 100 + game->tablero[i][j] * 5;
                color.b = 100 + game->tablero[i][j] * 2;
                color.a = 255;

                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &cell);

                // Renderizar texto en la celda
                char text[5];
                snprintf(text, sizeof(text), "%d", game->tablero[i][j]);

                SDL_Color textColor = { 0, 0, 0, 255 }; // Color del texto
                SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor); // Renderizar superficie de texto
                SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); // Crear textura de texto
                SDL_Rect textRect = { cell.x + cell_size / 2 - textSurface->w / 2, cell.y + cell_size / 2 - textSurface->h / 2, textSurface->w, textSurface->h }; // Posicion del texto
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect); // Copiar el texto en el renderizador
                SDL_FreeSurface(textSurface); // Liberar superficie de texto
                SDL_DestroyTexture(textTexture); // Destruir textura de texto
            }
        }
    }

    SDL_RenderPresent(renderer);
}

int main() {
    srand(time(NULL));

    Game game;
    game.tamanoTablero = BOARD_SIZE_MIN;

    if (!initSDL()) {
        return 1;
    }

    // Inicializar el tablero y agregar las primeras casillas aleatorias
    init_board(&game);
    addCasillaRandom(&game);
    addCasillaRandom(&game);

    int quit = 0;
    SDL_Event e;
    while (!quit && !checkPerder(&game)) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        moverCasillas(&game, 'u');
                        break;
                    case SDLK_DOWN:
                        moverCasillas(&game, 'd');
                        break;
                    case SDLK_LEFT:
                        moverCasillas(&game, 'l');
                        break;
                    case SDLK_RIGHT:
                        moverCasillas(&game, 'r');
                        break;
                }

                addCasillaRandom(&game);
            }
        }

        render_board(&game, renderer);
        SDL_Delay(100);
    }

    closeSDL();
    freeTablero(&game);

    return 0;
}
