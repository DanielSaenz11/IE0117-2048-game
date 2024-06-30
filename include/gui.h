// gui.h

#ifndef GUI_H
#define GUI_H

#include <stdbool.h> // Incluir para el tipo de dato bool
#include <SDL2/SDL.h> // Incluir para SDL_Renderer y otras definiciones de SDL
#include "game-logic.h" // Incluir el archivo de encabezado para Game y otras funciones de lógica de juego
#include "window.h" // Incluir el archivo de encabezado para Window

typedef struct {
    bool quit; // Campo para indicar si el juego debe salir
    // Otros campos necesarios para el estado del juego
} Game;

void renderizarTablero(Game* game, SDL_Renderer* renderer);
void manejarEventos(Game* game);
int createBoardSizeWindow(Window* window, int* boardSize);

#endif /* GUI_H */
