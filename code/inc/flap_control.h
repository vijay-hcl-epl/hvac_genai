#ifndef FLAP_CONTROL_H
#define FLAP_CONTROL_H
#include <stdint.h>
typedef enum { FLAP_IDLE, FLAP_MOVING, FLAP_TARGET_REACHED, FLAP_ERROR } FlapState_t;
void FlapControl_request(uint8_t target);
void FlapControl_stop(void);
void flap_control_init(void);
#endif // FLAP_CONTROL_H
