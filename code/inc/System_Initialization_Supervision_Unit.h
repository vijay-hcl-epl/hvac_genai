#ifndef SYSTEM_INITIALIZATION_SUPERVISION_UNIT_H
#define SYSTEM_INITIALIZATION_SUPERVISION_UNIT_H

#include <stdint.h>

typedef struct {
    uint8_t adc_init_flag;
    uint8_t uart_init_flag;
    uint8_t pwm_init_flag;
    uint8_t gpio_init_flag;
    uint8_t system_mode;
    uint8_t supervision_timer;
    uint8_t safety_condition_flag;
} SystemInitializationSupervisionUnitData;

typedef enum {
    SISU_POWER_UP = 0,
    SISU_INITIALIZE_PERIPHERALS,
    SISU_WAIT_FOR_COMMAND,
    SISU_SUPERVISE
} SystemInitializationSupervisionUnitState;
void System_Initialization_Supervision_Unit_resp_1(SystemInitializationSupervisionUnitData* data);
void System_Initialization_Supervision_Unit_resp_2(SystemInitializationSupervisionUnitData* data, uint8_t valid_cmd);
void System_Initialization_Supervision_Unit_resp_3(SystemInitializationSupervisionUnitData* data, uint8_t motor_fault);

#endif // SYSTEM_INITIALIZATION_SUPERVISION_UNIT_H
