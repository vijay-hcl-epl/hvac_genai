#include "hardware_abstraction_layer.h"
#include "electrical_interface_driver.h"

void HAL_Init(void) {
    EID_Init();
}

uint16_t HAL_ReadADC(void) {
    return EID_ReadADC();
}

void HAL_SetRelay(uint8_t state) {
    EID_SetRelay(state);
}

void HAL_SetLED(uint8_t status) {
    EID_SetLED(status);
}

uint8_t HAL_GetLEDStatus(void) {
    return EID_GetLEDStatus();
}
