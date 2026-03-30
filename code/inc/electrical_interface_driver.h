#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H

#include <stdint.h>
typedef enum {
    EID_STATE_IDLE,
    EID_STATE_MOTORDRIVE,
    EID_STATE_ADCREAD,
    EID_STATE_LEDCONTROL
} eid_state_t;

typedef struct {
    uint8_t gpio_reg;
    uint16_t adc_register;
} ElectricalAbstraction;

typedef struct {
    ElectricalAbstraction hw;
    eid_state_t state;
} ElectricalInterfaceDriver;

void eid_init(ElectricalInterfaceDriver* eid);
void eid_drive_motor(ElectricalInterfaceDriver* eid, int enable);
uint16_t eid_adc_read(ElectricalInterfaceDriver* eid);
void eid_control_led(ElectricalInterfaceDriver* eid, int on);
void eid_handle_error(ElectricalInterfaceDriver* eid);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
