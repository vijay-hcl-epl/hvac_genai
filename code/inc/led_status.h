#ifndef LED_STATUS_H
#define LED_STATUS_H

#include <stdint.h>
#include <stdbool.h>
#define LED_POS_SIZE 8

typedef struct {
    uint8_t state_bits;
} led_status_t;

void led_status_init(led_status_t *inst);
void led_status_set_position(led_status_t *inst, uint8_t pos);
void led_status_power_ok(led_status_t *inst);
void led_status_error(led_status_t *inst);

#endif /* LED_STATUS_H */
