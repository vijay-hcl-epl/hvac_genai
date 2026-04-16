#ifndef CONTROL_LOGIC_UNIT_H
#define CONTROL_LOGIC_UNIT_H

#include <stdint.h>

#define MAPPING_TABLE_SIZE 8

// Internal Data Design
typedef struct {
    int target_position;
    int motor_state;
    int mapping_table[MAPPING_TABLE_SIZE];
} ControlLogicUnitData;

// State Machine
typedef enum {
    STATE_IDLE,
    STATE_MOVE_TO_TARGET,
    STATE_STOPPED
} ControlLogicUnitState;

// Function Declarations
void control_logic_unit_resp_0(ControlLogicUnitData* data);
void control_logic_unit_resp_1(ControlLogicUnitData* data);
void control_logic_unit_resp_2(ControlLogicUnitData* data);

#endif // CONTROL_LOGIC_UNIT_H
