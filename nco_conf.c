/*
 * Copyright (c) 2015-2018  OscillatorIMP Digital
 * Gwenhael Goavec-Merou <gwenhael.goavec-merou@trabucayre.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 */

#include <math.h>
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
#include <nco_counter_core/nco_counter_config.h>

int nco_counter_send_conf(const char *filename,
		const int freqHz_ref, const double freqHz_out,
		const int accum_size,
		const int offset,
		const char pinc_sw,
		const char poff_sw)
{
	long double step = (long double)freqHz_ref/powl(2,accum_size);
	long double incrf = ((long double)freqHz_out)/step;
	//unsigned int incr = (unsigned int)incrf;
	uint64_t incr = (uint64_t)round(incrf);
	printf("step %Lf incr %lld freqHz_out %lf incrf %Lf\n", step, incr, freqHz_out,
		incrf);
	long double real_freq = freqHz_ref/(powl(2,accum_size)/(long double)incr);
	printf("%Lf\n", real_freq);

	uint64_t ctrl_reg = 0;
	uint64_t offset_reg = offset;
	if (pinc_sw == 1) {
		ctrl_reg = ctrl_reg | CTRL_PINC_SW;
	}
	if (poff_sw == 1) {
		ctrl_reg = ctrl_reg | CTRL_POFF_SW;
	}

	int nco = open(filename, O_RDWR);
	if (nco < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return nco;
	}
	ioctl(nco, NCO_COUNTER_SET(REG_CTRL), &ctrl_reg);
	ioctl(nco, NCO_COUNTER_SET(REG_PINC), &incr);
	ioctl(nco, NCO_COUNTER_SET(REG_POFF), &offset_reg);
	ioctl(nco, NCO_COUNTER_GET(REG_PINC), &incr);
	printf("incr : %Ld\n", incr);
	close(nco);
	return 0;
}
