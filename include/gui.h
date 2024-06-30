// gui.h

#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>

// Declaración de variables globales como externas
extern SDL_Window *ventana;
extern SDL_Renderer *renderer;

// Declaración de funciones para la interfaz gráfica
void initSDL();
void renderizarTablero(Game *game);
void manejarEventos(Game *game);

#endif // GUI_H
