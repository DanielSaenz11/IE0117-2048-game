#include "../include/game-logic.h"
#include "../include/movement.h"
#include <stdlib.h>
#include <time.h>

int main() {

    srand(time(NULL));

    char direccion;

    Game game;
    int game_running = 0;

    
    game.tamanoTablero = checkSize(&game);

    game_running = init_board(&game);
    

    if (!game_running) {
        return 1;
    }

    do {
        addCasillaRandom(&game);

        printTablero(&game);

        direccion = checkTecla();

        if (direccion == 'q') break;

        moverCasillas(&game, direccion);
        fusionarCasillas(&game, direccion);
        moverCasillas(&game, direccion);

    } while ((direccion != 'q') && !(checkPerder(&game)));

    freeTablero(&game);
    
    return 0;
}