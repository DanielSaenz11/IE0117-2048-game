// gui.c
#include "../include/gui.h"

// Variable global para el tamaño del tablero
int boardSize = 0;

// Función para inicializar SDL, ventana y cargar recursos necesarios
int initSDLAndWindow(Window* window) {
    if (initSDL(window) != 0) {
        printf("Error al inicializar SDL y la ventana.\n");
        return -1;
    }

    return 0;
}

// Función para renderizar el juego en la ventana
void renderizarTablero(Game* game, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Establecer color de fondo blanco
    SDL_RenderClear(renderer); // Limpiar el renderizador con el color de fondo

    // Implementar aquí la lógica para renderizar el juego según el estado actual del juego en `game`

    SDL_RenderPresent(renderer); // Mostrar el renderizado en pantalla
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

// Función para crear y gestionar la ventana de selección del tamaño del tablero
int createBoardSizeWindow(Window* window, int* boardSize) {
    SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255); // Establecer color de fondo blanco
    SDL_RenderClear(window->renderer); // Limpiar el renderizador con el color de fondo

    // Implementar aquí la lógica para la ventana de selección del tamaño del tablero
    // Por ejemplo, renderizar texto para instrucciones y capturar la entrada del usuario

    SDL_RenderPresent(window->renderer); // Mostrar el renderizado en pantalla

    return 0; // Retornar el tamaño del tablero seleccionado por el usuario
}

// Función principal del juego
int main(int argc, char* argv[]) {
    Window window;
    Game game;
    game.quit = false; // Inicializar el campo `quit` de `Game`

    if (initSDLAndWindow(&window) != 0) {
        printf("Error al inicializar SDL y la ventana.\n");
        return -1;
    }

    // Bucle de selección de tamaño del tablero
    while (boardSize == 0) {
        manejarEventos(&game); // Manejar eventos de la ventana

        if (createBoardSizeWindow(&window, &boardSize) != 0) {
            printf("Error al crear la ventana de selección del tamaño del tablero.\n");
            break;
        }
    }

    // Bucle principal del juego
    while (!game.quit) {
        manejarEventos(&game); // Manejar eventos del juego

        renderizarTablero(&game, window.renderer); // Renderizar el juego en la ventana
    }

    cleanupWindow(&window); // Limpiar recursos y salir
    return 0;
}
