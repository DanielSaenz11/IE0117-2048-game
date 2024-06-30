// main.c

#include <stdio.h>
#include "game-logic.h" // Incluir el archivo de encabezado para la lógica del juego
#include "gui.h" // Incluir el archivo de encabezado para la interfaz gráfica

int main(int argc, char* argv[]) {
    Game game;
    int tamanoTablero = 4; // Ejemplo de tamaño de tablero, ajusta según sea necesario

    game.tamanoTablero = tamanoTablero; // Asignar el tamaño del tablero a la estructura Game

    // Inicializar el tablero y otras inicializaciones necesarias
    int game_running = init_board(&game);

    // Bucle principal del juego
    while (!game.quit) {
        // Lógica de manejo de eventos, renderizado y actualización del juego
        manejarEventos(&game); // Manejar eventos del juego
        renderizarTablero(&game, window.renderer); // Renderizar el tablero en la ventana
        // Otras funciones de lógica de juego como mover casillas, verificar perder, etc.
        if (!game_over) {
            moverCasillas(&game, direccion);
            fusionarCasillas(&game, direccion);
            moverCasillas(&game, direccion);
        } else {
            game.quit = true; // Ejemplo de condición para terminar el juego
        }
        SDL_Delay(100); // Pequeña pausa para controlar la velocidad del juego
    }

    // Liberar recursos al salir del juego
    freeTablero(&game);

    return 0;
}
