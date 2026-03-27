#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

typedef enum {
    STATE_HAL_IDLE = 0,
    STATE_HAL_MOTOR_ACTIVE,
    STATE_HAL_LED_ACTIVE,
    STATE_HAL_ERROR
} HalState;

void Hal_SetMotorDirection(int dir);
void Hal_StopMotor(void);
void Hal_SetLedState(int state);

#endif // HARDWARE_ABSTRACTION_LAYER_H
