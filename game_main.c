#include "game.h"
#include "util.h"

#include <time.h>

int main() {
    struct game *arrow_game = initialze_game();

    destroy_game(arrow_game);
    return 0;
}