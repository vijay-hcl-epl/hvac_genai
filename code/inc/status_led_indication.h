#ifndef STATUS_LED_INDICATION_H
#define STATUS_LED_INDICATION_H
#include <stdint.h>
void status_led_indication_init(void);
void update_led_indication(uint8_t position_idx, uint8_t pwr_status);
#endif // STATUS_LED_INDICATION_H
