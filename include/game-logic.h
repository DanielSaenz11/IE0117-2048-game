#ifndef GAME_LOGIC_H

#define GAME_LOGIC_H

typedef struct Game {
    int **tablero; // Doble puntero para tener un array 2D
    int puntuacion;
    int tamanoTablero;
} Game;

typedef enum {
    NULL_POINTER = -1,
    BAD_MEMORY_ALLOCATION = -2
} ErrorCode;

/*
 * checkSize() verifica el que el input del usuario sea un entero
 * en el rango establecido
 * 
 * @return numero: Numero entero entre 3-5
*/
int checkSize();

/*
 * checkTecla() valida la entrada de teclas de movimiento por parte del usuario (debugging)
 * 
 * @return char direccion: caracter de direccion valido  
 */
char checkTecla();

/*
 * init_board() reserva la memoria dinamica para el tablero
 * @param Game* game: Puntero al struct game
 * @return estadoReservacionMemoria (****** Pendiente *******)
*/
int init_board(Game* game);

/*
 * printTablero(Game* game) imprime el tablero en la terminal (DEBUGGING)
 * 
 * @param Game* game: Puntero al struct game
 */
void printTablero(Game* game); // Terminal debugging

/*
 * addCasillaRandom() anade una casilla nueva entre las casillas vacias
 * @param Game* game: Puntero al struct game
 */
void addCasillaRandom(Game* game);

/*
 * checkPerder() verifica si no hay movimientos disponibles
 * 
 * @param Game* game: Puntero al struct game
 * @return 1: Perdio
 * @return 0: No ha perdido
 */
int checkPerder(Game* game);


/*
 * checkVictoria() verifica si una casilla tiene el valor de 2048
 * 
 * @param Game* game: Puntero al struct game
 * @return int esGanador: 1 si es ganador | 0 si perdio
 */
int checkVictoria(Game* game);

/*
 * actualizarPuntuacion() cambia el valor de la variable puntuacion con el valor de fusion
 * 
 * @param1 Game* game: Puntero al struct game
 * @param2 int puntuacion: Valor de fusion para cambiar la puntuacion
 */
void actualizarPuntuacion(Game* game, int puntuacion);

/*
 * freeTablero() libera la memoria dinamica reservada para el tablero
 * 
 * @param1 Game* game: Puntero al struct game
 */
void freeTablero(Game* game);

#endif /* GAME_LOGIC_H */

