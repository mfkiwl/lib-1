/*
 * Copyright (c) 2023  OscillatorIMP Digital
 * Gwenhael Goavec-Merou <gwenhael.goavec-merou@trabucayre.com>
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

#include <lutGene_core/lutGene_config.h>
#include <lutGenerator.h>

int lutGeneratorComplex_fill_ram(const char *filename, const char *fileData, const int len)
{
	int i;
	uint32_t data[len * 2];
	int aa, bb, size = 2 * len * sizeof(uint32_t);
	int dev = open(filename, O_RDWR);
	if (dev < 0) {
		printf("%s: open failed\n", filename);
		return dev;
	}
	printf("configuration\n");

	FILE *data_fd = fopen(fileData, "r");
	if (data_fd == NULL) {
		printf("%s: open failed\n", fileData);
		close(dev);
		return EXIT_FAILURE;
	}

	for (i = 0; i < 2*len; i += 2) {
		fscanf(data_fd, "%d %d ", &aa, &bb);
		data[i]   = aa;
		data[i+1] = bb;
	}

	do {
		i = write(dev, data, size);
		size -= i;
	} while (size > 0);

	fclose(data_fd);
	close(dev);
	return 0;
}

int lutGenerator_set_prescaler(const char *filename, const uint32_t prescaler)
{
	int ret;
	/* open the device to do others operations */
	int dev = open(filename, O_RDWR);
	if (dev < 0) {
		printf("%s: open failed\n", filename);
		return dev;
	}
	ret = ioctl(dev, LUTGENE_SET(LUTGENE_PRESCALER), &prescaler);
	close(dev);
	return ret;
}

int lutGenerator_set_ram_length(const char *filename, const int len)
{
	int ret;
	/* open the device to do others operations */
	int dev = open(filename, O_RDWR);
	if (dev < 0) {
		printf("%s: open failed\n", filename);
		return dev;
	}
	ret = ioctl(dev, LUTGENE_SET(LUTGENE_RAM_LENGTH), &len);
	close(dev);
	return ret;
}

int lutGenerator_enable(const char *filename, const uint8_t enable)
{
	int ret;
	/* open the device to do others operations */
	int dev = open(filename, O_RDWR);
	if (dev < 0) {
		printf("%s: open failed\n", filename);
		return dev;
	}
	ret = ioctl(dev, LUTGENE_SET(LUTGENE_ENABLE), &enable);
	close(dev);
	return ret;
}

int lutGeneratorComplex_configure(const char *filename, const char *fileData,
	const int len, const uint8_t enable, const uint32_t prescaler)
{
	int ret;
	/* fill the RAM with fileData content */
	if ((ret = lutGeneratorComplex_fill_ram(filename, fileData, len)) != 0)
		return ret;

	/* configure prescaler */
	if ((ret = lutGenerator_set_prescaler(filename, prescaler)) != 0)
		return ret;
	/* configure ram_length */
	if ((ret = lutGenerator_set_ram_length(filename, len)) != 0)
		return ret;
	/* enable/disable */
	return lutGenerator_enable(filename, enable);
}
