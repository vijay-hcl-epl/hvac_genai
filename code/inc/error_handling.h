#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H
#include <stdint.h>
#include <stdbool.h>
void error_handling_init(void);
// Report error code (0:none, 1:ADC, 2:Invalid cmd, etc)
void error_handling_report(uint8_t code);
bool error_handling_has_error(void);
void error_handling_clear(void);
#endif
