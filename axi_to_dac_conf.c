/*
 * Copyright (c) 2019  OscillatorIMP Digital
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
#include <axi_to_dac_core/axi_to_dac_config.h>
#include <axi_to_dac_conf.h>

int axi_to_dac_full_conf(const char *filename,
	const int32_t chanA_val, const int32_t chanB_val,
	enum enable_high_t enable_high, uint8_t sync_chan)
{

	int retval = EXIT_FAILURE;
	int fd = open(filename, O_RDWR);
	if (fd < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return EXIT_FAILURE;
	}

	/* configure sync */
	if (ioctl(fd, AXI_TO_DAC_SET(AXI_TO_DAC_SYNC_CHAN), &sync_chan) < 0)
		goto fd_close;
	/* configure enable */
	if (ioctl(fd, AXI_TO_DAC_SET(AXI_TO_DAC_EN_HIGH), &enable_high) < 0)
		goto fd_close;
	if (ioctl(fd, AXI_TO_DAC_SET(AXI_TO_DAC_DATA_A), &chanA_val) < 0)
		goto fd_close;
	if (ioctl(fd, AXI_TO_DAC_SET(AXI_TO_DAC_DATA_B), &chanB_val) < 0)
		goto fd_close;

	retval = EXIT_SUCCESS;
fd_close:
	close(fd);
	return retval;
}

int axi_to_dac_set_chan(const char *filename, const enum output_chan_t chan, const int32_t val)
{
	int retval = EXIT_FAILURE;
	int fd = open(filename, O_RDWR);
	if (fd < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return EXIT_FAILURE;
	}

	int reg = (chan == CHANA) ? AXI_TO_DAC_DATA_A : AXI_TO_DAC_DATA_B;
	if (ioctl(fd, AXI_TO_DAC_SET(reg), &val) < 0)
		goto fd_close;

	retval = EXIT_SUCCESS;
fd_close:
	close(fd);
	return retval;
}

int axi_to_dac_conf_enable(const char *filename, const enum enable_high_t enable_high)
{
	int retval = EXIT_FAILURE;
	int fd = open(filename, O_RDWR);
	if (fd < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return EXIT_FAILURE;
	}

	if (ioctl(fd, AXI_TO_DAC_SET(AXI_TO_DAC_EN_HIGH), &enable_high) < 0)
		goto fd_close;

	retval = EXIT_SUCCESS;
fd_close:
	close(fd);
	return retval;
}

int axi_to_dac_conf_sync(const char *filename, const uint8_t sync_chan)
{
	int retval = EXIT_FAILURE;
	int fd = open(filename, O_RDWR);
	if (fd < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return EXIT_FAILURE;
	}

	if (ioctl(fd, AXI_TO_DAC_SET(AXI_TO_DAC_SYNC_CHAN), &sync_chan) < 0)
		goto fd_close;

	retval = EXIT_SUCCESS;
fd_close:
	close(fd);
	return retval;
}
