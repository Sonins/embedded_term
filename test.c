//#include "graphic.c"

#include <stdbool.h>
#include <stdio.h>

#define BOW_WIDTH 40
#define BOW_HEIGHT 32
#define CHARACTER_WIDTH 24
#define CHARACTER_HEIGHT 48

const unsigned char bow_release[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x02, 0x04,
    0x04, 0x08, 0x10, 0x20, 0xC0, 0x00, 0x00,
    
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x87, 0xF8,
    
    0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x0F,


     0x00, 0x00, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x20, 0x10,
    0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00};

bool access_by_idx(const unsigned char *graphic, int x, int y, int width) {
    unsigned int mask = 1 << (y % 8);
    return !!(graphic[(y / 8) * width + x] & mask);
}

int main() {
    for (int i = 0; i < BOW_HEIGHT; i++) {
        for (int j = 0; j < BOW_WIDTH; j++) {
            if (access_by_idx(bow_release, j, i, BOW_WIDTH))
                printf("#");
            else
                printf("@");
        }
        printf("\n");
    }
    return 0;
}