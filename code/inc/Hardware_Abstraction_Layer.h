#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

typedef enum {
    STATE_HAL_IDLE,
    STATE_HAL_MOTOR_ACTIVE,
    STATE_HAL_LED_ACTIVE,
    STATE_HAL_ERROR
} HAL_StateType;

typedef struct {
    int motorState;
    int indicatorState;
} HardwareAbstractionLayer_DataType;

int Hal_SetMotorDirection(int direction);
void Hal_StopMotor(void);
int Hal_SetLedState(int state);

#endif // HARDWARE_ABSTRACTION_LAYER_H
