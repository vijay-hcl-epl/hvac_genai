#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

typedef enum {
    STATE_EID_IDLE = 0,
    STATE_EID_READ,
    STATE_EID_WRITE,
    STATE_EID_ERROR
} ElectricalIdState;

int ElectricalDriver_ReadAdc(void);
int ElectricalDriver_ReadInput(void);
void ElectricalDriver_SetMotor(int active);
void ElectricalDriver_StopMotor(void);
void ElectricalDriver_SetStatusLed(int state);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
