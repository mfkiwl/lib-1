/*
 * SPI testing utility (using spidev driver)
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
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

int fpgagen_send_conf(char *filename, int reg, int value)
{
	int fpgagen = open(filename, O_RDWR);
	if (fpgagen < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return fpgagen;
	}

	ioctl(fpgagen, FPGAGEN_SET_REGISTER(reg), &value);
	close(fpgagen);
	return 0;
}

int fpgagen_recv_conf(char *filename, int reg, int *value)
{
	int fpgagen = open(filename, O_RDWR);
	if (fpgagen < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return fpgagen;
	}

	ioctl(fpgagen, FPGAGEN_GET_REGISTER(reg), value);
	close(fpgagen);
	return 0;
}
