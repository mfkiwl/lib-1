#ifndef AXI_TO_DAC_CONF_H
#define AXI_TO_DAC_CONF_H

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif
#include <stdint.h>

#include <axi_to_dac_core/axi_to_dac_config.h>

enum output_chan_t {
	CHANA = 0,
	CHANB
};

enum enable_high_t {
	CHANA_ALWAYS_HIGH = AXI_TO_DAC_DATAA_EN_HIGH,
	CHANB_ALWAYS_HIGH = AXI_TO_DAC_DATAB_EN_HIGH,
	BOTH_ALWAYS_HIGH = AXI_TO_DAC_BOTH_EN_HIGH
};

/* configure all parameters at the same time
 * chanA_val/chanB_val: output value
 * enable_high: set if output enable signal is always high (1) or if
 *	it used in oneshot mode (0)
 * sync_chan: set to 0 for independent access to chanA and chanB, set to 1 to
 * 	update chanA and chanB in a same time
 */
int axi_to_dac_full_conf(const char *filename,
	const int32_t chanA_val, const int32_t chanB_val,
	const enum enable_high_t enable_high, const uint8_t sync_chan);

/* send chan value:
 * chan: must be CHANA or CHANB
 * value: value to send
 */
int axi_to_dac_set_chan(const char *filename, const enum output_chan_t chan, const int32_t val);

/* configure enable behavior
 * enable_high: set to 0 for oneshot mode, set to 1 to have enable always high
 */
int axi_to_dac_conf_enable(const char *filename, const enum enable_high_t enable_high);

/* configure channel update
 * sync_chan: set to 0 for independant channel update, set to 1 to update
 * channel in the same time
 */
int axi_to_dac_conf_sync(const char *filename, const uint8_t sync_chan);

#ifdef __cplusplus
}
#endif

#endif /*AXI_TO_DAC_CONF_H*/
