#include "../include/gui.h"
#include "../include/window.h" // Incluir el archivo de cabecera de window.h
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Declarar variables globales para el tamaño del tablero y la ventana
int boardSize = 4;
Window window;

// Función para inicializar SDL, ventana y cargar recursos necesarios
int initSDLAndWindow() {
    if (initSDL(&window) != 0) {
        printf("Error al inicializar SDL y la ventana.\n");
        return -1;
    }

    return 0;
}

// Función para renderizar el juego en la ventana
void renderizarTablero(Game* game, SDL_Renderer* renderer) {
    // Implementar la lógica para renderizar el tablero según el estado del juego
    // Utilizar SDL_Renderer* renderer para dibujar los elementos del juego
    // Por ejemplo:
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Establecer color de fondo blanco
    SDL_RenderClear(renderer); // Limpiar el renderizador con el color de fondo

    // Ejemplo: Renderizar un cuadrado simple
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = 50;
    rect.h = 50;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Color rojo para el cuadrado
    SDL_RenderFillRect(renderer, &rect); // Dibujar el cuadrado en el renderizador

    // Ejemplo: Renderizar el tablero del juego (reemplazar con tu propia lógica de renderizado)
    
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

// Función principal del juego
int main(int argc, char* argv[]) {
    Game game;
    // Inicializar SDL y la ventana
    if (initSDLAndWindow() != 0) {
        printf("Error al inicializar SDL y la ventana.\n");
        return -1;
    }

    // Bucle principal del juego
    while (!game.quit) {
        manejarEventos(&game); // Manejar eventos del juego

        if (boardSize == 0) {
            if (createBoardSizeWindow(&window, &boardSize) != 0) {
                printf("Error al crear la ventana de selección del tamaño del tablero.\n");
                break;
            }
        } else {
            renderizarTablero(&game, window.renderer); // Renderizar el juego en la ventana
        }
    }

    // Limpiar recursos y salir
    cleanupWindow(&window);
    return 0;
}
