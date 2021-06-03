#include <linux/delay.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/smp.h>
#include <linux/uaccess.h>
#include <linux/types.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");

#define PERIPHERAL_BASE 0x3F000000UL
#define GPIO_BASE (PERIPHERAL_BASE + 0x200000)

void* gpio_ctr = NULL;

void set_gpio_input(void* gpio_ctr, int gpio_nr) {
    int reg_id = gpio_nr / 10;
    int pos = gpio_nr % 10;
    
    u_int32_t* fsel_reg = (u_int32_t*)(gpio_ctr + 0x4 * reg_id);

    u_int32_t fsel_val = *fsel_reg;

    u_int32_t mask = 0x7 << (pos * 3);
    fsel_val = fsel_val & ~mask;

    *fsel_reg = fsel_val;
}

void get_gpio_input_value(void* gpio_ctr, int gpio_nr, int* value) {
    const int GPIO_LEV_OFFSET = 0x34;

    int reg_id = gpio_nr / 32;
    int pos = gpio_nr % 32;

    u_int32_t* level_reg =
        (u_int32_t*)(gpio_ctr + GPIO_LEV_OFFSET + 0x4 * reg_id);
    u_int32_t level = *level_reg & (0x1 << pos);

    *value = level ? 1 : 0;
}

void set_gpio_pullup(void *gpio_ctr, int gpio_nr) {
    const int GPIO_PUD_OFFSET = 0x94;
    const int GPIO_PUDCLK_OFFSET = 0x98;
    const int GPIO_PUD_PULLUP = 0x2;

    int reg_id = gpio_nr / 32;
    int pos = gpio_nr % 32;

    u_int32_t* pud_reg = (u_int32_t*) (gpio_ctr + GPIO_PUD_OFFSET);
    u_int32_t* pudclk_reg = (u_int32_t*) (gpio_ctr + GPIO_PUDCLK_OFFSET + 0x4 * reg_id);

    *pud_reg = GPIO_PUD_PULLUP;
    udelay(1);
    *pudclk_reg = (0x1 << pos);
    udelay(1);
    *pud_reg = 0;
    *pudclk_reg = 0;
}

#define MAJOR_NUM 0
#define DEVICE_NAME "gpiodev"
#define CLASS_NAME "gpiodev_class"

static int majornumber;
static struct class* cRpiKeyClass = NULL;
static struct device* cRpiKeyDevice = NULL;

static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "rpi_key device_open(%p)\n", file);
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "rpi_key device_release(%p)\n", file);
    return 0;
}

long device_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param) {
    
    if (ioctl_num == 100) {
        u_int32_t param_value[3];
        get_gpio_input_value(gpio_ctr, 17, &param_value[0]);
        get_gpio_input_value(gpio_ctr, 27, &param_value[1]);
        get_gpio_input_value(gpio_ctr, 22, &param_value[2]);

        copy_to_user((void*) ioctl_param, (void*) param_value, sizeof(u_int32_t) * 2);

    }
    return 0;
}

struct file_operations gpio_fops = {
    .unlocked_ioctl = device_ioctl,
    .open = device_open,
    .release = device_release,
};

static int __init rpi_key_init(void) {
    majornumber = register_chrdev(MAJOR_NUM, DEVICE_NAME, &gpio_fops);
    cRpiKeyClass = class_create(THIS_MODULE, CLASS_NAME);
    cRpiKeyDevice = device_create(cRpiKeyClass, NULL, MKDEV(majornumber, 0), NULL, DEVICE_NAME);

    gpio_ctr = ioremap(GPIO_BASE, 0x1000);
    set_gpio_input(gpio_ctr, 17);
    set_gpio_input(gpio_ctr, 27);
    set_gpio_input(gpio_ctr, 22);

    set_gpio_pullup(gpio_ctr, 17);
    set_gpio_pullup(gpio_ctr, 27);
    set_gpio_pullup(gpio_ctr, 22);

    return 0;
}

static void __exit rpi_key_exit(void) {
    iounmap(gpio_ctr);

    device_destroy(cRpiKeyClass, MKDEV(majornumber, 0));
    class_unregister(cRpiKeyClass);
    class_destroy(cRpiKeyClass);
    unregister_chrdev(majornumber, DEVICE_NAME);
}

module_init(rpi_key_init);
module_exit(rpi_key_exit);