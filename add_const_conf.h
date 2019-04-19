#ifndef ADD_CONST_CONF_H
#define ADD_CONST_CONF_H

#ifdef __cplusplus /* if C++, specify external linkage to C functions */
extern "C" {
#endif
#include <stdint.h>

int add_const_set_offset(const char *filename, const int64_t offset);
int add_constMulti_set_offset(const char *basename, const int nb_adder, const int64_t *offset);
int add_const_get_offset(const char *filename, int64_t *offset);

#ifdef __cplusplus
}
#endif

#endif /*ADD_CONST_CONF_H*/
