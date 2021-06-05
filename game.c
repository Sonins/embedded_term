#include "game.h"

#include "graphic.c"

struct game *initialze_game() {
    i2c_fd = ssd1306_init();
    gpio_fd = gpio_open();

    struct game *g;
    MALLOC(g, sizeof(struct game));

    init_character(&g->player, PLAYER_INIT_POSX, PLAYER_INIT_POSY);
    init_character(&g->enemy, ENEMY_INIT_POSX, ENEMY_INIT_POSY);
    init_bow(&g->player_bow, get_neck_pos(&g->player));

    g->display_cursor.x = 0;
    g->display_cursor.y = MAP_HEIGHT;
    g->score = 0;

    memset(g->entire_map, 0, sizeof(g->entire_map));
    draw_to_map(g);
    struct display_range map_range = point_to_range()
    display_map(g, po);
    return g;
}

void destroy_game(struct game *g) {
    ssd1306_destroy(i2c_fd);
    gpio_close(gpio_fd);
    free(g);
}

bool box_colide(struct point *pt, struct box *b) {
    return (b->lower_x <= pt->x && b->upper_x >= pt->x) &&
           (b->lower_y <= pt->y && b->upper_y >= pt->y);
}

void run_game(struct game *g) {
    for (int i = 0; i < ARROW_AMOUNT; i++) {
        aim_phase(g);
        fire_phase(g);
    }
}


struct display_range cursor_to_range(struct point *cursor) {
    struct display_range range;

    if (cursor->x < S_WIDTH / 2) {
        range.col[0] = 0;
        range.col[1] = S_WIDTH;
    } else if (S_WIDTH / 2 <= cursor->x && cursor->x < MAP_WIDTH - S_WIDTH / 2) {
        range.col[0] = cursor->x - S_WIDTH / 2;
        range.col[1] = cursor->x + S_WIDTH / 2;
    } else {
        range.col[0] = MAP_WIDTH - S_WIDTH;
        range.col[1] = MAP_WIDTH;
    }

    if (cursor->y < S_HEIGHT / 2) {
        range.row[0] = 0;
        range.row[1] = S_HEIGHT;
    } else if (S_HEIGHT / 2 <= cursor->y && cursor->y < MAP_HEIGHT - S_HEIGHT / 2) {
        range.row[0] = cursor->y - S_HEIGHT / 2;
        range.row[1] = cursor->y + S_HEIGHT / 2;
    } else {
        range.row[0] = MAP_HEIGHT - S_HEIGHT;
        range.row[1] = MAP_HEIGHT;
    }

    return range;
}