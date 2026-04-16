#ifndef MOTOR_FLAP_ACTUATION_AND_POSITIONING_UNIT_H
#define MOTOR_FLAP_ACTUATION_AND_POSITIONING_UNIT_H
// Structs from Internal Data Design
typedef struct {
    int target_position;
    int motor_state;
    int direction_control;
    int adc_discrete_position;
    int adc_valid;
} MotorFlapInternalData;

// Enums from State Machine
typedef enum {
    STATE_MOVE_TO_POSITION,
    STATE_STOP_MOTOR_AT_TARGET,
    STATE_SWITCH_DIRECTION,
    STATE_QUANTIZE_POSITION,
    STATE_ERROR_ADC_RANGE
} MotorFlapState;

// Function declarations
void Motor_Flap_Actuation_and_Positioning_Unit_resp_0(void);
void Motor_Flap_Actuation_and_Positioning_Unit_resp_1(void);
void Motor_Flap_Actuation_and_Positioning_Unit_resp_2(void);
void Motor_Flap_Actuation_and_Positioning_Unit_resp_3(void);
void Motor_Flap_Actuation_and_Positioning_Unit_resp_4(void);

#endif /* MOTOR_FLAP_ACTUATION_AND_POSITIONING_UNIT_H */
