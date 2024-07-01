void renderizarTablero(Game* game, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Calcula el tamaño de cada celda basado en el tamaño de la ventana y el tablero
    int cellSize = WINDOW_WIDTH / game->tamanoTablero;

    // Si el tamaño del tablero no está dentro del rango válido, mostrar mensaje inicial
    if (game->tamanoTablero < 3 || game->tamanoTablero > 5) {
        TTF_Font* initialFont = TTF_OpenFont("path/to/font.ttf", 24); // Carga otra fuente para el mensaje inicial
        if (!initialFont) {
            printf("Error al cargar la fuente para el mensaje inicial: %s\n", TTF_GetError());
            return;
        }

        SDL_Color initialTextColor = { 255, 255, 255, 255 }; // Texto blanco
        char initialText[] = "Ingrese tamaño del tablero (3-5):"; // Mensaje inicial
        SDL_Surface* initialSurface = TTF_RenderText_Solid(initialFont, initialText, initialTextColor);
        if (initialSurface != NULL) {
            SDL_Texture* initialTexture = SDL_CreateTextureFromSurface(renderer, initialSurface);
            if (initialTexture != NULL) {
                int textW = 0, textH = 0;
                SDL_QueryTexture(initialTexture, NULL, NULL, &textW, &textH);
                SDL_Rect initialRect = { (WINDOW_WIDTH - textW) / 2, (WINDOW_HEIGHT - textH) / 2, textW, textH };

                // Renderiza el texto inicial
                SDL_RenderCopy(renderer, initialTexture, NULL, &initialRect);
                SDL_DestroyTexture(initialTexture);
            }
            SDL_FreeSurface(initialSurface);
        }
        TTF_CloseFont(initialFont);
    } else {
        // Itera sobre el tablero y dibuja cada celda con números negros si el tamaño del tablero es válido
        for (int i = 0; i < game->tamanoTablero; ++i) {
            for (int j = 0; j < game->tamanoTablero; ++j) {
                SDL_Rect cellRect;
                cellRect.x = j * cellSize;
                cellRect.y = i * cellSize;
                cellRect.w = cellSize;
                cellRect.h = cellSize;

                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Color de fondo de la celda
                SDL_RenderFillRect(renderer, &cellRect);

                if (game->tablero[i][j] != 0) {
                    SDL_Color textColor = { 0, 0, 0, 255 }; // Color del texto (negro)
                    char cellText[5];
                    snprintf(cellText, sizeof(cellText), "%d", game->tablero[i][j]);

                    SDL_Surface* textSurface = TTF_RenderText_Solid(font, cellText, textColor);
                    if (textSurface != NULL) {
                        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                        if (textTexture != NULL) {
                            int textW = 0, textH = 0;
                            SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
                            SDL_Rect textRect = {
                                cellRect.x + (cellRect.w - textW) / 2,
                                cellRect.y + (cellRect.h - textH) / 2,
                                textW,
                                textH
                            };
                            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                            SDL_DestroyTexture(textTexture);
                        }
                        SDL_FreeSurface(textSurface);
                    }
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
}
