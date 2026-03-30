#include "Hardware_Abstraction_Layer.h"
#include "Electrical_Interface_Driver.h"

void HardwareAbstractionLayer_Init(HardwareAbstractionLayer_Data_t *data) {
    data->adc_value = 0;
    data->gpio_state = 0;
    data->led_status = 0;
    data->state = HAL_INIT;
}

void HardwareAbstractionLayer_Periodic(HardwareAbstractionLayer_Data_t *data) {
    // Periodic sensor read and status update
    data->adc_value = ElectricalInterfaceDriver_ReadADC();
    data->gpio_state = ElectricalInterfaceDriver_ReadGPIO();
    data->led_status = ElectricalInterfaceDriver_GetLEDStatus();
}

void HardwareAbstractionLayer_ReceiveCommand(uint8_t cmd) {
    // Forward to low-level
    ElectricalInterfaceDriver_DriveMotorTo(cmd);
}
