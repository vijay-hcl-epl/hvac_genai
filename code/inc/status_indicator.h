#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H

typedef enum {
    LED_OFF,
    LED_MOVING,
    LED_AT_TARGET,
    LED_ERROR
} led_state_t;

// LED Control API
void status_indicator_update(led_state_t state);

#endif // STATUS_INDICATOR_H
