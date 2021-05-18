#ifndef FFT_CONF_H
#define FFT_CONF_H

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif

int fft_send_conf(const char *filename, const char *fileCoeffRe, const char *fileCoeffIm,
	const int coeffSize);
int fft_MultiSend_conf(const char *basename, const int nbFFT,
	const char *fileCoeffRe, const char *fileCoeffIm, const int coeffSize);
int fft_get_conf(const char *filename, const char *fileCoeffRe, const char *fileCoeffIm,
	const int coeffSize);
int fft_get_test_data(const char *filename, const char *fileData, const int dataSize);

#ifdef __cplusplus
}
#endif

#endif /*FFT_CONF_H*/
