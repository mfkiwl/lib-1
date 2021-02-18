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
#include <pidv3_axi_core/pidv3_axi_config.h>
#include <pidv3_axi_conf.h>

int pidv3_axi_full_conf(const char *filename,
	const int32_t kp_val, const int32_t ki_val, const int32_t kd_val,
	const int32_t setpoint_val,
	const int8_t int_rst_val, const int8_t sign_val, const enum input_set_t input_val)
{

	int retval = EXIT_FAILURE;
	int fd = open(filename, O_RDWR);
	if (fd < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return EXIT_FAILURE;
	}

	/* configure kxx */
	if (ioctl(fd, PIDV3_AXI_SET(REG_PIDV3_AXI_KP), &kp_val) < 0)
		goto fd_close;
	if (ioctl(fd, PIDV3_AXI_SET(REG_PIDV3_AXI_KI), &ki_val) < 0)
		goto fd_close;
	if (ioctl(fd, PIDV3_AXI_SET(REG_PIDV3_AXI_KD), &kd_val) < 0)
		goto fd_close;
	/* configure setpoint */
	if (ioctl(fd, PIDV3_AXI_SET(REG_PIDV3_AXI_SETPOINT), &setpoint_val) < 0)
		goto fd_close;
	/* configure int rst */
	if (ioctl(fd, PIDV3_AXI_SET(REG_PIDV3_AXI_INT_RST), &int_rst_val) < 0)
		goto fd_close;
	/* configure sign */
	if (ioctl(fd, PIDV3_AXI_SET(REG_PIDV3_AXI_SIGN), &sign_val) < 0)
		goto fd_close;
	/* configure if sofware or input */
	if (ioctl(fd, PIDV3_AXI_SET(REG_PIDV3_AXI_INPUT), &input_val) < 0)
		goto fd_close;

	retval = EXIT_SUCCESS;
fd_close:
	close(fd);
	return retval;
}

int __pidv3_axi_set(const char *filename, const int32_t reg, const int32_t val)
{
	int retval = EXIT_FAILURE;
	int fd = open(filename, O_RDWR);
	if (fd < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return EXIT_FAILURE;
	}

	if (ioctl(fd, PIDV3_AXI_SET(reg), &val) < 0)
		goto fd_close;

	retval = EXIT_SUCCESS;
fd_close:
	close(fd);
	return retval;
}

int32_t __pidv3_axi_get(const char *filename, const int32_t reg, int32_t *val)
{
	int retval = EXIT_FAILURE;
	int fd = open(filename, O_RDWR);
	if (fd < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return EXIT_FAILURE;
	}

	if (ioctl(fd, PIDV3_AXI_GET(reg), val) < 0)
		goto fd_close;

	retval = EXIT_SUCCESS;
fd_close:
	close(fd);
	return retval;
}

int pidv3_axi_set_kchan(const char *filename, const enum k_chan_t chan, const int32_t val)
{
	int reg = (chan == KP) ? REG_PIDV3_AXI_KP : ((chan == KI) ? REG_PIDV3_AXI_KI:REG_PIDV3_AXI_KD);
	return __pidv3_axi_set(filename, reg, val);
}

int pidv3_axi_get_kchan(const char *filename, const enum k_chan_t chan, int32_t *val)
{
	int reg = (chan == KP) ? REG_PIDV3_AXI_KP : ((chan == KI) ? REG_PIDV3_AXI_KI:REG_PIDV3_AXI_KD);
	return __pidv3_axi_get(filename, reg, val);
}

int pidv3_axi_set_setpoint(const char *filename, const int32_t val)
{
	return __pidv3_axi_set(filename, REG_PIDV3_AXI_SETPOINT, val);
}

int pidv3_axi_get_setpoint(const char *filename, int32_t *val)
{
	return __pidv3_axi_get(filename, REG_PIDV3_AXI_SETPOINT, val);
}

int pidv3_axi_set_int_rst(const char *filename, const int8_t val)
{
	return __pidv3_axi_set(filename, REG_PIDV3_AXI_INT_RST, val);
}

int pidv3_axi_set_sign(const char *filename, const int8_t val)
{
	return __pidv3_axi_set(filename, REG_PIDV3_AXI_SIGN, val);
}

int pidv3_get_axi_sign(const char *filename, int8_t *val)
{
	int32_t v;
	int ret = __pidv3_axi_get(filename, REG_PIDV3_AXI_SIGN, &v);
	*val = v;
	return ret;
}

int pidv3_axi_set_sw_hw(const char *filename, const enum input_set_t input)
{
	return __pidv3_axi_set(filename, REG_PIDV3_AXI_INPUT, input);
}
