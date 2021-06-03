#include "gpio.h"

int gpio_open() {
    int gpio_fd = open(DRIVER_NAME, O_RDWR);

    if (gpio_fd < 0) {
        fprintf(stderr, "Cannot open device\n");
        exit(1);
    }

    return gpio_fd;
}

void get_gpio_input(int gpio_fd, uint32_t param_value[3]) {
    int res = ioctl(gpio_fd, 100, param_value);

    if (res < 0) {
        fprintf(stderr, "Cannot ioctl to gpio device\n");
        exit(1);
    }
}

void gpio_close(int gpio_fd) {
    close(gpio_fd);
}