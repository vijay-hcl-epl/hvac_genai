#ifndef STATUS_INDICATION_H
#define STATUS_INDICATION_H

#include <stdint.h>
#include <stdbool.h>
#include "state_manager.h"

void StatusIndication_Init(void);
void StatusIndication_Update(bool power_on, uint8_t pos_idx);
void StatusIndication_UpdateOnState(system_state_t state);

#endif // STATUS_INDICATION_H
