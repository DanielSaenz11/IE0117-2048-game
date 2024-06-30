#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define BOARD_SIZE 4
#define CELL_SIZE 100

typedef struct {
    int **board;
    int size;
} Game;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE, SDL_WINDOW_SHOWN);
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

    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            SDL_Rect cell;
            cell.x = j * cell_size;
            cell.y = i * cell_size;
            cell.w = cell_size - 5;
            cell.h = cell_size - 5;

            if (game->board[i][j] == 0) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            } else {
                // Aquí puedes ajustar los colores según los valores del tablero
                SDL_SetRenderDrawColor(renderer, 100 + game->board[i][j] * 10, 100 + game->board[i][j] * 5, 100 + game->board[i][j] * 2, 255);
            }

            SDL_RenderFillRect(renderer, &cell);

            // Si deseas añadir texto en las celdas, puedes hacerlo aquí
            // Puedes usar SDL_ttf o dibujar texto directamente sobre la ventana

        }
    }

    SDL_RenderPresent(renderer);
}

int main() {
    srand(time(NULL));

    if (!initSDL()) {
        return 1;
    }

    Game game;
    game.size = BOARD_SIZE;
    game.board = (int **)malloc(game.size * sizeof(int *));
    for (int i = 0; i < game.size; i++) {
        game.board[i] = (int *)malloc(game.size * sizeof(int));
        for (int j = 0; j < game.size; j++) {
            game.board[i][j] = 0; // Inicializar el tablero con ceros
        }
    }

    // Ejemplo: Agregar un número aleatorio al inicio del juego
    int row = rand() % game.size;
    int col = rand() % game.size;
    game.board[row][col] = 2;

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            // Aquí puedes manejar otros eventos como teclas para mover las celdas
        }

        render_board(&game, renderer);
        SDL_Delay(100); // Ajusta el retraso para controlar la velocidad de actualización
    }

    closeSDL();

    // Liberar memoria utilizada por el tablero
    for (int i = 0; i < game.size; i++) {
        free(game.board[i]);
    }
    free(game.board);

    return 0;
}
