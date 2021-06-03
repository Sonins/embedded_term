#include "graphic.h"
#include "util.h"

#include <stdint.h>

#ifndef DISPLAY_H
#define DISPLAY_H

#define I2C_DEV "/dev/i2c-1"
#define SSD1306_I2C_DEV 0x3C

#define S_WIDTH 128
#define S_HEIGHT 64
#define S_PAGES (S_HEIGHT / 8)

#define FONT_WIDTH 8

#define I2C_OPEN(fd, of)                         \
    if ((fd = open(I2C_DEV, of)) < 0) {          \
        fprintf(stderr, "err opening device\n"); \
        exit(1);                                 \
    }

#define I2C_IOCTL(fd, m, dev)                               \
    if (ioctl(fd, m, dev) < 0) {                            \
        fprintf(stderr, "err setting i2c slave address\n"); \
        exit(1);                                            \
    }

struct display_range {
    int row[2];
    int col[2];
};

void ssd1306_init();

void update_full(uint8_t* data);

void ssd1306_destroy();

struct display_range cursor_to_range(struct point cursor);

#endif