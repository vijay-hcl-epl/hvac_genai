#ifndef HARDWARE_ABSTRACTION_LAYER_H
#define HARDWARE_ABSTRACTION_LAYER_H

// HAL States
typedef enum {
    STATE_HAL_IDLE,
    STATE_HAL_MOTOR_ACTIVE,
    STATE_HAL_LED_ACTIVE,
    STATE_HAL_ERROR
} HalState_t;

// HAL static data
static HalState_t hal_state;
static int hal_motor_state;
static int hal_indicator_state;

// Function prototypes
void Hal_Init(void);
void Hal_SetMotorDirection(int direction);
void Hal_StopMotor(void);
void Hal_SetLedState(int led_id, int state);

#endif // HARDWARE_ABSTRACTION_LAYER_H
