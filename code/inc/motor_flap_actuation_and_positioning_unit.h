#ifndef MOTOR_FLAP_ACTUATION_AND_POSITIONING_UNIT_H
#define MOTOR_FLAP_ACTUATION_AND_POSITIONING_UNIT_H

#include <stdint.h>
#include <stdbool.h>

// Internal Data Design
typedef enum {
    MOTOR_STATE_OFF,
    MOTOR_STATE_ON_CW,
    MOTOR_STATE_ON_CCW,
    MOTOR_STATE_ERROR
} MotorState_e;

typedef enum {
    FLAP_STATE_MOVE,
    FLAP_STATE_STOP,
    FLAP_STATE_SWITCH_DIR,
    FLAP_STATE_QUANTIZE,
    FLAP_STATE_ERROR
} FlapState_e;

typedef struct {
    uint16_t target_position;
    MotorState_e motor_state;
    uint8_t direction; // 0: CW, 1: CCW
    uint16_t adc_position;
    bool adc_valid;
} MotorFlapData_t;

// Interface function declarations
void motor_flap_resp_1(MotorFlapData_t *data, uint16_t user_command, uint16_t adc_feedback); // Move flap to requested position
void motor_flap_resp_2(MotorFlapData_t *data, uint16_t adc_feedback); // Stop the motor when reaches target
void motor_flap_resp_3(MotorFlapData_t *data); // Support movement in both directions
void motor_flap_resp_4(MotorFlapData_t *data, uint16_t adc_feedback); // Support discrete flap positions mapped by ADC
void motor_flap_resp_5(MotorFlapData_t *data, uint16_t adc_feedback); // Stop if ADC readings out of range

#endif
