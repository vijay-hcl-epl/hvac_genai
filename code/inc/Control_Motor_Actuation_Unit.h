#ifndef CONTROL_MOTOR_ACTUATION_UNIT_H
#define CONTROL_MOTOR_ACTUATION_UNIT_H

#include <stdint.h>

typedef struct {
    uint8_t target_flap_position;
    uint8_t current_position;
    uint16_t adc_thresholds[6];
    uint8_t motor_state;
    uint8_t target_reached;
    uint8_t adc_safety_status;
    uint8_t logic_state;
    uint8_t actuation_fault_flag;
    uint8_t shutdown_flag;
} ControlMotorActuationUnitData;

typedef enum {
    CMAU_WAIT_FOR_COMMAND = 0,
    CMAU_MOTOR_POSITIONING,
    CMAU_IDLE,
    CMAU_ERROR_RECOVERY
} ControlMotorActuationUnitState;

void Control_Motor_Actuation_Unit_resp_1(ControlMotorActuationUnitData* data, uint8_t command);
void Control_Motor_Actuation_Unit_resp_2(ControlMotorActuationUnitData* data, uint8_t cur_pos);
void Control_Motor_Actuation_Unit_resp_3(ControlMotorActuationUnitData* data);

#endif // CONTROL_MOTOR_ACTUATION_UNIT_H
