#include "flap_control.h"
#include "hw_abstraction.h"
#define FLAP_MIN_POS 0
#define FLAP_MAX_POS 5
static uint8_t target_pos = 0;
static uint8_t current_pos = 0;
static FlapControlState_t status = FLAP_IDLE;
static bool adc_fault = false;
void flap_control_init(void) {
    target_pos = hw_adc_read();
    current_pos = target_pos;
    status = FLAP_IDLE;
    adc_fault = false;
}
void flap_control_set_target(uint8_t pos) {
    if(pos < FLAP_MIN_POS || pos > FLAP_MAX_POS) return; // ignore
    target_pos = pos;
    status = FLAP_MOVING;
}
// This should be called periodically
void flap_control_update(void) {
    uint16_t adc = hw_adc_read();
    if(adc < 100 || adc > 4095) {
        adc_fault = true;
        status = FLAP_FAULT;
        hw_pwm_set_duty(0,0); // stop motor
        return;
    }
    current_pos = (adc - 100)/660; // normalize to 0–5
    if(status == FLAP_MOVING) {
        if(current_pos == target_pos) {
            hw_pwm_set_duty(0, 0); // stop motor
            status = FLAP_TARGET_REACHED;
        } else {
            uint8_t duty = 60; // nominal speed
            hw_pwm_set_duty(0, duty); // move to pos
        }
    }
}
FlapControlState_t flap_control_get_status(void) {
    return status;
}
void flap_control_clear_fault(void) {
    adc_fault = false;
    status = FLAP_IDLE;
}
uint8_t flap_control_get_position(void) {
    return current_pos;
}
