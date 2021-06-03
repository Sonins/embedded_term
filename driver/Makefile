BUILDROOT_DIR = $(HOME)/buildroot/output
 
KERNEL_DIR = $(BUILDROOT_DIR)/build/linux-custom/
CROSS_COMPILE = $(BUILDROOT_DIR)/host/bin/arm-linux-
CFLAGS = -Wall

obj-m+=gpio-driver.o

all :
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR) M=$(PWD) modules
	rm .*.cmd *.o *.symvers *.order *.mod *.mod.c

clean :
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR) M=$(PWD) clean
	