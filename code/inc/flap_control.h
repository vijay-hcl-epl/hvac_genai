#ifndef FLAP_CONTROL_H
#define FLAP_CONTROL_H
#include <stdint.h>
typedef enum { FLAP_IDLE, FLAP_MOVING, FLAP_SAFE, FLAP_ERROR } FlapControlState;
void FlapControl_Init(void);
void FlapControl_MoveTo(uint8_t position);
void FlapControl_Update(void);
uint8_t FlapControl_GetStatus(void);
#endif
