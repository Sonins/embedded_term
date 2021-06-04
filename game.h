#ifndef ARROW_GAME_H
#define ARROW_GAME_H

#define MAP_WIDTH 256
#define MAP_HEIGHT 128
#define MAP_HEIGHT_PAGES (MAP_HEIGHT / 8)

#define GPIO_FIRE_INDEX 0
#define GPIO_UP_INDEX 1
#define GPIO_DOWN_INDEX 2

#define ARROW_FALL_SPEED .1
#define ARROW_MAX 256
#define ARROW_LENGTH 5

#define BOW_ANGLE_CHANGE_RATE 0.5
#define BOW_MAX_ANGLE 90
#define BOW_MIN_ANGLE 0
#define BOW_START_ANGLE 30
#define BOW_WIDTH 40
#define BOW_HEIGHT 32
#define BOW_POS_CENTER_OFFSET_X 12
#define BOW_POS_CENTER_OFFSET_Y 12

#define CHARACTER_WIDTH 24
#define CHARACTER_HEIGHT 48

#define PLAYER_INIT_POSX 10
#define PLAYER_INIT_POSY MAP_HEIGHT - CHARACTER_HEIGHT

#define ENEMY_INIT_POSX 200
#define ENEMY_INIT_POSY MAP_HEIGHT - CHARACTER_HEIGHT

#define TO_DISPLAY_Y(y) \
    MAP_HEIGHT - y

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "display.h"
#include "gpio.h"
#include "util.h"

struct arrow {
    double arrow_angle;
    double power_x;
    double power_y;
    struct point pos;
    struct point vect;
};

struct bow {
    double angle;
    struct point center_pos;
    struct point pos;
    bool tense;
};

struct box {
// box declared by lower left and upper right.
    int lower_x;
    int lower_y;
    int upper_x;
    int upper_y;
};

struct character {
// position will be upper left of character
    struct point pos;
    struct box head_box;
    struct box body_box;
};

struct game {
    uint8_t entire_map[MAP_HEIGHT_PAGES][MAP_WIDTH];
    struct character player;
    struct character enemy;
    struct bow player_bow;
    struct point display_cursor;
    int score;
};

// global
int i2c_fd;
int gpio_fd;

// arrow.c proto
void arrow_precede(struct arrow *__arrow);

// bow.c proto
void rotate_bow_up(struct bow *b);

void rotate_bow_down(struct bow *b);

void init_bow(struct bow *b, struct point center_pos);

bool is_tense(struct bow *b);

bool is_release(struct bow *b);

// character.c proto
struct point get_neck_pos(struct character *ch);

void init_character(struct character *ch, int posx, int posy);

// draw.c proto
void draw_stuff(uint8_t map[MAP_HEIGHT_PAGES][MAP_WIDTH],
                const unsigned char *graphic, int width, int height,
                struct point *pos);

void drawover_stuff(uint8_t map[MAP_HEIGHT_PAGES][MAP_WIDTH],
                    const unsigned char *graphic, int width, int height,
                    struct point *pos);

uint8_t *bow_rotational_graphic(struct bow *_bow);

// game.c prto
void run_game(struct game *);

struct game *initialze_game();

void destroy_game(struct game *g);

void draw_to_map(struct game *g);

struct display_range cursor_to_range(struct point *cursor);

void display_map(struct game *g);

#endif