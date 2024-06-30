#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

// Dimensiones de la ventana
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Función para renderizar texto en la ventana
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    int text_width = surface->w;
    int text_height = surface->h;
    SDL_FreeSurface(surface);
    SDL_Rect destRect = { x, y, text_width, text_height };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Inicializar SDL_ttf
    if (TTF_Init() < 0) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    // Crear una ventana
    SDL_Window* window = SDL_CreateWindow("Seleccionar Tamaño del Tablero",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Crear un renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Cargar fuente
    TTF_Font* font = TTF_OpenFont("path/to/font.ttf", 24); // Reemplaza con la ruta a tu fuente
    if (font == NULL) {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Variables para manejar la entrada del usuario
    int boardSize = 0;
    int running = 1;
    int textInputActive = 1;
    SDL_StartTextInput();
    char inputText[3] = "";
    SDL_Color textColor = { 255, 255, 255, 255 };

    // Bucle principal
    SDL_Event event;
    while (running) {
        // Manejar eventos
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN && textInputActive) {
                    boardSize = atoi(inputText);
                    if (boardSize >= 3 && boardSize <= 5) {
                        textInputActive = 0; // Dejar de recibir entrada de texto
                        running = 0; // Salir del bucle principal
                    } else {
                        sprintf(inputText, ""); // Resetear entrada si no es válida
                    }
                }
            } else if (event.type == SDL_TEXTINPUT && textInputActive) {
                strcat(inputText, event.text.text);
            }
        }

        // Renderizar
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color de fondo (negro)
        SDL_RenderClear(renderer);

        // Renderizar texto de entrada
        renderText(renderer, font, "Ingrese el tamano del tablero (3-5):", textColor, 50, 50);
        renderText(renderer, font, inputText, textColor, 50, 100);

        // Actualizar la pantalla
        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();

    // Limpiar y salir
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    printf("Tamaño del tablero seleccionado: %d\n", boardSize);

    return 0;
}
