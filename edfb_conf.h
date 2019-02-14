#ifndef EDFB_CONF_H
#define EDFB_CONF_H

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif

int edfb_send_conf(char *filename, int position);
int edfb_get_conf(char *filename);

#ifdef __cplusplus
}
#endif

#endif /*EDFB_CONF_H*/
