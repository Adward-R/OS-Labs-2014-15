TARGET = P1_3
KDIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)
	obj-m += $(TARGET).o 
default:
	make -C $(KDIR) M=$(PWD) modules
