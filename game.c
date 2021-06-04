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
    display_map(g);
    return g;
}

void destroy_game(struct game *g) {
    ssd1306_destroy(i2c_fd);
    gpio_close(gpio_fd);
    free(g);
}

void draw_player(struct game *g) {

    // first, clear the player box.
    struct box update_box = {
        .lower_x = g->player_bow.center_pos.x - g->player_bow.max_radius,
        .upper_x = g->player_bow.center_pos.x + g->player_bow.max_radius,
        .upper_y = g->player_bow.center_pos.y - g->player_bow.max_radius,
        .lower_y = 0};

    int width = update_box.upper_x - update_box.lower_x;
    int height = update_box.upper_y = update_box.lower_y;
    
    unsigned char *clear_mask;
    MALLOC(clear_mask, sizeof(unsigned char *) * width * height);
    memset(clear_mask, 0, sizeof(unsigned char *) * width * height);

    draw_stuff(g->entire_map, clear_mask, width, height, &update_pos);

    free(clear_mask);

    // then draw the player.
    draw_stuff(g->entire_map, character_graphic, CHARACTER_WIDTH,
               CHARACTER_HEIGHT / 8, &g->player.pos);

    uint8_t *bow_rotation = bow_rotational_graphic(&g->player_bow);

    drawover_stuff(g->entire_map, bow_rotation, 2 * g->player_bow.max_radius,
                   (2 * g->player_bow.max_radius) / 8, &g->player_bow.draw_pos);

    free(bow_rotation);
}

void draw_to_map(struct game *g) {
    draw_player(g);

    draw_stuff(g->entire_map, character_graphic, CHARACTER_WIDTH,
               CHARACTER_HEIGHT / 8, &g->enemy.pos);
}

void display_map(struct game *g) {
    uint8_t data[S_WIDTH * S_PAGES];
    for (int y = 0; y < S_PAGES; y++) {
        for (int x = 0; x < S_WIDTH; x++) {
            data[y * S_WIDTH + x] =
                g->entire_map[y + (MAP_HEIGHT_PAGES - S_PAGES)][x];
        }
    }

    for (int i = 0; i < S_WIDTH; i++) {
        data[S_WIDTH + i] = 1;
    }
    update_full(i2c_fd, data);
}

void run_game(struct game *g) { aim_phase(); }