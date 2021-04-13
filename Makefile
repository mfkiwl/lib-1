#define all stuffs needed to compile
OUTPUT_DIR=$(BR_DIR)/output
HOST_DIR=$(OUTPUT_DIR)/host

COMPILER_NAME=arm-linux-
CC=$(HOST_DIR)/usr/bin/$(COMPILER_NAME)gcc
AR=$(HOST_DIR)/usr/bin/$(COMPILER_NAME)ar

PREFIX=$(OUTPUT_DIR)/target/usr/lib

PYTHON_ENABLED=$(shell grep '^BR2_PACKAGE_PYTHON3=' $(BR_DIR)/.config | cut -d= -f2)
ifeq ($(PYTHON_ENABLED),y)
PYTHON_VERS=$(shell grep "^PYTHON3_VERSION_MAJOR" $(BR_DIR)/package/python3/python3.mk | \
	cut -d= -f2 | sed 's/[[:space:]]*//g')
endif

CFLAGS+=-g -W -Wall -I. -I$(OSCIMP_DIGITAL_DRIVER)
LDFLAGS=-lm

SRC= $(wildcard *.c)
OBJS= $(SRC:.c=.o)

LIB_NAME=liboscimp_fpga

#distant device ip
IP?=192.168.0.10

all: $(LIB_NAME).so $(LIB_NAME)_static.a

$(LIB_NAME).so: $(OBJS)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

$(LIB_NAME)_static.a: $(OBJS)
	$(AR) rcs -o $@ $^

# $@ left side of :
%.o: %.c %.h
	$(CC) $(CFLAGS) -fpic -o $@ -c $<

clean:
	rm -rf $(OBJS)
	rm -f $(LIB_NAME).so
	rm -f $(LIB_NAME)_static.a
	rm -f *.c~ *.h~ Makefile~


ifeq ($(PYTHON_ENABLED),n)
install: all
	cp -f $(LIB_NAME).so $(PREFIX)
install_ssh: all
	scp $(LIB_NAME).so root@$(IP):/usr/lib
else
install: all
	cp -f $(LIB_NAME).so $(PREFIX)
	cp -f $(LIB_NAME).py $(PREFIX)/python$(PYTHON_VERS)/site-packages
install_ssh: all
	scp $(LIB_NAME).so root@$(IP):/usr/lib
	scp $(LIB_NAME).py root@$(IP):/usr/lib/python$(PYTHON_VERS)/site-packages
endif

uninstall: clean
	rm -f $(PREFIX)/$(LIB_NAME).so

.PHONY: clean install uninstall
