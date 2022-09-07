#include "12_rp-i2c-max7311.h"
#include "12_i2c.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)

unsigned long g_sleep_time = 50 * 1000;

char g_I2C_address = 0;
char getDefaultAddress();

int initController(const char *i2c_dev_path,  char address){
    _Bool state = 1;
    char value = 0xAA;
    // setup reset relay
    state = (write_to_i2c(i2c_dev_path , address , 0x02, value , 0) == 0) & state;
    state = (write_to_i2c(i2c_dev_path , address , 0x03, value , 0) == 0) & state;
    usleep(g_sleep_time);
    value = 0x00;
    // setup null level on all out ports
    state = (write_to_i2c(i2c_dev_path , address , 0x02, value , 0) == 0) & state;
    state = (write_to_i2c(i2c_dev_path , address , 0x03, value , 0) == 0) & state;
    // setup all port in outgoing mode
    value = 0x00;
    state = (write_to_i2c(i2c_dev_path , address , 0x06, value , 0) == 0) & state;
    state = (write_to_i2c(i2c_dev_path , address , 0x07, value , 0) == 0) & state;

    // check all regs
    state = (read_from_i2c(i2c_dev_path , address , 0x02, &value , 0) == 0) & state;
    state = (value == 0x00) & state;
    state = (read_from_i2c(i2c_dev_path , address , 0x03, &value , 0) == 0) & state;
    state = (value == 0x00) & state;
    state = (read_from_i2c(i2c_dev_path , address , 0x06, &value , 0) == 0) & state;
    state = (value == 0x00) & state;
    state = (read_from_i2c(i2c_dev_path , address , 0x07, &value , 0) == 0) & state;
    state = (value == 0x00) & state;
    return state;
}

int rp_initController(){
    return initController(DEFAULT_DEV_PATH, getDefaultAddress());
}

char getDefaultAddress(){
    if (g_I2C_address) return g_I2C_address;
    g_I2C_address = MAX7311_DEFAULT_ADDRESS_1_1;
    FILE *modelF = popen("i2cdetect -y -r 0 | grep 20: | cut -f2 -d:", "r");
    char model[128];
    fread(&model, sizeof(char), 128, modelF);
    char *found = strstr(model, "21");
    if(found){
        g_I2C_address = MAX7311_DEFAULT_ADDRESS_1_2;
    }
    return g_I2C_address;
}

int setPIN_GROUP(unsigned short pin_group,int state){
    return setPIN_GROUP_EX(DEFAULT_DEV_PATH, getDefaultAddress(), pin_group, state);
}

int setPIN_GROUP_EX(const char *i2c_dev_path, char address, unsigned short pin_group,int state){
    char value = 0;
    char flag = 0;
    char reg_addr = 0x02;
    if (pin_group > 0xFF) {
        reg_addr = 0x03;
        pin_group = pin_group >> 8;
    }

    if (read_from_i2c(i2c_dev_path , address , reg_addr, &value , 0) == -1)
        return -1;

    if (state == 0) flag = 0xAA;
    if (state == 1) flag = 0x55;

    value = ((value & ~pin_group) | (pin_group & flag));

    if (write_to_i2c(i2c_dev_path , address , reg_addr, value , 0) == -1)
        return -1;
    return 0;
}


int  rp_setAC_DC(char port,char mode){
    switch(port){
        case RP_MAX7311_IN2:
            if (setPIN_GROUP(PIN_K1,mode) == -1) return -1;
            usleep(g_sleep_time);
            if (setPIN_GROUP(PIN_K1,-1) == -1) return -1;
            break;
        case RP_MAX7311_IN1:
            if (setPIN_GROUP(PIN_K2,mode) == -1) return -1;
            usleep(g_sleep_time);
            if (setPIN_GROUP(PIN_K2,-1) == -1) return -1;
            break;
        default:
            return -1;
    }
    return 0;
}


int  rp_setAttenuator(char port,char mode){
    switch(port){
        case RP_MAX7311_IN2:
            if (setPIN_GROUP(PIN_K3,mode) == -1) return -1;
            usleep(g_sleep_time);
            if (setPIN_GROUP(PIN_K3,-1) == -1) return -1;
            break;
        case RP_MAX7311_IN1:
            if (setPIN_GROUP(PIN_K4,mode) == -1) return -1;
            usleep(g_sleep_time);
            if (setPIN_GROUP(PIN_K4,-1) == -1) return -1;
            break;
        default:
            return -1;
    }
    return 0;
}


int  rp_setGainOut(char port,char mode){
    switch(port){
        case RP_MAX7311_OUT2:
            if (setPIN_GROUP(PIN_K5,mode) == -1) return -1;
            usleep(g_sleep_time);
            if (setPIN_GROUP(PIN_K5,-1) == -1) return -1;
            break;
        case RP_MAX7311_OUT1:
            if (setPIN_GROUP(PIN_K6,mode) == -1) return -1;
            usleep(g_sleep_time);
            if (setPIN_GROUP(PIN_K6,-1) == -1) return -1;
            break;
        default:
            return -1;
    }
    return 0;
}
