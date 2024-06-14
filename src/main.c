#include "../include/game-logic.h"

int main() {
    Game game;
    int game_running = 0;

    game.tamanoTablero = checkSize(&game);

    game_running = init_board(&game);
      
    if (!game_running) {
        return 1;
    }
     
    addCasillaRandom(&game);

    printTablero(&game);

    freeTablero(&game);
    
    return 0;
}