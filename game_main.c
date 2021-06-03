#include "arrow-game.h"
#include "util.h"

int main() {
    struct game *arrow_game = initialze_game();
    
    game_run(arrow_game);

    destroy_game(arrow_game);
    return 0;
}