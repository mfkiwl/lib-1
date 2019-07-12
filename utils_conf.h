#ifndef UTILS_CONF_H
#define UTILS_CONF_H

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif

int shifter_set(char *filename, int shift);
int shifter_get(char *filename, int *shift);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_CONF_H */
