#include "../include/gui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void renderizarTablero(Game* game, SDL_Renderer* renderer) {
    // Limpiar el renderizador con un color de fondo blanco
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Ejemplo: Dibujar un cuadrado rojo en el centro de la ventana
    SDL_Rect rect;
    rect.x = 200;
    rect.y = 200;
    rect.w = 100;
    rect.h = 100;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Rojo
    SDL_RenderFillRect(renderer, &rect);

    // Mostrar el renderizado en pantalla
    SDL_RenderPresent(renderer);
}


    // Ejemplo: Renderizar texto usando SDL_ttf
    TTF_Font* font = TTF_OpenFont("path_to_your_font_file.ttf", 24); // Cargar una fuente TTF (reemplaza con tu propia ruta)
    if (font == NULL) {
        // Manejar error si la fuente no se carga correctamente
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        return;
    }

    SDL_Color textColor = {0, 0, 0, 255}; // Color del texto (negro en este caso)
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello, SDL!", textColor); // Renderizar texto en una superficie
    if (textSurface == NULL) {
        // Manejar error si no se puede renderizar el texto
        printf("Error al renderizar texto: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); // Crear textura desde la superficie de texto
    if (textTexture == NULL) {
        // Manejar error si no se puede crear la textura desde la superficie
        printf("Error al crear la textura del texto: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Posicionar y renderizar la textura del texto
    SDL_Rect textRect;
    textRect.x = 200;
    textRect.y = 200;
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h); // Obtener dimensiones de la textura
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect); // Copiar la textura al renderizador

    // Liberar recursos
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    // Ejemplo: Renderizar el tablero del juego (reemplaza con tu propia lógica de renderizado)

    SDL_RenderPresent(renderer); // Mostrar todos los renderizados en pantalla
}
