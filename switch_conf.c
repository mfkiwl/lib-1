/*
 * Copyright (c) 2015-2018  OscillatorIMP Digital
 * Gwenhael Goavec-Merou <gwenhael.goavec-merou@trabucayre.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
/* memory management */
#include <sys/mman.h>
#include <switch_core/switch_config.h>

int switch_send_conf(char *filename, int input)
{
	int fd_sw = open(filename, O_RDWR);
	if (fd_sw < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return fd_sw;
	}
	printf("configuration switch\n");
	ioctl(fd_sw, SWITCH_SELECT_INPUT, &input);
	close(fd_sw);
	return 0;
}
