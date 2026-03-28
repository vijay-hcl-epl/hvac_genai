#ifndef ELECTRICAL_INTERFACE_DRIVER_H
#define ELECTRICAL_INTERFACE_DRIVER_H
#include <stdint.h>

typedef enum {
    EID_STATE_IDLE = 0,
    EID_STATE_ACTUATE,
    EID_STATE_SAMPLE,
    EID_STATE_HOLD
} ElectricalInterfaceDriverState;

typedef struct {
    uint8_t output_latch;
    uint16_t adc_sample;
    uint8_t pwm_level;
    ElectricalInterfaceDriverState state;
} ElectricalInterfaceDriverContext;

void ElectricalInterfaceDriver_Init(ElectricalInterfaceDriverContext *ctx);
void ElectricalInterfaceDriver_Process(ElectricalInterfaceDriverContext *ctx);

#endif // ELECTRICAL_INTERFACE_DRIVER_H
