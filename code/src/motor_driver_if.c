// RAG_SOURCE: infineon-tle9851qxw-datasheet-en.pdf §26-27, infineon-tle985xqx-usermanual-en.pdf §27
#include "motor_driver_if.h"
// Includes BDRV_CTRL, BDRV_CP_CTRL, CCU6_T12PR, CCU6_CC60SR, etc.
void MotorDriverIF_Run(uint8_t direction, uint8_t speed) {
    // Enable bridge driver (set BDRV_CTRL1 bits for H-bridge)
    // Ensure charge pump ready
    // Set direction using PWM output via CCU6
    // Set PWM period (CCU6_T12PR) and duty cycle (CCU6_CC60SR/61SR)
}
void MotorDriverIF_Stop(void) {
    // Disable all half-bridges (clear enable bits in BDRV_CTRL1)
}
void MotorDriverIF_Brake(void) {
    // Enter brake mode: set both LS or both HS ON, charge pump low power
}
void MotorDriverIF_Init(void) {
    // Configure CCU6 timer, BDRV SFRs for initial bridge safe state
    // See Register Table 294, User Manual §18.10
}
