#include "game.h"
#include "util.h"

int main() {
    struct game *arrow_game = initialze_game();
    
    run_game(arrow_game);

    destroy_game(arrow_game);
    return 0;
}