#ifndef FLAP_CONTROL_H
#define FLAP_CONTROL_H
#include <stdint.h>
typedef enum { FLAP_IDLE = 0, FLAP_MOVING, FLAP_ERROR } FlapState_t;
void FlapControl_Init(void);
void FlapControl_StartMovement(uint8_t target_pos);
void FlapControl_StopMovement(void);
FlapState_t FlapControl_GetState(void);
void FlapControl_PeriodicTask(void);
#endif /* FLAP_CONTROL_H */
