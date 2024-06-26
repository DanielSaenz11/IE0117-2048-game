#include "../include/game-logic.h"
#include "../include/movement.h"
#include <stdlib.h>
#include <time.h>

int main() {

    srand(time(NULL));

    char direccion = 'd';

    Game game;
    int game_running = 0;

    game.tamanoTablero = checkSize(&game);

    game_running = init_board(&game);
      
    if (!game_running) {
        return 1;
    }
     
    // addCasillaRandom(&game);
    // addCasillaRandom(&game);
    // addCasillaRandom(&game);
    // addCasillaRandom(&game);
    // addCasillaRandom(&game);
    // addCasillaRandom(&game);
    // addCasillaRandom(&game);
    // addCasillaRandom(&game);
    // addCasillaRandom(&game);

    game.tablero[0][0] = 2;
    game.tablero[1][0] = 2;
    game.tablero[2][0] = 2;
    game.tablero[3][0] = 2;

    printTablero(&game);

    int casillasMovidas = moverCasillas(&game, direccion);

    if (casillasMovidas) {
        fusionarCasillas(&game, direccion);
        //printTablero(&game);
        moverCasillas(&game, direccion);
    }

    printTablero(&game);

    freeTablero(&game);
    
    return 0;
}