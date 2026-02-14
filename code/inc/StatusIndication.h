#ifndef STATUSINDICATION_H
#define STATUSINDICATION_H
#include <stdint.h>
#include <stdbool.h>
void StatusIndication_Init(void);
void StatusIndication_SetLed(uint8_t pos);
void StatusIndication_PowerLed(bool on);
#endif // STATUSINDICATION_H
