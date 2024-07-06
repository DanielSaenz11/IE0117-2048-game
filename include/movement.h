#include "game-logic.h"

#ifndef MOVEMENT_H

#define MOVEMENT_H

/*
 * moverCasillas() realiza el movimientos de las casillas en una direccion dada
 * 
 * @param1 Game* game: Puntero al struct game
 * @param2 char direccion: Direccion indicada de movimiento (u|d|r|l)
 * @return casillasMovidas: Numero de casillas movidas durante el llamado de la funcion
 */
int moverCasillas(Game* game, char direccion);

/*
 * fusionarCasillas() se encarga de fusionar las casillas contiguas entre si en
 * la direccion indicada
 * 
 * @param1 Game* game: Puntero al struct game
 * @param2 char direccion: Direccion de fusion indicada
 */
int fusionarCasillas(Game* game, char direccion);

#endif /* MOVEMENT_H */