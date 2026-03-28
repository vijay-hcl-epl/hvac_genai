#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H
#include <stdint.h>

typedef enum {
    DRIVE_IDLE,
    DRIVE_ACTIVE
} drive_state_t;

void EID_Init(void);
void EID_Task(void);
void EID_Actuate(uint8_t cmd);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
