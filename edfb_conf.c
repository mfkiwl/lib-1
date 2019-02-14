/*
 * Copyright (c) 2015-2019  OscillatorIMP Digital
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
#include <edfb_core/edfb_config.h>

#define EDFB_POINT_POS_REG 0x01

int edfb_send_conf(char *filename, int position)
{
	int edfb = open(filename, O_RDWR);
	if (edfb < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return edfb;
	}
	printf("configuration edfb\n");
	ioctl(edfb, EDFB_SET_POINT_POS, &position);
	close(edfb);
	return 0;
}
int edfb_get_conf(char *filename)
{
	int position;
	int edfb = open(filename, O_RDWR);
	if (edfb < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return edfb;
	}
	printf("configuration edfb\n");
	ioctl(edfb, EDFB_GET_POINT_POS, &position);
	close(edfb);
	return 0;
}
