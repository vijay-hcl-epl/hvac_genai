/* MotorDriver.c - Motor control logic for enable, disable, and direction. */
#include "MotorDriver.h"
#include "GPIO.h"

void MotorDriver_Init(void) {
    GPIO_SetMotorEnable(false);
}

void MotorDriver_CmdActuate(uint8_t direction) {
    if (direction == MOTOR_DIR_UP) {
        GPIO_SetMotorDir(true);
    } else {
        GPIO_SetMotorDir(false);
    }
    GPIO_SetMotorEnable(true);
}

void MotorDriver_Stop(void) {
    GPIO_SetMotorEnable(false);
}
