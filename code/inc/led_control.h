#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <stdint.h>

void led_control_init(void);
void led_update(int8_t position);

#endif // LED_CONTROL_H
/* MISRA: Rule 20.3 – Ending preprocessor directives with comments for readability */
