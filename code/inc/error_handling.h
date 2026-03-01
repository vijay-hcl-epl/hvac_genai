#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H
#include <stdbool.h>
void error_handling_init(void);
void error_on_uart(void);
void error_on_adc(void);
bool error_is_safe(void);
void error_clear(void);
#endif // ERROR_HANDLING_H
