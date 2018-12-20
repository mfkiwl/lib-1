#ifndef FIR_CONF_H
#define FIR_CONF_H

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif

int fir_send_conf(const char *filename, const char *fileCoeff, const int coeffSize);
int fir_send_confSigned(const char *filename, const char *fileCoeff, const int coeffSize);
int fir_read_conf(const char *filename, short *content, const int coeffSize);
/* 
 * fir_MultiSend_StartStop_confSigned
 * send coeff tab for fir based on basename pattern
 * basename : pattern to retrieve /dev/xxx
 * startFir : first fir index
 * nbFir : number of fir to configure
 * fileCoeff
 * coeffSize
 */
int fir_MultiSend_StartStop_confSigned(const char *basename,
	const int startFir, const int nbFir,
	const char *fileCoeff, const int coeffSize);
int fir_MultiSend_confSigned(const char *basename, const int nbFir,
	const char *fileCoeff, const int coeffSize);

#ifdef __cplusplus
}
#endif

#endif /*FIR_CONF_H*/
