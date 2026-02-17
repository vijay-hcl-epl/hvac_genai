#ifndef FLAP_POSITION_CTRL_H
#define FLAP_POSITION_CTRL_H
#include <stdint.h>

typedef enum { FLAP_IDLE, FLAP_MOVING, FLAP_TARGET, FLAP_ERROR} FlapState;

void FlapCtrl_eval(uint8_t target_pos, uint16_t adc_val);
FlapState FlapCtrl_status(void);

#endif // FLAP_POSITION_CTRL_H
