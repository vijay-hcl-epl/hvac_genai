#ifndef LED_STATUS_INDICATOR_H
#define LED_STATUS_INDICATOR_H

#include <stdint.h>

typedef struct {
    uint8_t power_led_state;
    uint8_t green_led_states[6];
    uint8_t led_update_needed;
} led_status_indicator_t;

typedef enum {
    POWER_OFF,
    POWER_ON
} power_led_state_e;

typedef enum {
    POSITIONLED_NONE,
    POSITIONLED_0,
    POSITIONLED_1,
    POSITIONLED_2,
    POSITIONLED_3,
    POSITIONLED_4,
    POSITIONLED_5
} green_led_state_e;

typedef enum {
    PENDING_STATE_CHANGE,
    STATE_SYNCHRONIZED
} led_sync_state_e;

void led_status_indicator_resp_1(led_status_indicator_t *ctx);
void led_status_indicator_resp_2(led_status_indicator_t *ctx);
void led_status_indicator_resp_3(led_status_indicator_t *ctx);

#endif
