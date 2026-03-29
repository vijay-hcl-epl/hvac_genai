#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

#include <stdint.h>

typedef enum {
    EID_STATE_IDLE,
    EID_STATE_SIGNAL_DRIVE,
    EID_STATE_FEEDBACK_CAPTURE
} ElectricalInterface_State_e;

typedef struct {
    uint8_t currentState;
    uint8_t ledState;
} ElectricalInterface_Data_t;

void ElectricalInterface_Init(ElectricalInterface_Data_t *eid);
void ElectricalInterface_Drive(ElectricalInterface_Data_t *eid, uint8_t signal);
void ElectricalInterface_Capture(ElectricalInterface_Data_t *eid);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
