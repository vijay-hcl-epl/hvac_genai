#ifndef ERROR_SAFETY_MONITOR_H
#define ERROR_SAFETY_MONITOR_H
#include <stdbool.h>

void error_safety_monitor_init(void);
void error_safety_monitor_set_error(void);
void error_safety_monitor_clear_error(void);
bool error_safety_monitor_is_error(void);

#endif // ERROR_SAFETY_MONITOR_H
