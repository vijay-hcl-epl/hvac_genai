#ifndef INDICATION_LED_H
#define INDICATION_LED_H
#include <stdint.h>
void IndicationLed_Init(void);
void IndicationLed_Update(uint8_t system_power, uint8_t position_idx);
#endif /* INDICATION_LED_H */
