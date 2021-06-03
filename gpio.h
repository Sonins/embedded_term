#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>

#define FIRE_GPIO 17
#define UP_GPIO 27
#define DOWN_GPIO 22

#define DRIVER_NAME "/dev/gpiodev"

int gpio_open();

void get_gpio_input(int gpio_fd, uint32_t param_value[3]);

void gpio_close(int gpio_fd);
