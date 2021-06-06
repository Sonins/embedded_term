#include "game.h"

extern struct display_range player_screen;

void aim_phase(struct game *g) {
    uint32_t param_value[3];
    g->player_bow.tense = true;
    do {
        get_gpio_input(gpio_fd, param_value);
        if (param_value[GPIO_UP_INDEX]) {
            rotate_bow_up(&g->player_bow);
        }

        if (param_value[GPIO_DOWN_INDEX]) {
            rotate_bow_down(&g->player_bow);
        }

        draw_player(g);
        display_map(g, &player_screen);
    } while (!param_value[GPIO_FIRE_INDEX]);

    g->player_bow.tense = false;
    draw_player(g);
    display_map(g, &player_screen);
}

void fire_phase(struct game *g) {
    struct arrow _arrow;
    init_arrow(&_arrow, &g->player_bow);
    int score_earned = 0;
    struct display_range range;
    while (!(score_earned = arrow_enemy_colide(&_arrow, &g->enemy)) &&
           !arrow_expired(&_arrow)) {
        arrow_fly(&_arrow);
        draw_arrow(&_arrow, g->entire_map);
        range = cursor_to_range(&_arrow.pos);
        display_map(g, &range);
    }

    if (score_earned) {
        // make arrow fly little more!
        for (int i = 0; i < 2; i++) {
            arrow_fly(&_arrow);
            draw_arrow(&_arrow, g->entire_map);
        }
    }

    g->score += score_earned;
    display_map(g, &range);
    sleep(1);
}

void score_display_phase(int score) {
    display_score(score);

    uint32_t param_value[3];
    do {
        get_gpio_input(gpio_fd, param_value);
    } while (!param_value[GPIO_FIRE_INDEX] && !param_value[GPIO_DOWN_INDEX] &&
             !param_value[GPIO_UP_INDEX]);
}