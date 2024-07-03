#include <SDL2/SDL.h>
#include <stdio.h>
#include "gui.h"
#include "game-logic.h"

int main() {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int board_size = 0;

    // Inicializar SDL y crear ventana y renderer
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("2048 Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Mostrar ventana de selección de tamaño de tablero
    board_size = show_board_size_selection(renderer);

    // Verificar tamaño seleccionado
    if (board_size < 3 || board_size > 5) {
        printf("Invalid board size selected!\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Inicializar juego con el tamaño seleccionado
    Game game;
    initialize_game(&game, board_size);

    // Ciclo principal del juego
    while (!game_over(&game)) {
        // Renderizar el tablero y manejar eventos
        render_board(&game, renderer);
        handle_events(&game);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
