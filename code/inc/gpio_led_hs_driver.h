#ifndef GPIO_LED_HS_DRIVER_H
#define GPIO_LED_HS_DRIVER_H
#include <stdint.h>

typedef enum { INDICATE_IDLE, INDICATE_MOVING, INDICATE_TARGET, INDICATE_FAULT } IndicateState;

void GPIO_init(void);
void LED_set(IndicateState state);
void HS_set(uint8_t index, uint8_t state);

#endif // GPIO_LED_HS_DRIVER_H
