#include "motor_driver_if.h"
#include "error_handler.h"
static uint8_t pwm_duty_cycle;
void MotorDriver_Init(void) {
    pwm_duty_cycle = 0;
    // hw init stub
}
void MotorDriver_Drive(MotorDirection dir, uint8_t duty) {
    pwm_duty_cycle = duty;
    // set PWM, direction GPIO here (stub)
}
void MotorDriver_Brake(void) {
    pwm_duty_cycle = 0;
    // brake logic stub
}
void MotorDriver_Off(void) {
    pwm_duty_cycle = 0;
    // deactivate bridge outputs stub
}
