#include "Electrical_Interface_Driver.h"

void ElectricalDriver_Init(void) {
    eid_state = STATE_EID_IDLE;
    eid_adc_sample_value = 0;
    eid_gpio_output_state = 0;
    eid_input_state = 0;
}

int ElectricalDriver_ReadAdc(void) {
    eid_state = STATE_EID_READ;
    // Simulate ADC read
    eid_adc_sample_value = 42;
    return eid_adc_sample_value;
}

int ElectricalDriver_ReadInput(void) {
    eid_state = STATE_EID_READ;
    // Simulate digital input
    eid_input_state = 10;
    return eid_input_state;
}

void ElectricalDriver_SetMotor(int direction) {
    eid_gpio_output_state = direction;
    eid_state = STATE_EID_WRITE;
}

void ElectricalDriver_StopMotor(void) {
    eid_gpio_output_state = 0;
    eid_state = STATE_EID_IDLE;
}

void ElectricalDriver_SetStatusLed(int led_id, int state) {
    // Store state for given LED
    eid_state = STATE_EID_WRITE;
}
