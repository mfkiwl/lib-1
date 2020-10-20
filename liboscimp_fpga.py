import time
import ctypes
from ctypes import *
lib = ctypes.CDLL('/usr/lib/liboscimp_fpga.so')

def add_const_set_offset(filename, offset):
	file = ctypes.create_string_buffer(str.encode(filename))
	my_val = c_longlong(offset)
	lib.add_const_set_offset(file, my_val)

def add_constMulti_set_offset(basename, nb_adder, offset):
	lib.add_constMulti_set_offset(basename, nb_adder, offset)

def add_const_get_offset(filename):
	file = ctypes.create_string_buffer(str.encode(filename))
	my_val = c_longlong()
	ret_val = lib.add_const_get_offset(file, byref(my_val))
	return (ret_val, my_val.value)

(CHANA, CHANB) = (0, 1)
(CHANA_ALWAYS_HIGH, CHANB_ALWAYS_HIGH, BOTH_ALWAYS_HIGH) = (i * 2 for i in (range(1, 4)))
def axi_to_dac_full_conf(filename, chanA_val, chanB_val, enable_high, sync_chan):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.axi_to_dac_full_conf(file, chanA_val, chanB_val,enable_high, sync_chan)

def axi_to_dac_set_chan(filename, chan, val):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.axi_to_dac_set_chan(file, chan, val)

def axi_to_dac_conf_enable(filename, enable_high):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.axi_to_dac_conf_enable(file, enable_high)

def axi_to_dac_conf_sync(filename, sync_chan):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.axi_to_dac_conf_sync(file, sync_chan)

def edfb_send_conf(filename, position):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.edfb_send_conf(file, position)

def edfb_get_conf(filename):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.edfb_get_conf(file)

def fir_send_conf(filename, fileCoeff, coeffSize):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.fir_send_conf(file, fileCoeff, coeffSize)

def fir_send_confSigned(filename, fileCoeff, coeffSize):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.fir_send_confSigned(file, fileCoeff, coeffSize)

def fir_read_conf(filename, content, coeffSize):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.fir_read_conf(file, content, coeffSize)

def fir_MultiSend_StartStop_confSigned(basename,startFir, nbFir,fileCoeff, coeffSize):
	lib.fir_MultiSend_StartStop_confSigned(basename,startFir, nbFir,fileCoeff, coeffSize)

def fir_MultiSend_confSigned(basename, nbFir,fileCoeff, coeffSize):
	lib.fir_MultiSend_confSigned(basename, nbFir,fileCoeff, coeffSize)

def fpgagen_send_conf(filename, reg, value):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.fpgagen_send_conf(file, reg, value)

def fpgagen_recv_conf(filename, reg, value):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.fpgagen_recv_conf(file, reg, value)

def nco_counter_send_conf(filename,freqHz_ref, freqHz_out,accum_size, offset,pinc_sw, poff_sw):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.nco_counter_send_conf(file,freqHz_ref, freqHz_out,accum_size, offset,pinc_sw, poff_sw)

def nco_counter_set_max_accum(filename, max):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.nco_counter_set_max_accum(file, max)

(KP, KI, KD, SETPOINT, SIGN, RST_INT) = (range(0, 6))
def pidv3_axi_set(filename, chan, val):
	file = ctypes.create_string_buffer(str.encode(filename))
	my_val = ctypes.c_int32(val)
	lib.pidv3_axi_set_kchan(file, chan, my_val)

def pidv3_axi_set_int_rst(filename, rst):
	file = ctypes.create_string_buffer(str.encode(filename))
	my_val = ctypes.c_int8(rst)
	lib.pidv3_axi_set_int_rst(file, my_val)

def pidv3_axi_set_sign(filename, sign):
	file = ctypes.create_string_buffer(str.encode(filename))
	my_val = ctypes.c_int8(sign)
	lib.pidv3_axi_set_sign(file, my_val)

def redpitaya_converters_12_spi_conf(filename, adc_dac_sel_val, conf_addr_val, config_val, conf_en_val):
	file = ctypes.create_string_buffer(str.encode(filename))
	conf_en = ctypes.c_int8(conf_en_val)
	conf_addr = ctypes.c_ubyte(conf_addr_val)
	config = ctypes.c_ubyte(config_val)
	adc_dac_sel = ctypes.c_int8(adc_dac_sel_val)
	lib.redpitaya_converters_12_spi_conf(file, adc_dac_sel, conf_addr, config, conf_en)

def redpitaya_converters_12_ext_ref_enable(filename, pll_en_val):
	file = ctypes.create_string_buffer(str.encode(filename))
	pll_en = ctypes.c_int8(pll_en_val)
	lib.redpitaya_converters_12_ext_ref_enable(file, pll_en)

def redpitaya_converters_12_get_ref_status(filename):
	file = ctypes.create_string_buffer(str.encode(filename))
	val = ctypes.c_int8()
	ret_val = lib.redpitaya_converters_12_get_ref_status(file, byref(val))
	return (ret_val, val.value)

def switch_send_conf(filename, input):
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.switch_send_conf(file, input)

def shifter_set(filename, shift):
	my_val = ctypes.c_int32(shift)
	file = ctypes.create_string_buffer(str.encode(filename))
	lib.shifter_set(file, my_val)

def shifter_get(filename):
	file = ctypes.create_string_buffer(str.encode(filename))
	my_val = ctypes.c_int32()
	ret_val = lib.shifter_get(file, my_val)
	return (ret_val, my_val.value)

(CH1, CH2) = (0x01, 0x02)
#(S1, S2) = (0x00, 0x01)
def RP_12_setAC_DC(port_name, mode_num):
	# RP_MAX7311_IN2 RP_MAX7311_IN1 port 0x01 0x02
	# mode RP_AC_MODE 0x01 or RP_DC_MODE 0x00
	mode = ctypes.c_int8(mode_num)
	port = port_name
	lib.rp_setAC_DC(port,mode)

def RP_12_setAttenuator(port_name, mode_num):
	# RP_MAX7311_IN2 RP_MAX7311_IN1 port 0x01 0x02
	# mode RP_ATTENUATOR_1_1 0x01 or RP_ATTENUATOR_1_20 0x00
	mode = ctypes.c_int8(mode_num)
	port = port_name
	lib.rp_setAttenuator(port,mode)

def RP_12_setGainOut(port_name, mode_num):
	# RP_MAX7311_OUT2 RP_MAX7311_OUT1 port 0x01 0x02
	# mode RP_GAIN_2V 0x00 or RP_GAIN_10V 0x01
	mode = ctypes.c_int8(mode_num)
	port = port_name 
	lib.rp_setGainOut(port,mode)

def RP_12_initController():
	lib.rp_initController()
	return
