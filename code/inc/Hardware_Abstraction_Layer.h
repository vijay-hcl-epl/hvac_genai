#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

typedef enum {
    HAL_STATE_IDLE,
    HAL_STATE_MOTOR_ACTIVE,
    HAL_STATE_LED_ACTIVE,
    HAL_STATE_ERROR
} HalState_t;

typedef struct {
    int motorState;
    int indicatorState;
} Hal_Data_t;

int Hal_SetMotorDirection(int direction);
int Hal_StopMotor(void);
int Hal_SetLedState(int state);

#endif // HARDWARE_ABSTRACTION_LAYER_H
