#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#include "util.h"

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

int ssd1306_init();

void update_full(int i2c_fd, uint8_t* data);

void ssd1306_destroy(int i2c_fd);

void update_range_map(int i2c_fd, uint8_t* data, struct box range, int data_width, struct point *display_cursor);

#endif