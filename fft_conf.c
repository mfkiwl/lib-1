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
#include <fft_core/fft_config.h>

int _fft_send_conf(const char *filename, int32_t* coeffs, int size)
{
	int retval = EXIT_FAILURE;
	int i, incr = 0;

	int fft = open(filename, O_RDWR);
	if (fft < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return retval;
	}

	do {
		i = write(fft, coeffs+incr, size* sizeof(int32_t));
		if (i < 0)
			goto err_write;
		i/=sizeof(int32_t);
		size -= i;
		incr += i;
	} while (size > 0);

	retval = EXIT_SUCCESS;

err_write:
	close(fft);
	return retval;
}

int _fft_read_coeff(int32_t *coeffs_tab, const char *fileCoeffRe,
	const char *fileCoeffIm, int coeffSize)
{
	int retval = EXIT_FAILURE;
	int i, aa, size = coeffSize;

	FILE *coeffRe_fd = fopen(fileCoeffRe, "r");
	if (coeffRe_fd == NULL) {
		printf("erreur d'ouverture des coefficients I\n");
		goto err_fdI;
	}
	FILE *coeffIm_fd = fopen(fileCoeffIm, "r");
	if (coeffIm_fd == NULL) {
		printf("erreur d'ouverture des coefficients Q\n");
		goto err_fdQ;
	}
	for (i = 0; i < size; i+=2) {
		fscanf(coeffIm_fd, "%d", &aa);
		coeffs_tab[i] = aa;
		fscanf(coeffRe_fd, "%d", &aa);
		coeffs_tab[i+1] = aa;
	}

	retval = EXIT_SUCCESS;
	fclose(coeffIm_fd);
err_fdQ:
	fclose(coeffRe_fd);
err_fdI:
	return retval;
}

int fft_send_conf(const char *filename, const char *fileCoeffRe, const char *fileCoeffIm,
	const int coeffSize)
{
	int retval = EXIT_FAILURE;
	int size = coeffSize*2;
	int32_t coeffs[size];
	/*int fft = open(filename, O_RDWR);
	if (fft < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return retval;
	}*/
	printf("configuration\n");

	/*FILE *coeffRe_fd = fopen(fileCoeffRe, "r");
	if (coeffRe_fd == NULL) {
		printf("erreur d'ouverture des coefficients I\n");
		goto err_fdI;
	}
	FILE *coeffIm_fd = fopen(fileCoeffIm, "r");
	if (coeffIm_fd == NULL) {
		printf("erreur d'ouverture des coefficients Q\n");
		goto err_fdQ;
	}*/

	/*for (i = 0; i < size; i+=2) {
		fscanf(coeffIm_fd, "%d", &aa);
		coeffs[i] = aa;
		fscanf(coeffRe_fd, "%d", &aa);
		coeffs[i+1] = aa;
	}*/

	if (_fft_read_coeff(coeffs, fileCoeffRe, fileCoeffIm, size) != EXIT_SUCCESS)
		return EXIT_FAILURE;

	if (_fft_send_conf(filename, coeffs, size) != EXIT_SUCCESS)
		goto err_write;
	/* int incr = 0;
	do {
		i = write(fft, coeffs+incr, size* sizeof(int32_t));
		if (i < 0)
			goto err_write;
		i/=sizeof(int32_t);
		size -= i;
		incr += i;
		//printf("plop %d %d %d\n", i, size, incr);
	} while (size > 0); */

	retval = EXIT_SUCCESS;
err_write:
/*	fclose(coeffIm_fd);
err_fdQ:
	fclose(coeffRe_fd);
err_fdI:*/
	//close(fft);
	return retval;

}

int fft_MultiSend_conf(const char *basename, const int nbFFT,
	const char *fileCoeffRe, const char *fileCoeffIm, const int coeffSize)
{
	int i, size = coeffSize*2;
	int32_t coeffs[size];
	char filename[256];

	printf("configuration\n");

	if (_fft_read_coeff(coeffs, fileCoeffRe, fileCoeffIm, size) != EXIT_SUCCESS)
		return EXIT_FAILURE;

	for (i=0; i < nbFFT; i++) {
		sprintf(filename, basename, i);
		if (_fft_send_conf(filename, coeffs, size) != EXIT_SUCCESS)
			return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int fft_get_conf(const char *filename, const char *fileCoeffRe, const char *fileCoeffIm,
	const int coeffSize)
{
	int retval = EXIT_FAILURE;
	int i;
	int size = coeffSize*2;
	int32_t coeffs[size];
	int fft = open(filename, O_RDWR);
	if (fft < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return retval;
	}
	printf("configuration\n");

	FILE *coeffRe_fd = fopen(fileCoeffRe, "w+");
	if (coeffRe_fd == NULL) {
		printf("erreur d'ouverture des coefficients I\n");
		goto err_fdI;
	}
	FILE *coeffIm_fd = fopen(fileCoeffIm, "w+");
	if (coeffIm_fd == NULL) {
		printf("erreur d'ouverture des coefficients Q\n");
		goto err_fdQ;
	}
	
	i = read(fft, coeffs, size* sizeof(int32_t));
	if (i < 0)
		goto err_write;

	for (i = 0; i < size; i+=2) {
		fprintf(coeffIm_fd, "%d\n", coeffs[i]);
		fprintf(coeffRe_fd, "%d\n", coeffs[i+1]);
	}

	retval = EXIT_SUCCESS;
err_write:
	fclose(coeffIm_fd);
err_fdQ:
	fclose(coeffRe_fd);
err_fdI:
	close(fft);
	return retval;

}

int fft_get_test_data(const char *filename, const char *fileData, const int dataSize)
{
	int retval = EXIT_FAILURE;
	int i;
	int size = dataSize;
	int32_t coeffs[size];
	int fft = open(filename, O_RDWR);
	if (fft < 0) {
		printf("erreur d'ouverture de %s\n", filename);
		return retval;
	}
	printf("configuration\n");

	FILE *data_fd = fopen(fileData, "w+");
	if (data_fd == NULL) {
		printf("erreur d'ouverture des coefficients I\n");
		goto err_fdData;
	}
	
	i = read(fft, coeffs, size* sizeof(int32_t));
	if (i < 0)
		goto err_write;

	for (i = 0; i < size; i++) {
		fprintf(data_fd, "%d\n", coeffs[i]);
	}

	retval = EXIT_SUCCESS;
err_write:
	fclose(data_fd);
err_fdData:
	close(fft);
	return retval;

}
