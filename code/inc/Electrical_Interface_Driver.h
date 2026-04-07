#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

#include <stdint.h>
typedef enum {
    EDRV_STATE_IDLE,
    EDRV_STATE_DRIVE,
    EDRV_STATE_REST
} ElectricalDriverState_t;

typedef struct {
    uint8_t motor_enable;
    uint8_t led_selector;
    ElectricalDriverState_t state;
} ElectricalDriverContext_t;

void ElectricalInterfaceDriver_Init(ElectricalDriverContext_t* ctx);
void ElectricalInterfaceDriver_Task(ElectricalDriverContext_t* ctx);
int ElectricalInterfaceDriver_SetTargetPosition(uint16_t pos);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
