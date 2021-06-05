#include "game.h"

void aim_phase(struct game *g) {
    struct display_range range = {
        .col[0] = 0,
        .col[1] = S_WIDTH,
        .row[0] = MAP_HEIGHT - S_HEIGHT,
        .row[1] = MAP_HEIGHT};

    uint32_t param_value[3];
    do {
        get_gpio_input(gpio_fd, param_value);
        if (param_value[GPIO_UP_INDEX]) {
            rotate_bow_up(&g->player_bow);
        }

        if (param_value[GPIO_DOWN_INDEX]) {
            rotate_bow_down(&g->player_bow);
        }

        draw_player(g);
        display_map(g, &range);
    } while (!param_value[GPIO_FIRE_INDEX]);

    g->player_bow.tense = false;
    draw_player(g);
    display_map(g);
}

void fire_phase(struct game *g) {
    struct arrow _arrow;
    init_arrow(&_arrow, &g->player_bow);
    int score_earned = 0;
    struct display_range range;
    while (!(score_earned = arrow_enemy_colide(&_arrow, &g->enemy)) &&
           !arrow_expired(&_arrow)) {
        
        arrow_fly(&_arrow);
        range = cursor_to_range(&_arrow.pos);
        display_map(g, &range);
    }
    g->score += score_earned;
    printf("%d\n", g->score);
    sleep(1);
}