/*
 * Copyright (c) 2019  OscillatorIMP Digital
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
#include <fpgagen_core/fpgagen_config.h>
#include <utils_conf.h>

#define SHIFT_VAL_REG (1 << 2)

int shifter_set(char *filename, int shift)
{
	int fd_sw = open(filename, O_RDWR);
	if (fd_sw < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return fd_sw;
	}

	ioctl(fd_sw, FPGAGEN_SET_REGISTER(SHIFT_VAL_REG), &shift);
	close(fd_sw);
	return 0;
}

int shifter_get(char *filename, int *shift)
{
	int fd_sw = open(filename, O_RDWR);
	if (fd_sw < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return fd_sw;
	}

	ioctl(fd_sw, FPGAGEN_GET_REGISTER(SHIFT_VAL_REG), &shift);
	close(fd_sw);
	return 0;
}
