#ifndef SUPV_H
#define SUPV_H

#include <stdbool.h>

void supv_init(void);
bool supv_get_init_complete(void);
bool supv_get_safe_state(void);
void supv_report_unit_status(bool cmdh_ready, bool pos_ready, bool mtr_ready, bool led_ready);
void supv_report_unit_error(const char *unit, int errcode);

#endif // SUPV_H
