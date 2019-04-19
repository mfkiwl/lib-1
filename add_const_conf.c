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
#include <add_const_core/add_const_config.h>

int add_const_set_offset(const char *filename, const int64_t offset)
{
	int retval = EXIT_SUCCESS;
	int fd = open(filename, O_RDWR);
	if (fd < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return EXIT_FAILURE;
	}

	retval = EXIT_SUCCESS;
	if (ioctl(fd, ADD_CONST_SET_CONST, &offset) < 0)
		retval = EXIT_FAILURE;
	close(fd);
	return retval;
}

int add_constMulti_set_offset(const char *basename, const int nb_adder, const int64_t *offset)
{
	int i;
	char filename[256];

	for (i=0; i < nb_adder; i++) {
		sprintf(filename, basename, i);
		if (add_const_set_offset(filename, offset[i]) != EXIT_SUCCESS)
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int add_const_get_offset(const char *filename, int64_t *offset)
{
	int retval = EXIT_SUCCESS;
	int fd = open(filename, O_RDWR);
	if (fd < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return EXIT_FAILURE;
	}

	retval = EXIT_SUCCESS;
	if (ioctl(fd, ADD_CONST_GET_CONST, &offset) < 0)
		retval = EXIT_FAILURE;
	close(fd);
	return retval;
}
