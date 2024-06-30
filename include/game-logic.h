#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

// Definición de la estructura del juego
typedef struct {
    int **tablero;      // Matriz para almacenar el tablero
    int tamanoTablero;  // Tamaño del tablero (número de filas/columnas)
    int puntuacion;     // Puntuación actual del jugador
    int quit;           // Indicador para finalizar el juego
} Game;

// Declaraciones de funciones para la lógica del juego
int init_board(Game* game);                     // Inicialización del tablero
void printTablero(Game* game);                  // Función para imprimir el tablero (para debug)
void addCasillaRandom(Game* game);              // Añadir una casilla aleatoria al tablero
int checkPerder(Game* game);                    // Verificar si el jugador ha perdido
void actualizarPuntuacion(Game* game, int puntuacion); // Actualizar la puntuación del jugador
void freeTablero(Game* game);                   // Liberar la memoria del tablero
int moverCasillas(Game* game, char direccion);  // Mover las casillas según la dirección especificada
void fusionarCasillas(Game* game, char direccion); // Fusionar las casillas adyacentes en la dirección especificada

#endif // GAME_LOGIC_H

