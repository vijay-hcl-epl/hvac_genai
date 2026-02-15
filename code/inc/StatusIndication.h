#ifndef STATUSINDICATION_H
#define STATUSINDICATION_H
#include <stdint.h>
#include <stdbool.h>
void StatusIndication_Init(void);
void StatusIndication_SetLed(uint8_t pos);
void StatusIndication_PowerLed(bool on);
#endif /* MISRA: Rule 20.5 – Preprocessor #endif should have comment */
