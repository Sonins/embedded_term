BUILDROOT_DIR = ~/buildroot/output
 
KERNEL_DIR = $(BUILDROOT_DIR)/build/linux-custom/
CROSS_COMPILE = $(BUILDROOT_DIR)/host/bin/arm-linux-
CFLAGS = -Wall

TARGET = gpio-driver

obj-m += gpio-driver.o

all : $(TARGET)

clean :
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE)-C $(KERNEL_DIR)M=`pwd` clean

driver :
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE)-C $(KERNEL_DIR)M=`pwd` modules

gpio-driver :
	$(CROSS_COMPILE)gcc gpio-driver.c -o gpio-driver