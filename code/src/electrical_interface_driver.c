#include "electrical_interface_driver.h"

void eid_init(ElectricalInterfaceDriver* eid) {
    eid->hw.gpio_reg = 0;
    eid->hw.adc_register = 0;
    eid->state = EID_STATE_IDLE;
}

void eid_drive_motor(ElectricalInterfaceDriver* eid, int enable) {
    // Simulate motor control
    eid->hw.gpio_reg = (enable) ? 1 : 0;
    eid->state = EID_STATE_MOTORDRIVE;
}

uint16_t eid_adc_read(ElectricalInterfaceDriver* eid) {
    // Simulate ADC
    eid->hw.adc_register = 500; // Fake ADC
    eid->state = EID_STATE_ADCREAD;
    return eid->hw.adc_register;
}

void eid_control_led(ElectricalInterfaceDriver* eid, int on) {
    // Simulate LED control
    if (on) { eid->hw.gpio_reg = 1; }
    else { eid->hw.gpio_reg = 0; }
    eid->state = EID_STATE_LEDCONTROL;
}

void eid_handle_error(ElectricalInterfaceDriver* eid) {
    eid->state = EID_STATE_IDLE;
}
