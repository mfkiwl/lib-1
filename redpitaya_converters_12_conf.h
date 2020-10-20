#ifndef REDPITAYA_CONVERTERS_12_CONF_H
#define REDPITAYA_CONVERTERS_12_CONF_H

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif
#include <stdint.h>

#include <redpitaya_converters_12_core/redpitaya_converters_12_config.h>

/* configure spi parameters */

int redpitaya_converters_12_spi_conf(const char *filename,
        const int8_t adc_dac_sel_val, unsigned char conf_addr_val, unsigned char config_val,
        const int8_t conf_en_val);

/* enable external reference pll */

int redpitaya_converters_12_ext_ref_enable(const char *filename, const int8_t pll_en_val);

/* know if the external referencing is active */

int redpitaya_converters_12_get_ref_status(const char *filename, int8_t *pll_ref_status);

#ifdef __cplusplus
}
#endif

#endif /*REDPITAYA_CONVERTERS_12_CONF_H*/
