import ctypes
from ctypes import *
lib = ctypes.CDLL('/usr/lib/liboscimp_fpga.so')

def add_const_set_offset(filename, offset):
	fichier = ctypes.create_string_buffer(str.encode(filename))
	my_val = c_longlong(offset)
	lib.add_const_set_offset(fichier, my_val)

def add_constMulti_set_offset(basename, nb_adder, offset):
	lib.add_constMulti_set_offset(basename, nb_adder, offset)

def add_const_get_offset(filename, offset):
	fichier = ctypes.create_string_buffer(str.encode(filename))
	my_val = c_longlong()
	ret_val = lib.add_const_get_offset(fichier, byref(my_val))
	return (ret_val, my_val.value)

(CHANA, CHANB) = (0, 1)
(CHANA_ALWAYS_HIGH, CHANB_ALWAYS_HIGH, BOTH_ALWAYS_HIGH) = (i * 2 for i in (range(1, 4)))
def axi_to_dac_full_conf(filename, chanA_val, chanB_val, enable_high, sync_chan):
	fichier = ctypes.create_string_buffer(str.encode(filename))
	lib.axi_to_dac_full_conf(fichier, chanA_val, chanB_val,enable_high, sync_chan)

def axi_to_dac_set_chan(filename, chan, val):
	fichier = ctypes.create_string_buffer(str.encode(filename))
	lib.axi_to_dac_set_chan(fichier, chan, val)

def axi_to_dac_conf_enable(filename, enable_high):
	fichier = ctypes.create_string_buffer(str.encode(filename))
	lib.axi_to_dac_conf_enable(fichier, enable_high)

def axi_to_dac_conf_sync(filename, sync_chan):
	fichier = ctypes.create_string_buffer(str.encode(filename))
	lib.axi_to_dac_conf_sync(fichier, sync_chan)

def edfb_send_conf(filename, position):
	lib.edfb_send_conf(filename, position)

def edfb_get_conf(filename):
	lib.edfb_get_conf(filename)

def fir_send_conf(filename, fileCoeff, coeffSize):
	lib.fir_send_conf(filename, fileCoeff, coeffSize)

def fir_send_confSigned(filename, fileCoeff, coeffSize):
	lib.fir_send_confSigned(filename, fileCoeff, coeffSize)

def fir_read_conf(filename, content, coeffSize):
	lib.fir_read_conf(filename, content, coeffSize)

def fir_MultiSend_StartStop_confSigned(basename,startFir, nbFir,fileCoeff, coeffSize):
	lib.fir_MultiSend_StartStop_confSigned(basename,startFir, nbFir,fileCoeff, coeffSize)

def fir_MultiSend_confSigned(basename, nbFir,fileCoeff, coeffSize):
	lib.fir_MultiSend_confSigned(basename, nbFir,fileCoeff, coeffSize)

def fpgagen_send_conf(filename, reg, value):
	lib.fpgagen_send_conf(filename, reg, value)

def fpgagen_recv_conf(filename, reg, value):
	lib.fpgagen_recv_conf(filename, reg, value)

def nco_counter_send_conf(filename,freqHz_ref, freqHz_out,accum_size, offset,pinc_sw, poff_sw):
	lib.nco_counter_send_conf(filename,freqHz_ref, freqHz_out,accum_size, offset,pinc_sw, poff_sw)

def nco_counter_set_max_accum(filename, max):
	lib.nco_counter_set_max_accum(filename, max)

(KP, KI, KD, SETPOINT, SIGN, RST_INT) = (range(0, 6))
def pidv3_axi_set(filename, chan, val):
	fichier = ctypes.create_string_buffer(str.encode(filename))
	my_val = ctypes.c_int32(val)
	lib.pidv3_axi_set_kchan(fichier, chan, my_val)

def pidv3_axi_set_int_rst(filename, rst):
	fichier = ctypes.create_string_buffer(str.encode(filename))
	my_val = ctypes.c_int8(rst)
	lib.pidv3_axi_set_int_rst(fichier, my_val)

def pidv3_axi_set_sign(filename, sign):
	fichier = ctypes.create_string_buffer(str.encode(filename))
	my_val = ctypes.c_int8(sign)
	lib.pidv3_axi_set_sign(fichier, my_val)

def switch_send_conf(filename, input):
	lib.switch_send_conf(filename, input)

def shifter_set(filename, shift):
	lib.shifter_set(filename, shift)

def shifter_get(filename, shift):
	lib.shifter_get(filename, shift)

