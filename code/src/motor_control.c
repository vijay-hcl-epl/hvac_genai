#include "motor_control.h"
#include <stdbool.h>
#include "system_config_data.h"
// Hardware-specific stubs
#define MOTOR_ENABLE_PIN   (1)
#define MOTOR_DIR_PIN      (2)
static bool motor_enabled = false;
static motor_direction_t motor_direction = MOTOR_DIR_OFF;

static void set_motor_pins(motor_direction_t dir, bool enable)
{
    // Hardware stub: set pin values
    (void)dir; (void)enable;
}

void motor_control_init(void) {
    motor_control_stop();
}

void motor_control_move(motor_direction_t dir)
{
    if (dir == MOTOR_DIR_FWD || dir == MOTOR_DIR_REV) {
        set_motor_pins(dir, true);
        motor_enabled = true;
        motor_direction = dir;
    } else {
        motor_control_stop();
    }
}

void motor_control_stop(void)
{
    set_motor_pins(MOTOR_DIR_OFF, false);
    motor_enabled = false;
    motor_direction = MOTOR_DIR_OFF;
}
