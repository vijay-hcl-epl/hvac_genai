#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

typedef enum {
    EID_STATE_INIT,
    EID_STATE_ACTIVE,
    EID_STATE_FAULT
} EidState_t;

typedef struct {
    int reg_table[8];
    int status_reg[8];
} EidHandle_t;

void ElectricalInterfaceDriver_Init(EidHandle_t* e);
int ElectricalInterfaceDriver_Actuate(EidHandle_t* e, int pin, int val);
int ElectricalInterfaceDriver_Read(EidHandle_t* e, int pin);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
