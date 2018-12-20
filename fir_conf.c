/*
 * Copyright (c) 2015-2018  OscillatorIMP Digital
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
#include <fir_core/fir_config.h>

int fir_send_conf(const char *filename, const char *fileCoeff, const int coeffSize)
{
	int i;
	uint32_t coeffs[coeffSize];
	int aa, size = coeffSize * sizeof(uint32_t);
	int fir = open(filename, O_RDWR);
	if (fir < 0) {
		printf("%s: open failed\n", filename);
		return fir;
	}
	printf("configuration\n");

	FILE *coeff_fd = fopen(fileCoeff, "r");
	if (coeff_fd == NULL) {
		printf("%s: open failed\n", fileCoeff);
		return EXIT_FAILURE;
	}

	for (i = coeffSize-1; i >= 0; i--) {
		fscanf(coeff_fd, "%d", &aa);
		coeffs[i] = aa;
	}

	do {
		i = write(fir, coeffs, size);
		size -= i;
	} while (size > 0);

	fclose(coeff_fd);
	close(fir);
	return 0;

}

int fir_readCoeffSigned(int32_t *coeffTab, const char *fileCoeff, const int coeffSize)
{
	int aa, i;
	FILE *coeff_fd = fopen(fileCoeff, "r");
	if (coeff_fd == NULL) {
		printf("%s: open failed\n", fileCoeff);
		return EXIT_FAILURE;
	}

	for (i = coeffSize-1; i >= 0; i--) {
		fscanf(coeff_fd, "%d", &aa);
		coeffTab[i] = aa;
	}
	fclose(coeff_fd);
	return EXIT_SUCCESS;
}

int fir_send_confSigned(const char *filename, const char *fileCoeff, const int coeffSize)
{
	int32_t coeffs[coeffSize];
	int size = coeffSize * sizeof(int32_t), fir = open(filename, O_RDWR);
	if (fir < 0) {
		printf("%s: open failed\n", filename);
		return fir;
	}
	printf("configuration\n");
	if (fir_readCoeffSigned(coeffs, fileCoeff, coeffSize) == EXIT_FAILURE)
		return EXIT_FAILURE;

	do {
		size -= write(fir, coeffs, size);
	} while (size > 0);

	close(fir);
	return EXIT_SUCCESS;
}

int fir_MultiSend_StartStop_confSigned(const char *basename,
	const int startFir, const int nbFir,
	const char *fileCoeff, const int coeffSize)
{
	int32_t coeffs[coeffSize];
	int i, size, fir;
	char filename[128];
	printf("configuration\n");
	if (fir_readCoeffSigned(coeffs, fileCoeff, coeffSize) == EXIT_FAILURE)
		return EXIT_FAILURE;
	
	for (i=startFir; i < startFir+nbFir; i++) {
		size = coeffSize * sizeof(int32_t);
		sprintf(filename, basename, i);
		fir = open(filename, O_RDWR);
		if (fir < 0) {
			printf("fail to open %s\n", filename);
			return EXIT_FAILURE;
		}

		do {
			size -= write(fir, coeffs, size);
		} while (size > 0);

		close(fir);
	}
	return EXIT_SUCCESS;
}

int fir_MultiSend_confSigned(const char *basename, const int nbFir,
	const char *fileCoeff, const int coeffSize)
{
	return fir_MultiSend_StartStop_confSigned(basename, 0, nbFir, fileCoeff, coeffSize);
}

int fir_read_conf(const char *filename, short *content, const int coeffSize)
{
	int i;
	int aa=0;
	int size = coeffSize;

	int fir = open(filename, O_RDWR);
	if (fir < 0) {
		printf("%s: open failed\n", filename);
		return fir;
	}

	do {
		i = read(fir, content+aa, size);
		size -= i;
		aa+=i;
	} while (size > 0);

	close(fir);
	return 0;
}
