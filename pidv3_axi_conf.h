#ifndef PIDV3_AXI_CONF_H
#define PIDV3_AXI_CONF_H

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif
#include <stdint.h>

#include <pidv3_axi_core/pidv3_axi_config.h>

enum k_chan_t {
	KP = 0,
	KI,
	KD
};

enum input_set_t {
	INPUT_SETPOINT_SW= PIDV3_AXI_SETPOINT_SW,
	INPUT_SETPOINT_HW= PIDV3_AXI_SETPOINT_HW,
	INPUT_KP_SW      = PIDV3_AXI_KP_SW,
	INPUT_KP_HW      = PIDV3_AXI_KP_HW,
	INPUT_KI_SW      = PIDV3_AXI_KI_SW,
	INPUT_KI_HW      = PIDV3_AXI_KI_HW,
	INPUT_KD_SW      = PIDV3_AXI_KD_SW,
	INPUT_KD_HW      = PIDV3_AXI_KD_HW,
	INPUT_SIGN_SW    = PIDV3_AXI_SIGN_SW,
	INPUT_SIGN_HW    = PIDV3_AXI_SIGN_HW,
	INPUT_INT_RST_SW = PIDV3_AXI_INT_RST_SW,
	INPUT_INT_RST_HW = PIDV3_AXI_INT_RST_HW,
	INPUT_ALL_HW     = PIDV3_AXI_SETPOINT_HW |
						PIDV3_AXI_KP_HW |
						PIDV3_AXI_KI_HW |
						PIDV3_AXI_KD_HW |
						PIDV3_AXI_SIGN_HW |
						PIDV3_AXI_INT_RST_HW,
	INPUT_ALL_SW     = PIDV3_AXI_SETPOINT_SW |
						PIDV3_AXI_KP_SW |
						PIDV3_AXI_KI_SW |
						PIDV3_AXI_KD_SW |
						PIDV3_AXI_SIGN_SW |
						PIDV3_AXI_INT_RST_SW
};

/* configure all parameters at the same time
 * chanA_val/chanB_val: output value
 * enable_high: set if output enable signal is always high (1) or if
 *	it used in oneshot mode (0)
 * sync_chan: set to 0 for independent access to chanA and chanB, set to 1 to
 * 	update chanA and chanB in a same time
 */
int pidv3_axi_full_conf(const char *filename,
	const int32_t kp_val, const int32_t ki_val, const int32_t kd_val,
	const int32_t setpoint_val,
	const int8_t int_rst, const int8_t sign, const enum input_set_t input);

/* send chan value:
 * chan: must be KP, KI or KD
 * value: value to send
 */
int pidv3_axi_set_kchan(const char *filename, const enum k_chan_t chan, const int32_t val);

/* read chan value:
 * chan: must be KP, KI or KD
 * val: current value
 */
int pidv3_axi_get_kchan(const char *filename, const enum k_chan_t chan, int32_t *val);

/* send setpoint value:
 * value: value to send
 */
int pidv3_axi_set_setpoint(const char *filename, const int32_t val);

/* read setpoint value:
 * return current setpoint value
 */
int iidv3_axi_get_setpoint(const char *filename, int32_t *val);

/* send int_rst:
 * value: value to send
 */
int pidv3_axi_set_int_rst(const char *filename, const int8_t val);

/* send sign
 * value: value to send
 */
int pidv3_set_axi_sign(const char *filename, const int8_t val);

/* read sign
 * current sign value
 */
int pidv3_get_axi_sign(const char *filename, int8_t *val);

/* configure if signal is from AXI or from input
 * input: configuration
 */
int pidv3_axi_set_sw_hw(const char *filename, const enum input_set_t input);

#ifdef __cplusplus
}
#endif

#endif /*PIDV3_AXI_CONF_H*/
