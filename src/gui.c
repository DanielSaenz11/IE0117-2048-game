#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>
#include "../include/gui.h" 
#include "../include/game-logic.h"
#include "../include/movement.h"
#include <SDL2/SDL_ttf.h>


/*
 * render_tablero() se encarga de renderizar el tablero para mostrar en la ventana
 * los movimientos y acciones del usuario
 * 
 * @param1 Game* game: Puntero al struct que almacena las propiedades del juego
 * @param2 SDL_Renderer* renderer: Puntero al renderer propio de SDL
 */
void render_tablero(Game* game, SDL_Renderer* renderer) {
    // Tamano para cada una de las celdas en pixeles
    int tamano_celda = 100;
    int margen_superior = 50;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Cargar la fuente para el tablero y la puntuacion
    TTF_Font *font = TTF_OpenFont("NightPumpkind-1GpGv.ttf", 24);  // Ruta y tamano de la fuente 
    if (font == NULL) {
        printf("Error al cargar la fuente del programa: %s\n", TTF_GetError());
        return;
    }

    SDL_Color textColor = {0, 0, 0, 255};  // Color negro para el texto de la puntuacion

    // Renderizar la puntuacion
    char puntuacion[20];
    sprintf(puntuacion, "Puntuacion: %d", game->puntuacion);
    SDL_Surface *superficie_puntuacion = TTF_RenderText_Solid(font, puntuacion, textColor);
    if (superficie_puntuacion == NULL) {
        printf("Error al renderizar superficie el texto de la puntuación. SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        SDL_Texture *textura_puntuacion = SDL_CreateTextureFromSurface(renderer, superficie_puntuacion);
        if (textura_puntuacion == NULL) {
            printf("Error al crear textura de superficie de la puntuacion. SDL Error: %s\n", SDL_GetError());
        } else {
            SDL_Rect puntRectangulo;
            puntRectangulo.x = 10;  // Posición en X de la puntuación
            puntRectangulo.y = 10;  // Posición en Y de la puntuación
            puntRectangulo.w = superficie_puntuacion->w;
            puntRectangulo.h = superficie_puntuacion->h;
            SDL_RenderCopy(renderer, textura_puntuacion, NULL, &puntRectangulo);
            SDL_DestroyTexture(textura_puntuacion);
        }
        SDL_FreeSurface(superficie_puntuacion);
    }

    // Iterar sobre el tablero para renderizar cada celda
    for (int i = 0; i < game->tamanoTablero; i++) {
        for (int j = 0; j < game->tamanoTablero; j++) {
            SDL_Rect celda;
            celda.x = j * tamano_celda;
            celda.y = i * tamano_celda + margen_superior;  // Desplazar el tablero hacia abajo para hacer espacio para la puntuación
            celda.w = tamano_celda - 5;
            celda.h = tamano_celda - 5;

            // Configurar color y renderizar rectángulo de la celda
            if (game->tablero[i][j] == 0) {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);  // Color para celdas vacías
            } else {
                SDL_SetRenderDrawColor(renderer, 100 + game->tablero[i][j] * 10, 100 + game->tablero[i][j] * 5, 100 + game->tablero[i][j] * 2, 255);  // Color dependiendo del valor en la celda
            }
            SDL_RenderFillRect(renderer, &celda);

            // Renderizar texto si la celda no está vacía
            if (game->tablero[i][j] != 0) {
                char valorCasilla[5];
                sprintf(valorCasilla, "%d", game->tablero[i][j]); // Agregar valor de la casilla

                // Renderizar texto
                SDL_Surface *superficie_texto = TTF_RenderText_Solid(font, valorCasilla, textColor);
                if (superficie_texto == NULL) {
                    printf("Error al renderizar superficie el texto. SDL_ttf Error: %s\n", TTF_GetError());
                    continue;
                }

                SDL_Texture *textura_texto = SDL_CreateTextureFromSurface(renderer, superficie_texto);
                if (textura_texto == NULL) {
                    printf("Error al crear textura de superficie. SDL Error: %s\n", SDL_GetError());
                    SDL_FreeSurface(superficie_texto);
                    continue;
                }

                // Configurar posición del texto dentro de la celda
                SDL_Rect textRect;
                textRect.x = celda.x + (tamano_celda - superficie_texto->w) / 2;
                textRect.y = celda.y + (tamano_celda - superficie_texto->h) / 2;
                textRect.w = superficie_texto->w;
                textRect.h = superficie_texto->h;

                // Renderizar texto en la pantalla
                SDL_RenderCopy(renderer, textura_texto, NULL, &textRect);

                // Liberar superficie y textura
                SDL_FreeSurface(superficie_texto);
                SDL_DestroyTexture(textura_texto);
            }
        }
    }
    // Cerrar la fuente después de su uso
    TTF_CloseFont(font);

    // Actualizar la pantalla
    SDL_RenderPresent(renderer);
}

