#ifndef REDPITAYA_CONVERTERS_12_CONF_H
#define REDPITAYA_CONVERTERS_12_CONF_H

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif
#include <stdint.h>

#include <redpitaya_converters_12_core/redpitaya_converters_12_config.h>

enum input_set_t {
	INPUT_CONF_SW= REDPITAYA_CONVERTERS_12_CONF_SW,
	INPUT_CONF_HW= REDPITAYA_CONVERTERS_12_CONF_HW,
	INPUT_ADC_DAC_SEL_SW      = REDPITAYA_CONVERTERS_12_ADC_DAC_SEL_SW,
	INPUT_ADC_DAC_SEL_HW      = REDPITAYA_CONVERTERS_12_ADC_DAC_SEL_HW,
	INPUT_CONF_EN_SW      = REDPITAYA_CONVERTERS_12_CONF_EN_SW,
	INPUT_CONF_EN_HW      = REDPITAYA_CONVERTERS_12_CONF_EN_HW,
	INPUT_PLL_EN_SW      = REDPITAYA_CONVERTERS_12_PLL_EN_SW,
	INPUT_PLL_EN_HW      = REDPITAYA_CONVERTERS_12_PLL_EN_HW,
	INPUT_ALL_HW     = REDPITAYA_CONVERTERS_12_CONF_HW |
						REDPITAYA_CONVERTERS_12_ADC_DAC_SEL_HW |
						REDPITAYA_CONVERTERS_12_CONF_EN_HW|
						REDPITAYA_CONVERTERS_12_PLL_EN_HW,
	INPUT_ALL_SW     = REDPITAYA_CONVERTERS_12_CONF_SW |
						REDPITAYA_CONVERTERS_12_ADC_DAC_SEL_SW |
						REDPITAYA_CONVERTERS_12_CONF_EN_SW|
						REDPITAYA_CONVERTERS_12_PLL_EN_SW
};

/* configure spi parameters
 */

int redpitaya_converters_12_spi_conf(const char *filename,
        const int8_t adc_dac_sel_val, unsigned char conf_addr_val, unsigned char config_val,
        const int8_t conf_en_val);

int redpitaya_converters_12_ext_ref_enable(const char *filename, const int8_t pll_en_val);

#ifdef __cplusplus
}
#endif

#endif /*REDPITAYA_CONVERTERS_12_CONF_H*/
