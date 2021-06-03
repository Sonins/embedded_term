#include "arrow-game.h"

double to_map_y_axis(double y) { return MAP_HEIGHT - y; }

void draw_stuff(uint8_t map[MAP_WIDTH][MAP_HEIGHT_PAGES],
                const unsigned char *graphic, int width, int height,
                struct point *pos) {
    int pos_x = (int)pos->x;
    int pos_y = (int)pos->y;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            map[pos_x + x][pos_y + y] = graphic[y * width + x];
        }
    }
}

void drawover_stuff(uint8_t map[MAP_WIDTH][MAP_HEIGHT_PAGES],
                    const unsigned char *graphic, int width, int height,
                    struct point *pos) {
    int pos_x = (int)pos->x;
    int pos_y = (int)pos->y;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            map[pos_x + x][pos_y + y] |= graphic[y * width + x];
        }
    }
}

void draw_pixel(unsigned char *graphic, int x, int y, int width,
                int height) {
    unsigned int mask = 1 << (y % 8);
    graphic[(y / 8) * width + x] |= mask;
}

bool access_by_idx(const unsigned char *graphic, int x, int y, int width,
                   int height) {
    unsigned int mask = 1 << (y % 8);
    return !!(graphic[(y / 8) * width + x] & mask);
}

uint8_t *bow_rotational_graphic(double bow_angle, bool tense) {
    const unsigned char *bow_graphic;
    if (tense) {
        bow_graphic = bow_tense;
    } else
        bow_graphic = bow_release;

    int max_radius =
        (BOW_WIDTH > BOW_HEIGHT ? BOW_WIDTH - BOW_POS_CENTER_OFFSET_X
                                : BOW_HEIGHT - BOW_POS_CENTER_OFFSET_Y);

    struct point center_moving_offset = {
        .x = max_radius - BOW_POS_CENTER_OFFSET_X,
        .y = max_radius - BOW_POS_CENTER_OFFSET_Y
    };

    uint8_t *bow_box;
    MALLOC(bow_box, (2 * max_radius) * (2 * max_radius) * sizeof(uint8_t));

    struct point center = {.x = 12, .y = 15};

    for (int y = 0; y < BOW_HEIGHT; y++) {
        for (int x = 0; x < BOW_WIDTH; x++) {
            if (access_by_idx(bow_graphic, x, y, BOW_WIDTH, BOW_HEIGHT)) {
                struct point pos = {x, y};
                struct point rotation = rotate(&pos, &center, bow_angle);
                rotation.x += center_moving_offset.x;
                rotation.y += center_moving_offset.y;

                draw_pixel(bow_box, rotation.x, rotation.y, 2 * max_radius, 2 * max_radius);
            }
        }
    }

    return bow_box;
}