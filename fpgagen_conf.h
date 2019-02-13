#ifndef FPGAGEN_CONF_H
#define FPGAGEN_CONF_H

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif

int fpgagen_send_conf(char *filename, int reg, int value);
int fpgagen_recv_conf(char *filename, int reg, int *value);

#ifdef __cplusplus
}
#endif

#endif /*FPGAGEN_CONF_H*/
