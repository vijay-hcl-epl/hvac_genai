#include "HardwareAbstractionLayer.h"
#include "ElectricalInterfaceDriver.h"

void HAL_Init(HardwareAbstractionLayer_t* instance) {
    instance->adc_value = 0;
    instance->gpio_status = 0;
    instance->uart_status = 0;
    instance->led_status = 0;
    instance->state = HW_IDLE;
}

void HAL_ProcessAction(HardwareAbstractionLayer_t* instance, int action) {
    // Example: decide what hardware op to process (abstract)
    instance->state = HW_IO_REQUEST;
    // set dummy values for illustration
    instance->adc_value = action * 10;
    instance->gpio_status = 1;
    instance->led_status = 1;
    instance->state = HW_COMPLETE;
}

void HAL_Run(HardwareAbstractionLayer_t* instance) {
    switch(instance->state) {
        case HW_IDLE:
            // Await cmd
            break;
        case HW_IO_REQUEST:
            // HAL perform operation (interact with ElectricalDriver)
            // ElectricalInterfaceDriver_PerformIO();
            instance->state = HW_UPDATING;
            break;
        case HW_UPDATING:
            // Update status, check completion
            instance->state = HW_COMPLETE;
            break;
        case HW_COMPLETE:
            // Finalize, return to IDLE
            instance->state = HW_IDLE;
            break;
        default:
            instance->state = HW_IDLE;
            break;
    }
}
