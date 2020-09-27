/*
 * Copyright (c) 2019  OscillatorIMP Digital
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
#include <redpitaya_converters_12_core/redpitaya_converters_12_config.h>
#include <redpitaya_converters_12_conf.h>

int redpitaya_converters_12_spi_conf(const char *filename,
	const int8_t adc_dac_sel_val, unsigned char conf_addr_val, unsigned char config_val,
	int8_t conf_en_val)
{
	//const int32_t conf_val = (conf_addr_val<<8) | (config_val);
	unsigned long conf_val = (conf_addr_val<<8) | (config_val);
	int retval = EXIT_FAILURE;
	int fd = open(filename, O_RDWR);

	if (fd < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return EXIT_FAILURE;
	}

	/* configure spi address */
	if (ioctl(fd, REDPITAYA_CONVERTERS_12_SET(REG_REDPITAYA_CONVERTERS_12_CONF), &conf_val) < 0)
		goto fd_close;
	/* configure select adc/dac */
	if (ioctl(fd, REDPITAYA_CONVERTERS_12_SET(REG_REDPITAYA_CONVERTERS_12_ADC_DAC_SEL), &adc_dac_sel_val) < 0)
		goto fd_close;
	/* configure enable configuration */
	if (ioctl(fd, REDPITAYA_CONVERTERS_12_SET(REG_REDPITAYA_CONVERTERS_12_CONF_EN), &conf_en_val) < 0)
		goto fd_close;

	retval = EXIT_SUCCESS;
fd_close:
	close(fd);
	return retval;
}


int redpitaya_converters_12_ext_ref_enable(const char *filename, int8_t pll_en_val)
{
        int retval = EXIT_FAILURE;
        int fd = open(filename, O_RDWR);

        if (fd < 0) {
                printf("erreur d'ouverture de %s\n", filename);
                return EXIT_FAILURE;
        }

        /* enable external reference clock*/
        if (ioctl(fd, REDPITAYA_CONVERTERS_12_SET(REG_REDPITAYA_CONVERTERS_12_PLL_EN), &pll_en_val) < 0)
                goto fd_close;

        retval = EXIT_SUCCESS;
fd_close:
        close(fd);
        return retval;
}

int __redpitaya_converters_12_set(const char *filename, unsigned long reg, unsigned long val)
{
	int retval = EXIT_FAILURE;
	int fd = open(filename, O_RDWR);
	if (fd < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return EXIT_FAILURE;
	}

	if (ioctl(fd, REDPITAYA_CONVERTERS_12_SET(reg), &val) < 0)
		goto fd_close;

	retval = EXIT_SUCCESS;
fd_close:
	close(fd);
	return retval;
}
