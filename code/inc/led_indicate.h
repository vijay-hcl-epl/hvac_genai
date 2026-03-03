#ifndef LED_INDICATE_H
#define LED_INDICATE_H

#include <stdint.h>

typedef enum {
    LED_STATUS_POWER = 0,
    LED_STATUS_POSITION,
    LED_STATUS_ERROR
} LED_Status_t;

void LED_Init(void);
void LED_SetPosition(int pos);
void LED_SetStatus(LED_Status_t status);

#endif // LED_INDICATE_H
