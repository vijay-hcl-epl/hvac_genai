#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

typedef enum {
    EID_STATE_IDLE,
    EID_STATE_MOVE,
    EID_STATE_INDICATE,
    EID_STATE_ERROR
} EidState_t;

typedef struct {
    int motor_state;
    int led_state;
    int fault_flag;
    EidState_t state;
} ElectricalInterfaceDriver_t;

void EID_MoveMotor(ElectricalInterfaceDriver_t* eid);
void EID_UpdateLED(ElectricalInterfaceDriver_t* eid);
void EID_CheckFault(ElectricalInterfaceDriver_t* eid);

#endif
