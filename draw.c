#include "game.h"

extern const unsigned char bow_release[];
extern const unsigned char bow_tense[];

double to_map_y_axis(double y) { return MAP_HEIGHT - y; }

void draw_stuff(uint8_t map[MAP_HEIGHT_PAGES][MAP_WIDTH],
                const unsigned char *graphic, int width, int height_page,
                struct point *pos) {

    int pos_x = (int)pos->x;
    int pos_y = (int)pos->y / 8;

    for (int y = 0; y < height_page; y++) {
        for (int x = 0; x < width; x++) {
            map[pos_y + y][pos_x + x] = graphic[y * width + x];
        }
    }
}

void drawover_stuff(uint8_t map[MAP_HEIGHT_PAGES][MAP_WIDTH],
                    const unsigned char *graphic, int width, int height_page,
                    struct point *pos) {
    int pos_x = (int)pos->x;
    int pos_y = (int)pos->y / 8;

    for (int y = 0; y < height_page; y++) {
        for (int x = 0; x < width; x++) {
            map[pos_y + y][pos_x + x] |= graphic[y * width + x];
        }
    }
}

bool access_by_idx(const unsigned char *graphic, int x, int y, int width) {
    unsigned int mask = 1 << (y % 8);
    return !!(graphic[(y / 8) * width + x] & mask);
}

void draw_pixel(unsigned char *graphic, int x, int y, int width,
                bool pixel) {
    unsigned int mask = 1 << (y % 8);
    if (pixel)
        graphic[(y / 8) * width + x] |= mask;
    else {
        mask = ~mask;
        graphic[(y / 8) * width + x] &= mask;
    }
}

uint8_t *bow_rotational_graphic(struct bow *_bow) {
    bool tense = _bow->tense;
    double angle = _bow->angle;
    const unsigned char *bow_graphic;
    if (tense) {
        bow_graphic = bow_tense;
    } else
        bow_graphic = bow_release;

    struct point center_moving_offset = {
        .x = _bow->max_radius - BOW_POS_CENTER_OFFSET_X,
        .y = _bow->max_radius - BOW_POS_CENTER_OFFSET_Y
    };

    uint8_t *bow_box;
    MALLOC(bow_box, (2 * _bow->max_radius) * (2 * _bow->max_radius) * sizeof(uint8_t));

    struct point center = {.x = BOW_POS_CENTER_OFFSET_X + 2, .y = BOW_POS_CENTER_OFFSET_Y};

    for (int y = 0; y < BOW_HEIGHT; y++) {
        for (int x = 0; x < BOW_WIDTH; x++) {
            if (access_by_idx(bow_graphic, x, y, BOW_WIDTH)) {
                struct point pos = {x, y};
                struct point rotation = rotate(&pos, &center, angle);
                rotation.x += center_moving_offset.x;
                rotation.y += center_moving_offset.y;

                draw_pixel(bow_box, rotation.x, rotation.y, 2 * _bow->max_radius, 1);
            }
        }
    }

    return bow_box;
}

void draw_player(struct game *g) {
    // first, clear the player box.
    struct box update_box = {
        .lower_x = g->player_bow.center_pos.x - g->player_bow.max_radius,
        .upper_x = g->player_bow.center_pos.x + g->player_bow.max_radius,
        .upper_y = g->player_bow.center_pos.y - g->player_bow.max_radius,
        .lower_y = 0};

    int width = update_box.upper_x - update_box.lower_x;
    int height = update_box.upper_y - update_box.lower_y;

    unsigned char *clear_mask;
    MALLOC(clear_mask, sizeof(unsigned char *) * width * height);
    memset(clear_mask, 0, sizeof(unsigned char *) * width * height);

    struct point update_pos = {.x = update_box.lower_x,
                               .y = update_box.upper_y};

    draw_stuff(g->entire_map, clear_mask, width, height / 8, &update_pos);

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

void display_map(struct game *g, struct display_range *range) {

    uint8_t data[S_WIDTH * S_PAGES];
    for (int y = range->row[0]; y < range->row[1]; y++) {
        for (int x = range->col[0]; x < range->col[1]; x++) {
            data[(y - range->row[0]) * S_WIDTH + (x - range->col[0])] =
                g->entire_map[y + (MAP_HEIGHT_PAGES - S_PAGES)][x];
        }
    }
    update_full(i2c_fd, data);
}

void draw_arrow(struct arrow *__arrow, uint8_t map[MAP_HEIGHT_PAGES][MAP_WIDTH]) {
    draw_pixel((uint8_t *) map, __arrow->pos.x, __arrow->pos.y, MAP_WIDTH, 1);
}