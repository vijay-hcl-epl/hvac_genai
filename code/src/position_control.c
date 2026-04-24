#include "position_control.h"
#include "sensing.h"
#include "hardware_abstraction.h"
#include <stdbool.h>
#include <stdint.h>

static int pc_target = -1;
static bool pc_moving = false;

void PC_Init(void) {
    pc_target = -1;
    pc_moving = false;
}

void PC_NewCommand(int target_position) {
    pc_target = target_position;
    pc_moving = true;
}

void PC_LoopTask(void) {
    int curr_pos;
    bool valid = SENS_GetCurrentPosition(&curr_pos);
    if (!valid) {
        HA_StopMotor();
        pc_moving = false;
        return;
    }
    if (!pc_moving || pc_target < 0) return;
    if (curr_pos == pc_target) {
        HA_StopMotor();
        pc_moving = false;
    } else if (curr_pos < pc_target) {
        HA_StartMotor(true); // CW
    } else {
        HA_StartMotor(false); // CCW
    }
}
