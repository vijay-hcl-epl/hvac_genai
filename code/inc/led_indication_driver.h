#ifndef LED_INDICATION_DRIVER_H
#define LED_INDICATION_DRIVER_H

#include <stdint.h>

typedef enum {
    LED_STATUS_OFF = 0,
    LED_STATUS_ON,
    LED_STATUS_ERROR
} LedStatus_t;

void set_led_state(LedStatus_t status);
LedStatus_t get_led_state(void);
void led_error_status(void);

#endif // LED_INDICATION_DRIVER_H
