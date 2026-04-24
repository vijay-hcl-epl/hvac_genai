#ifndef LED_STATUS_HANDLER_H
#define LED_STATUS_HANDLER_H

#include <stdbool.h>

void led_status_init(void);
void led_status_update(int position, bool fault);
void led_status_error_signal(void);

#endif // LED_STATUS_HANDLER_H
