#include "display.h"
#include "util.h"

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#include "HUNTER_font.h"

// basic i/o with display
void ssd1306_command(int i2c_fd, u_int8_t cmd) {
    u_int8_t buffer[2];
    buffer[0] = (0 << 7) | (0 << 6);  // Co = 0, D/C# = 0
    buffer[1] = cmd;

    if (write(i2c_fd, buffer, 2) != 2) {
        printf("i2c write failed!\n");
    }
}

int ssd1306_init() {
    int i2c_fd;
    I2C_OPEN(i2c_fd, O_RDWR);
    I2C_IOCTL(i2c_fd, I2C_SLAVE, SSD1306_I2C_DEV);

    ssd1306_command(i2c_fd, 0xA8);  // set MUX ratio
    ssd1306_command(i2c_fd, 0x3f);

    ssd1306_command(i2c_fd, 0xD3);  // set display offset
    ssd1306_command(i2c_fd, 0x00);

    ssd1306_command(i2c_fd, 0x40);  // set display start line

    ssd1306_command(i2c_fd, 0xA0);  // set segment re-map
                                    // 0xA1 for vertical inversion

    ssd1306_command(i2c_fd, 0xC0);  // set COM output scan direction
                                    // 0xC8 for horizontal inversion

    ssd1306_command(i2c_fd, 0xDA);  // set COM pins hardware configuration
    ssd1306_command(i2c_fd, 0x12);

    ssd1306_command(i2c_fd, 0x81);  // set contrast control
    ssd1306_command(i2c_fd, 0x7f);  // 0: min, 0xFF: max

    ssd1306_command(i2c_fd, 0xA4);  // disable entire display on

    ssd1306_command(i2c_fd, 0xA6);  // set normal display

    ssd1306_command(i2c_fd, 0xD5);  // set OSC frequency
    ssd1306_command(i2c_fd, 0x80);

    ssd1306_command(i2c_fd, 0x8D);  // enable charge pump regulator
    ssd1306_command(i2c_fd, 0x14);

    ssd1306_command(i2c_fd, 0xAF);  // display on

    return i2c_fd
}

void ssd1306_data(int i2c_fd, const u_int8_t* data, size_t size) {
    u_int8_t* buffer = malloc(size + 1);
    buffer[0] = (0 << 7) | (1 << 6);  // Co = 0, D/C# = 1
    memcpy(buffer + 1, data, size);

    if (write(i2c_fd, buffer, size + 1) != size + 1)
        fprintf(stderr, "i2c data write failed!\n");

    free(buffer);
}

void update_full(int i2c_fd, u_int8_t* data) {
    ssd1306_command(i2c_fd, 0x20);  // addressing mode
    ssd1306_command(i2c_fd, 0x0);   // horizontal addressing mode

    ssd1306_command(i2c_fd, 0x21);  // set column start/end address
    ssd1306_command(i2c_fd, 0);
    ssd1306_command(i2c_fd, S_WIDTH - 1);

    ssd1306_command(i2c_fd, 0x22);  // set page start/end address
    ssd1306_command(i2c_fd, 0);
    ssd1306_command(i2c_fd, S_PAGES);

    ssd1306_data(i2c_fd, data, S_WIDTH * S_PAGES);
}

void update_range(int i2c_fd, u_int8_t* data, struct display_range range) {
    ssd1306_command(i2c_fd, 0x20);  // addressing mode
    ssd1306_command(i2c_fd, 0x0);   // horizontal addressing mode

    ssd1306_command(i2c_fd, 0x21);  // set column start/end address
    ssd1306_command(i2c_fd, range.col[0]);
    ssd1306_command(i2c_fd, range.col[1] - 1);

    ssd1306_command(i2c_fd, 0x22);  // set page start/end address
    ssd1306_command(i2c_fd, range.row[0] / 8);
    ssd1306_command(i2c_fd, (int) ceil((double) range.row[1] / 8));

    int width = range.col[1] - range.col[0];
    int height = (int) ceil((double) range.row[1] / 8) - (range.row[0] / 8);

    ssd1306_data(i2c_fd, data, width * height);
}

void ssd1306_destroy(int i2c_fd) {
    ssd1306_command(i2c_fd, 0xAE); // oled off
    close(i2c_fd);
}


// util function.

struct display_range cursor_to_range(struct point *cursor) {
    struct display_range range;

    if (cursor->x < S_WIDTH / 2) {
        range.col[0] = 0;
        range.col[1] = S_WIDTH;
    } else if (S_WIDTH / 2 <= cursor->x && cursor->x < MAP_WIDTH - S_WIDTH / 2) {
        range.col[0] = cursor->x - S_WIDTH / 2;
        range.col[1] = cursor->x + S_WIDTH / 2;
    } else {
        range.col[0] = MAP_WIDTH - S_WIDTH;
        range.col[1] = MAP_WIDTH;
    }

    if (cursor->y < S_HEIGHT / 2) {
        range.row[0] = 0;
        range.row[1] = S_HEIGHT;
    } else if (S_HEIGHT / 2 <= cursor->y && cursor->y < MAP_HEIGHT - S_HEIGHT / 2) {
        range.row[0] = cursor->y - S_HEIGHT / 2;
        range.row[1] = cursor->y + S_HEIGHT / 2;
    } else {
        range.row[0] = MAP_HEIGHT - S_HEIGHT;
        range.row[1] = MAP_HEIGHT;
    }

    return range;
}

void write_str(u_int8_t *dis, const char *str, int x, int y) {
    for (int i = 0; i < strlen(str); i++) {
        for (int j = 0; j < FONT_WIDTH; j++) {
            dis[to_1dim(x++, y * 8)] = font[str[i] - ' '][j];
            if (!(x < S_WIDTH)) return;
        }
    }
}

int to_1dim(int x, int y) { return (y / 8) * S_WIDTH + x; }