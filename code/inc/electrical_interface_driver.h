#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

typedef enum {
    EID_IDLE,
    EID_ACTIVE,
    EID_FAULT
} ElectricalInterfaceState_t;

typedef struct {
    int drive_channels;
    int status_flags;
} ElectricalInterfaceDriverData_t;

void ElectricalInterfaceDriver_Init(void);
void ElectricalInterfaceDriver_Update(void);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
