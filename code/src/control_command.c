#include "control_command.h"
#include "input_handler.h"
#include "position_acquisition.h"

#define GPIO_FLAP_DIRECTION 1
#define GPIO_FLAP_ENABLE    2

static int target_position = 0;
static motor_state_t motor_state = MOTOR_IDLE;

static void SetMotorDirection(int direction) {
    // TODO: Implement GPIO direction control
}
static void SetMotorEnable(uint8_t en) {
    // TODO: Implement GPIO enable/disable
}

void SetFlapPosition(int new_target_position) {
    target_position = new_target_position;
    motor_state = MOTOR_MOVING;
}

void StopMotor(void) {
    SetMotorEnable(0);
    motor_state = MOTOR_STOPPED;
}

void ControlCommandMain(void) {
    if (motor_state == MOTOR_MOVING) {
        int current_position = GetCurrentPosition();
        if (current_position < target_position) {
            SetMotorDirection(1);
            SetMotorEnable(1);
        } else if (current_position > target_position) {
            SetMotorDirection(-1);
            SetMotorEnable(1);
        } else {
            StopMotor();
        }
    }
    // TODO: Add error monitoring and transition to MOTOR_ERROR as per specification
}
