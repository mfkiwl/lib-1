#define all stuffs needed to compile
OUTPUT_DIR=$(BR_DIR)/output
HOST_DIR=$(OUTPUT_DIR)/host

COMPILER_NAME=arm-linux-
CC=$(HOST_DIR)/usr/bin/$(COMPILER_NAME)gcc
AR=$(HOST_DIR)/usr/bin/$(COMPILER_NAME)ar

PREFIX=$(OUTPUT_DIR)/target/usr/lib

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

install: all
	cp -f $(LIB_NAME).so $(PREFIX)

install_ssh: all
	scp $(LIB_NAME).so root@$(IP):/usr/lib

uninstall: clean
	rm -f $(PREFIX)/$(LIB_NAME).so

.PHONY: clean install uninstall
