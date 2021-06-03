#include "arrow-game.h"

#include "arrow.c"
#include "bow.c"
#include "character.c"
#include "draw.c"

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
    return g;
}

void destroy_game(struct game *g) {
    ssd1306_destroy(i2c_fd);
    gpio_close(gpio_fd);
    free(g);
}

void draw_to_map(struct game *g) {
    draw_stuff(g->entire_map, character_graphic, CHARACTER_WIDTH,
               CHARACTER_HEIGHT, &g->player.pos);

    draw_stuff(g->entire_map, character_graphic, CHARACTER_WIDTH,
               CHARACTER_HEIGHT, &g->enemy.pos);

    uint8_t *bow_rotation = bow_rotational_graphic(g->player_bow.angle, is_tense(&g->player_bow));
    int max_radius =
        (BOW_WIDTH > BOW_HEIGHT ? BOW_WIDTH - BOW_POS_CENTER_OFFSET_X
                                : BOW_HEIGHT - BOW_POS_CENTER_OFFSET_Y);
    
    struct point bow_draw_pos = {
        .x = max_radius - g->player_bow.center_pos.x,
        .y = max_radius - g->player_bow.center_pos.y
    };
    
    drawover_stuff(g->entire_map, bow_rotation, 2 * max_radius,
                   2*max_radius, &bow_draw_pos);
}

void run_game(struct game *g) {
    uint8_t data[S_WIDTH * S_PAGES];
    for (int y = 0; y < S_PAGES; y++) {
        for (int x = 0; x < S_WIDTH; x++) {
            data[y * S_WIDTH + x] = g->entire_map[y + 64][x];
        }
    }
    update_full(i2c_fd, data);
}