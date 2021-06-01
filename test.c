#include <stdio.h>

#include "util.h"

int main() {
    struct point pos = {3, 5};
    struct point center = {0, 0};

    struct point result = rotate(&pos, &center, 90);
    printf("%d %d\n", result.x, result.y);
    return 0;
}