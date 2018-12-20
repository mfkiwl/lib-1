#define all stuffs needed to compile
OUTPUT_DIR=$(BR_DIR)/output
HOST_DIR=$(OUTPUT_DIR)/host

COMPILER_NAME=arm-linux-
CC=$(HOST_DIR)/usr/bin/$(COMPILER_NAME)gcc

PREFIX=$(OUTPUT_DIR)/target/usr/lib

CFLAGS+=-g -W -Wall -I. -I$(OSCIMP_DIGITAL_DRIVER)
LDFLAGS=-lm

SRC= $(wildcard *.c)
OBJS= $(SRC:.c=.o)

LIB_NAME=liboscimp_fpga.so

#distant device ip
IP?=192.168.0.10

all: $(LIB_NAME)

default: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

# $@ left side of :
%.o: %.c %.h
	$(CC) $(CFLAGS) -fpic -o $@ -c $<

clean:
	rm -rf $(OBJS)
	rm -f $(LIB_NAME)
	rm -f *.c~ *.h~ Makefile~

install: all
	cp -f $(LIB_NAME) $(PREFIX)

install_ssh: all
	scp $(LIB_NAME) root@$(IP):/usr/lib

uninstall: clean
	rm -f $(PREFIX)/$(LIB_NAME)

.PHONY: clean install uninstall
