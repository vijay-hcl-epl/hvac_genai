#include "ElectricalInterfaceDriver.h"

void ElecDrv_Init(ElectricalInterfaceDriver_t* instance) {
    instance->motor_status = 0;
    instance->adc_status = 0;
    instance->led_status = 0;
    instance->state = ELEC_IDLE;
}

void ElecDrv_PerformIO(ElectricalInterfaceDriver_t* instance) {
    switch(instance->state) {
        case ELEC_IDLE:
            // Wait for io request
            break;
        case ELEC_OP:
            // Perform direct hw op (register/poll/etc)
            // If error, set all to safe default
            instance->state = ELEC_DONE;
            break;
        case ELEC_DONE:
            // Transaction done
            instance->state = ELEC_IDLE;
            break;
        default:
            instance->state = ELEC_IDLE;
            break;
    }
}
