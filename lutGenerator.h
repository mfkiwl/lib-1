/*
 * Copyright (c) 2023  OscillatorIMP Digital
 * Gwenhael Goavec-Merou <gwenhael.goavec-merou@trabucayre.com>
 */

#ifndef LUTGENERATOR_CONF_H
#define LUTGENERATOR_CONF_H

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif
#include <stdint.h>

/* \brief sent `fileData` content to the IP
 * \param[in] filename: /dev/xxx
 * \param[in] fileData: sample file must be ASCII to column integer values
 * \param[in] len: number of sample to read/send
 * \return 0 when success, error code (<0) otherwise
 */
int lutGeneratorComplex_fill_ram(const char *filename, const char *fileData,
	const int len);

/* \brief configure `prescaler`
 * \param[in] fileData: /dev/xxx
 * \param[in] prescaler: the prescaler value between 1 and `PRESCALER_MAX`
 * \return 0 when success, error code (<0) otherwise
 */
int lutGenerator_set_prescaler(const char *filename, const uint32_t prescaler);

/* \brief configure ram_length
 * \param[in] fileData: /dev/xxx
 * \param[in] len: number of sample to read before restarting
 * \return 0 when success, error code (<0) otherwise
 */
int lutGenerator_set_ram_length(const char *filename, const int len);

/* \brief enable/disable stream
 * \param[in] fileData: /dev/xxx
 * \param[in] enable: 1 to enable stream, 0 to disable
 * \return 0 when success, error code (<0) otherwise
 */
int lutGenerator_enable(const char *filename, const uint8_t enable);

/* \brief sent `fileData` content to the IP
 * \param[in] filename: /dev/xxx
 * \param[in] fileData: sample file must be ASCII to column integer values
 * \param[in] len: number of sample to read/send
 * \param[in] enable: 1 to enable stream, 0 to disable
 * \param[in] prescaler: the prescaler value between 1 and `PRESCALER_MAX`
 * \return 0 when success, error code (<0) otherwise
 */
int lutGeneratorComplex_configure(const char *filename, const char *fileData,
	const int len, const uint8_t enable, const uint32_t prescaler);

#ifdef __cplusplus
}
#endif

#endif /*LUTGENERATOR_CONF_H*/
