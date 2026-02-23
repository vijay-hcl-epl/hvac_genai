#ifndef FLAP_MANAGER_H
#define FLAP_MANAGER_H
#include <stdint.h>
int FLAP_MapADC(uint16_t value);
void FLAP_SetTarget(int position);
void FLAP_Process(void);
int FLAP_GetCurrent(void);
int FLAP_GetTarget(void);
void FLAP_Init(void);
#endif // FLAP_MANAGER_H
