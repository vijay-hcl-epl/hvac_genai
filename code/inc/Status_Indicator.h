#ifndef STATUS_INDICATOR_H
#define STATUS_INDICATOR_H

typedef enum {
    LED_OFF,
    LED_RED,
    LED_GREEN
} LedState_t;

typedef struct {
    LedState_t red_led;
    LedState_t green_led;
    int position;
} StatusIndicator_t;

void Status_Indicator_Init(StatusIndicator_t *si);
void Status_Indicator_Update(StatusIndicator_t *si, int position, int power_on);

#endif // STATUS_INDICATOR_H
