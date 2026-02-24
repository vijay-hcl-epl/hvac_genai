#ifndef STATUS_LED_MANAGER_H
#define STATUS_LED_MANAGER_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    LED_POWER = 0,
    LED_ERROR,
    LED_FLAP_POS_0,
    LED_FLAP_POS_1,
    LED_FLAP_POS_2,
    LED_FLAP_POS_3,
    LED_COUNT
} Led_t;

void status_led_manager_init(void);
void set_led_status(Led_t led, bool on);

#endif // STATUS_LED_MANAGER_H
