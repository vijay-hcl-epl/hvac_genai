#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

typedef enum {
    EID_POWER_OFF,
    EID_INIT,
    EID_ACTIVE,
    EID_FAULT
} EID_State_t;

typedef enum {
    EID_EVENT_NONE,
    EID_POWER_ON,
    EID_INIT_COMPLETE,
    EID_FAULT_DETECTED
} EID_Event_t;

typedef struct {
    int control_status;
    int initialized;
} EID_Register_t;

void EID_Init(void);
void EID_ControlMotor(int run);
void EID_ReadADCStatus(void);
void EID_MonitorHardware(void);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
