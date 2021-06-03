#include "arrow-game.h"


void arrow_precede(struct arrow *__arrow) {

}


void arrow_set_initialize(struct arrow_set *set) {
    set->size = 0;
}

void arrow_set_add(struct arrow_set *set, struct arrow *arrow) {
    if (set->size < ARROW_MAX) {
        set->arr[set->size] = arrow;    
        set->size++;
    }
}
